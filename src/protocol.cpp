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
// Created by Antonio Salsi on 16/08/21.
//

#include <hgardenpi-protocol/protocol.hpp>

#include <stdexcept>
#include <iostream>
#include <memory>
using namespace std;

#include <hgardenpi-protocol/3thparts/CRC.h>

#include <hgardenpi-protocol/packages/aggregation.hpp>
#include <hgardenpi-protocol/packages/certificate.hpp>
#include <hgardenpi-protocol/packages/finish.hpp>
#include <hgardenpi-protocol/packages/station.hpp>
#include <hgardenpi-protocol/packages/synchro.hpp>

namespace hgardenpi::protocol
{
    inline namespace v1
    {

        /**
         * Add data to base Head whit FIN information
         * @param Head::Ptr allocated and semi filled structure
         */
        static void encodeFinish(Head::Ptr &head) noexcept;

        /**
         * Add data to base Head whit SYN information
         * @param Head::Ptr allocated and semi filled structure
         * @param synchro pointer to structure
         */
        static void encodeSynchro(Head::Ptr &head, const Synchro *synchro);

        Head::Ptr decode(const uint8_t *data)
        {
            Head::Ptr ret(new Head{
                .version = static_cast<uint8_t>((data[0] & 0x80) >> 0x07),
                .flags = static_cast<uint8_t>(data[0] & 0x7F),
                .id = static_cast<uint8_t>(data[1]),
                .length = static_cast<uint8_t>(data[2])
            });

            if (ret->version > 1)
            {
                throw runtime_error("head version out of range");
            }
            if (ret->flags > 0xE0)
            {
                throw runtime_error("head flags out of range or more packages set");
            }
            memcpy(ret->payload, &data[2], ret->length);
            ret->crc16 = static_cast<uint16_t>((data[ret->length + 4] << 0x08) | data[ret->length + 3]);

            const uint dataLessCrc16Length = ret->length + 3;
            const uint8_t * dataLessCrc16 = new (nothrow) uint8_t[dataLessCrc16Length];

            memcpy((void *) dataLessCrc16, data, dataLessCrc16Length);
            uint16_t crc16Calc = CRC::Calculate(dataLessCrc16, dataLessCrc16Length, CRC::CRC_16_XMODEM());
            delete[] dataLessCrc16;

            if (crc16Calc != ret->crc16)
            {
                throw runtime_error("crc not match");
            }
            return ret;
        }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
        Head::Ptr encode(Package * package, Flags additionalFags)
        {
            //check if package is null
            if (package == nullptr)
            {
                throw runtime_error("package null");
            }

            //prepare return head with common information
            Head::Ptr ret(new Head{
                .version = 0,
                .flags = additionalFags > NOT_SET ? additionalFags : NOT_SET,
                .id = 0,
                .length = 0
            });

            //set payload to 0
            memset(ret->payload, 0, PACKAGE_MAX_PAYLOAD_SIZE);

            //check which child package was packaged
            if (auto ptr = dynamic_cast<Aggregation *>(package); ptr)
            {
                cout << "Aggregation" << endl;
            }
            else if (auto ptr = dynamic_cast<Certificate *>(package); ptr)
            {
                cout << "Certificate" << endl;
            }
            else if (dynamic_cast<Finish *>(package)) //is FIN package
            {
                encodeFinish(ret);
            }
            else if (auto ptr = dynamic_cast<Station *>(package); ptr)
            {
                cout << "Station" << endl;
            }
            else if (auto ptr = dynamic_cast<Synchro *>(package); ptr) //is SYN package
            {
                encodeSynchro(ret, ptr);
            }
            else
            {
                throw runtime_error("class not child of Package");
            }

            //calculate size of crc16 and alloc it
            size_t dataLessCrc16Length = sizeof(uint8_t) + sizeof(ret->id) + sizeof(ret->length) + (sizeof (uint8_t) * ret->length);
            const uint8_t * crc16 = new (nothrow) uint8_t[dataLessCrc16Length];

            //calculate crc16
            memcpy((void *) crc16, ret.get(), dataLessCrc16Length);
            ret->crc16 = CRC::Calculate(crc16, dataLessCrc16Length, CRC::CRC_16_XMODEM());
            delete[] crc16;

            //free package
            delete package;

            return ret;
        }
#pragma clang diagnostic pop

        inline void encodeFinish(Head::Ptr &head) noexcept
        {
            //add package flag
            head->flags |= FIN;
        }

        static void encodeSynchro(Head::Ptr &head, const Synchro *synchro)
        {
            //check right seial size
            if (strlen(synchro->serial) > PACKAGE_MAX_SERIAL_SIZE)
            {
                throw runtime_error("serial too long max 255 chars");
            }

            //add package flag
            head->flags |= SYN;

            //copy serial to payload
            strncpy(reinterpret_cast<char *>(head->payload), synchro->serial, strlen(synchro->serial));
        }
    }
}
