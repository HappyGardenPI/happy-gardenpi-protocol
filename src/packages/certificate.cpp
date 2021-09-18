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

#include "hgardenpi-protocol/packages/certificate.hpp"

#include <stdexcept>
#include <cstring>
using namespace std;

#include "hgardenpi-protocol/constants.hpp"

namespace hgardenpi::protocol
{
    inline namespace v1
    {

        Buffer Certificate::serialize() const
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
            memcpy(ret.first + sizeof(length), &certificate[0], length);

            //return Buffer
            return ret;
        }

        Certificate * Certificate::deserialize(const uint8_t *buffer, uint8_t length , uint8_t chunkOfPackage) noexcept
        {
            if (!buffer)
            {
                return nullptr;
            }
            auto ret = new Certificate;


            if (chunkOfPackage == 0)
            {
                //set length of certificate and payload
                memset(&ret->length, 0, sizeof(ret->length));
                memcpy(&ret->length, buffer, sizeof(ret->length));

                ret->certificate = new char[ret->length];
                memset(ret->certificate, 0, ret->length);
                memcpy(ret->certificate, buffer + sizeof(ret->length), ret->length);

            }
            else
            {
                ret->length = length;
                ret->certificate = new char[ret->length];
                memset(ret->certificate, 0, ret->length);
                memcpy(ret->certificate, buffer, ret->length);
            }
            return ret;
        }

        string Certificate::getCertificate() const noexcept
        {
            char *c = new(nothrow) char[length + 1];
            memset(c, 0, length + 1);
            memcpy(c, certificate, length);
            string ret(c);
            delete [] c;
            return ret;
        }

        void Certificate::setCertificate(const string &certificate) noexcept
        {
            length = certificate.size();
            this->certificate = new char [length];
            memset(this->certificate, 0, length);
            memcpy(this->certificate, &certificate[0], length);
        }

    }
}
#pragma clang diagnostic pop