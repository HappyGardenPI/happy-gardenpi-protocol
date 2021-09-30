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
// Created by Antonio Salsi on 19/09/21.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"

#include "hgardenpi-protocol/packages/synchro.hpp"

#include <stdexcept>
#include <memory>
#include <cstring>
#include <iostream>
using namespace std;

#include <hgardenpi-protocol/utilities/stringutils.hpp>
#include <hgardenpi-protocol/constants.hpp>

namespace hgardenpi::protocol
{
    inline namespace v1
    {

        string Synchro::getSerial() const noexcept
        {
            HGARDENPI_PROTOCOL_GETTER(serial, length)
        }

        void Synchro::setSerial(const string &serial) noexcept
        {
            HGARDENPI_PROTOCOL_SETTER(serial, length)
        }

        Synchro *Synchro::deserialize(const uint8_t *buffer, uint8_t len, uint8_t)
        {
            if (!buffer)
            {
                return nullptr;
            }
            auto syn = new(nothrow) Synchro;
            if (!syn)
            {
                throw runtime_error("no memory for sin");
            }

            //set length of certificate and payload
            memset(&syn->length, 0, sizeof(syn->length));
            memcpy(&syn->length, buffer, sizeof(syn->length));

            syn->serial = new(nothrow) char[syn->length];
            if (!syn->serial)
            {
                throw runtime_error("no memory for serial");
            }
            memset(syn->serial, 0, syn->length);
            memcpy(syn->serial, buffer + sizeof(syn->length), syn->length);

            return syn;
        }

        Buffer Synchro::serialize() const
        {
            Buffer ret;

            if (length > HEAD_MAX_SERIAL_SIZE - sizeof(length))
            {
                throw runtime_error("serial too long max 255 chars");
            }

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
            memcpy(ret.first.get() + sizeof(length), &serial[0], length);

            //return Buffer
            return ret;
        }

    }
}
#pragma clang diagnostic pop