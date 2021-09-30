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
    inline namespace v1
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

            //copy cert length
            memcpy(ret.first.get(), &length, sizeof(length));

            //copy certificate field to payload
            memcpy(ret.first.get() + sizeof(length), &msg[0], length);

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
                //set length of certificate and payload
                memset(&err->length, 0, sizeof(err->length));
                memcpy(&err->length, buffer, sizeof(err->length));

                err->msg = new (nothrow) char[err->length];
                if (!err->msg)
                {
                    throw runtime_error("no memory for msg");
                }
                memset(err->msg, 0, err->length);
                memcpy(err->msg, buffer + sizeof(err->length), err->length);

            }
            else
            {
                err->length = length;
                err->msg = new (nothrow) char[err->length];
                if (!err->msg)
                {
                    throw runtime_error("no memory for msg");
                }
                memset(err->msg, 0, err->length);
                memcpy(err->msg, buffer, err->length);
            }
            return err;
        }

        string Error::getMsg() const noexcept
        {
            char *c = new(nothrow) char[length + 1];
            memset(c, 0, length + 1);
            memcpy(c, msg, length);
            string ret(c);
            delete [] c;
            return ret;
        }

        void Error::setMsg(const string &msg) noexcept
        {
            length = msg.size();
            this->msg = new char [length];
            memset(this->msg, 0, length);
            memcpy(this->msg, &msg[0], length);
        }

    }
}
#pragma clang diagnostic pop