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

#include "hgardenpi-protocol/packages/data.hpp"

#include <stdexcept>
#include <cstring>
using namespace std;

#include "hgardenpi-protocol/constants.hpp"

namespace hgardenpi::protocol
{
    inline namespace v2
    {

        Buffer Data::serialize() const
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
                memcpy(ret.first.get() + sizeof(length), &payload[0], length);
            }

            //return Buffer
            return ret;
        }

        Data * Data::deserialize(const uint8_t *buffer, uint8_t length, uint8_t chunkOfPackage)
        {
            if (!buffer)
            {
                return nullptr;
            }
            auto cer = new (nothrow) Data;
            if (!cer)
            {
                throw runtime_error("no memory for cer");
            }

            if (chunkOfPackage == 0)
            {
                //set length of payload
                memset(&cer->length, 0, sizeof(uint16_t));
                memcpy(&cer->length, buffer, sizeof(uint16_t));

                cer->chunkLength = length - sizeof(uint16_t);
                cer->chunk = new char[cer->chunkLength];
                memset(cer->chunk, 0, cer->chunkLength);
                memcpy(cer->chunk, &buffer[sizeof(uint16_t)], cer->chunkLength);
            }
            else
            {
                cer->chunkLength = length;
                cer->chunk = new char[cer->chunkLength];
                memset(cer->chunk, 0, cer->chunkLength);
                memcpy(cer->chunk, buffer, cer->chunkLength);
            }
            return cer;
        }

        string Data::getPayload() const noexcept
        {
            HGARDENPI_PROTOCOL_GETTER(payload, length)
        }

        void Data::setPayload(const string &payload) noexcept
        {
            HGARDENPI_PROTOCOL_SETTER(payload, length)
        }

        string Data::getChunk() const noexcept
        {
            HGARDENPI_PROTOCOL_GETTER(chunk, chunkLength)
        }

    }
}
#pragma clang diagnostic pop