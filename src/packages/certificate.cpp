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

#include "hgardenpi-protocol/packages/certificate.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
using namespace std;

#include "hgardenpi-protocol/constants.hpp"

namespace hgardenpi::protocol
{
    inline namespace v1
    {

        Buffer Certificate::serialize() const
        {
            Buffer ret;

            ret.second = certificateLen + sizeof(certificateLen);

            //alloc memory
            ret.first = new(nothrow) uint8_t[ret.second];
            if (!ret.first)
            {
                throw runtime_error("no memory for data");
            }

            //copy cert length
            memcpy(ret.first, &certificateLen, sizeof(certificateLen));

            //copy certificate field to payload
            memcpy(ret.first + sizeof(certificateLen), &certificate[0], certificateLen);

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
                memset(&ret->certificateLen, 0, sizeof(ret->certificateLen));
                memcpy(&ret->certificateLen, buffer, sizeof(ret->certificateLen));

                ret->certificate = new char[ret->certificateLen];
                memset(ret->certificate, 0, ret->certificateLen);
                memcpy(ret->certificate, buffer + sizeof(ret->certificateLen), ret->certificateLen);

            }
            else
            {
                ret->certificateLen = length;
                ret->certificate = new char[ret->certificateLen];
                memset(ret->certificate, 0, ret->certificateLen);
                memcpy(ret->certificate, buffer, ret->certificateLen);
            }
            return ret;
        }

        string Certificate::getCertificate() const noexcept
        {
            char *c = new(nothrow) char[certificateLen + 1];
            memset(c, 0, certificateLen + 1);
            memcpy(c, certificate, certificateLen);
            string ret(c);
            delete [] c;
            return ret;
        }

        void Certificate::setCertificate(const string &certificate) noexcept
        {
            certificateLen = certificate.size();
            this->certificate = new char [certificateLen];
            memset(this->certificate, 0, certificateLen);
            memcpy(this->certificate, &certificate[0], certificateLen);
        }

    }
}
#pragma clang diagnostic pop