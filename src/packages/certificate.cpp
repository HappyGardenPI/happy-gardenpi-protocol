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

#include <iostream>
#include <hgardenpi-protocol/utilities/stringutils.hpp>
using namespace std;

namespace hgardenpi::protocol
{
    inline namespace v1
    {

        Buffer Certificate::serialize() const
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
            memcpy(ret.first.get() + sizeof(length), &certificate[0], length);

            //return Buffer
            return ret;
        }

        Certificate * Certificate::deserialize(const uint8_t *buffer, uint8_t length, uint8_t chunkOfPackage)
        {
            if (!buffer)
            {
                return nullptr;
            }
            auto cer = new (nothrow) Certificate;
            if (!cer)
            {
                throw runtime_error("no memory for cer");
            }

            cout << "deserialize 0 " << stringHexToString(reinterpret_cast<const uint8_t *>(buffer), length) << " " << to_string(length) << endl;

            if (chunkOfPackage == 0)
            {
                //set length of certificate and payload
                memset(&cer->length, 0, sizeof(cer->length));
                memcpy(&cer->length, buffer, sizeof(cer->length));

                cer->chunkLength = length - sizeof(cer->length);
                cer->certificate = new char[cer->chunkLength];
                memset(cer->certificate, 0, cer->chunkLength);
                memcpy(cer->certificate, buffer + sizeof(cer->length), cer->chunkLength);

                cout << "deserialize 1 " << stringHexToString(reinterpret_cast<const uint8_t *>(cer->certificate), cer->chunkLength) << "<<>>" << to_string(cer->chunkLength) << " " << to_string(chunkOfPackage) << endl;
            }
            else
            {
                cer->length = 0;
//                cer->length = length;
//                cer->certificate = new char[cer->length];
//                memset(cer->certificate, 0, cer->length);
//                memcpy(cer->certificate, buffer, cer->length);
//
//                cout << "deserialize 2 " << stringHexToString(reinterpret_cast<const uint8_t *>(cer->certificate), cer->length) << " " << to_string(cer->length) << " " << to_string(chunkOfPackage) << endl;
            }
            return cer;
        }

        string Certificate::getCertificate() const noexcept
        {
//            uint8_t s = length < HEAD_MAX_PAYLOAD_SIZE ? length : length - (chunkOfPackage * HEAD_MAX_PAYLOAD_SIZE);
//            char *c = new(nothrow) char[s];
//            memset(c, 0, s);
//            memcpy(c, certificate, s);
//            string ret(c);
//            delete[] c;
//            return ret;
            if (length > 0)
            {

            }
            HGARDENPI_PROTOCOL_GETTER(certificate, length)
        }

        void Certificate::setCertificate(const string &certificate) noexcept
        {
            HGARDENPI_PROTOCOL_SETTER(certificate, length)
        }

    }
}
#pragma clang diagnostic pop