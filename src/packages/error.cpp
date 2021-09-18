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

#include "hgardenpi-protocol/packages/error.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
using namespace std;

#include "hgardenpi-protocol/constants.hpp"

#include <stdexcept>
#include <memory>

namespace hgardenpi::protocol
{
    inline namespace v1
    {

        Buffer Error::serialize() const
        {
            Buffer ret;

            ret.second = length + sizeof(length);

            //alloc memory
            ret.first = new(nothrow) uint8_t[ret.second];
            if (!ret.first)
            {
                throw runtime_error("no memory for data");
            }

            //copy cert length
            memcpy(ret.first, &length, sizeof(length));

            //copy certificate field to payload
            memcpy(ret.first + sizeof(length), &msg[0], length);

            //return Buffer
            return ret;
        }

        Error * Error::deserialize(const uint8_t *buffer, uint8_t length , uint8_t chunkOfPackage) noexcept
        {
            if (!buffer)
            {
                return nullptr;
            }
            auto ret = new Error;


            if (chunkOfPackage == 0)
            {
                //set length of certificate and payload
                memset(&ret->length, 0, sizeof(ret->length));
                memcpy(&ret->length, buffer, sizeof(ret->length));

                ret->msg = new char[ret->length];
                memset(ret->msg, 0, ret->length);
                memcpy(ret->msg, buffer + sizeof(ret->length), ret->length);

            }
            else
            {
                ret->length = length;
                ret->msg = new char[ret->length];
                memset(ret->msg, 0, ret->length);
                memcpy(ret->msg, buffer, ret->length);
            }
            return ret;
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

        void Error::setMsg(const string &certificate) noexcept
        {
            length = certificate.size();
            this->msg = new char [length];
            memset(this->msg, 0, length);
            memcpy(this->msg, &certificate[0], length);
        }

    }
}
#pragma clang diagnostic pop