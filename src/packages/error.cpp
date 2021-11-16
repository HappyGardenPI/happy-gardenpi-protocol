// MIT License
//
// Copyright (c) 2021. Happy GardenPI
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

//
// Created by Antonio Salsi on 15/09/21.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"

#include "hgardenpi-protocol/packages/error.hpp"

#include <stdexcept>
#include <memory>
#include <cstring>
#include <iostream>
using namespace std;

#include "hgardenpi-protocol/constants.hpp"

namespace hgardenpi::protocol
{
    inline namespace v2
    {

        Buffer Error::serialize() const
        {
            Buffer ret;

            ret.second = length + sizeof(length);

            //alloc memory
            ret.first = shared_ptr<uint8_t []>(new(nothrow) uint8_t[ret.second]);
            if (!ret.first)
            {
                throw runtime_error("no memory for data");
            }

            if (length > 0)
            {
                //copy error length
                memcpy(ret.first.get(), &length, sizeof(length));

                //copy error field to payload
                memcpy(ret.first.get() + sizeof(length), &msg[0], length);
            }

            //return Buffer
            return ret;
        }

        Error * Error::deserialize(const uint8_t *buffer, uint8_t length , uint8_t chunkOfPackage)
        {
            if (!buffer)
            {
                return nullptr;
            }
            auto err = new(nothrow) Error;
            if (!err)
            {
                throw runtime_error("no memory for err");
            }

            if (chunkOfPackage == 0)
            {
                //set length of error and payload
                memset(&err->length, 0, sizeof(uint16_t));
                memcpy(&err->length, buffer, sizeof(uint16_t));

                err->chunkLength = length - sizeof(uint16_t);
                err->chunk = new char[err->chunkLength];
                memset(err->chunk, 0, err->chunkLength);
                memcpy(err->chunk, &buffer[sizeof(uint16_t)], err->chunkLength);

            }
            else
            {
                err->chunkLength = length;
                err->chunk = new char[err->chunkLength];
                memset(err->chunk, 0, err->chunkLength);
                memcpy(err->chunk, buffer, err->chunkLength);
            }
            return err;
        }

        string Error::getMsg() const noexcept
        {
            HGARDENPI_PROTOCOL_GETTER(msg, length)
        }

        void Error::setMsg(const string &msg) noexcept
        {
            HGARDENPI_PROTOCOL_SETTER(msg, length)
        }

        string Error::getChunk() const noexcept
        {
            HGARDENPI_PROTOCOL_GETTER(chunk, chunkLength)
        }

    }
}
#pragma clang diagnostic pop