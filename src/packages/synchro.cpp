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
            char *c = new(nothrow) char[length + 1];
            memset(c, 0, length + 1);
            memcpy(c, serial, length);
            string ret(c);
            delete[] c;
            return ret;
        }

        void Synchro::setSerial(const string &serial) noexcept
        {
            length = serial.size();
            this->serial = new char[length];
            memset(this->serial, 0, length);
            memcpy(this->serial, &serial[0], length);
        }

        Synchro *Synchro::deserialize(const uint8_t *buffer, uint8_t len, uint8_t) noexcept
        {
            if (!buffer)
            {
                return nullptr;
            }
            auto ret = new Synchro;

            cout << "deserialize " << stringHexToString(buffer, len) << " " << to_string(len) << endl;

            //set length of certificate and payload
            memset(&ret->length, 0, sizeof(ret->length));
            memcpy(&ret->length, buffer, sizeof(ret->length));

            ret->serial = new char[ret->length];
            memset(ret->serial, 0, ret->length);
            memcpy(ret->serial, buffer + sizeof(ret->length), ret->length);

            return ret;
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

            cout << "serialize " << stringHexToString(ret.first.get(), ret.second) << " " << to_string(ret.second) << endl;

            //return Buffer
            return ret;
        }

    }
}
#pragma clang diagnostic pop