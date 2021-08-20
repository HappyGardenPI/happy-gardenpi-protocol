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
         * Add data to base Head whit SYN information
         * @param Head::Ptr allocated and semi filled structure
         * @param flag type of structure
         * @param t pointer to structure
         */
         template<typename T>
        static void encodeFlag(Head::Ptr &head, Flags flag, const T *t);

        Head::Ptr decode(const uint8_t *data)
        {
            //initialize default return value
            Head::Ptr ret(new (nothrow) Head{
                .version = static_cast<uint8_t>((data[0] & 0x80) >> 0x07),
                .flags = static_cast<uint8_t>(data[0] & 0x7F),
                .id = static_cast<uint8_t>(data[1]),
                .length = static_cast<uint8_t>(data[2])
            });
            if (ret == nullptr)
            {
                throw runtime_error("no memory for head");
            }

            //check max linit of value
            if (ret->flags > 0xE0)
            {
                throw runtime_error("head flags out of range or more packages set");
            }

            //copy payload from data
            memcpy(ret->payload, &data[2], ret->length);

            //copy crc16 from data
            ret->crc16 = static_cast<uint16_t>((data[ret->length + 4] << 0x08) | data[ret->length + 3]);

            //calculate crc16 from data received
            const uint dataLessCrc16Length = ret->length + 3;
            const uint8_t * dataLessCrc16 = new (nothrow) uint8_t[dataLessCrc16Length];

            memcpy((void *) dataLessCrc16, data, dataLessCrc16Length);
            uint16_t crc16Calc = CRC::Calculate(dataLessCrc16, dataLessCrc16Length, CRC::CRC_16_XMODEM());
            delete[] dataLessCrc16;

            //check crc16 send with that calculate
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
            Head::Ptr ret(new (nothrow) Head{
                .version = 0,
                .flags = additionalFags > NOT_SET ? additionalFags : NOT_SET,
                .id = 0,
                .length = 0
            });
            if (ret == nullptr)
            {
                throw runtime_error("no memory for head");
            }

            //set payload to 0
            memset(ret->payload, 0, PACKAGE_MAX_PAYLOAD_SIZE);

            //check which child package was packaged
            if (auto ptr = dynamic_cast<Aggregation *>(package); ptr) //is Flags::AGG package
            {
                encodeFlag(ret, AGG, ptr);
            }
            else if (auto ptr = dynamic_cast<Certificate *>(package); ptr) //is Flags::CRT package
            {
                encodeFlag(ret, CRT, ptr);
            }
            else if (dynamic_cast<Finish *>(package)) //is Flags::FIN package
            {
                //add package flag
                ret->flags |= FIN;
            }
            else if (auto ptr = dynamic_cast<Station *>(package); ptr) //is Flags::STA package
            {
                encodeFlag(ret, STA, ptr);
            }
            else if (auto ptr = dynamic_cast<Synchro *>(package); ptr) //is Flags::SYN package
            {
                //check right serial size
                if (strlen(ptr->serial) > PACKAGE_MAX_SERIAL_SIZE)
                {
                    throw runtime_error("serial too long max 255 chars");
                }

                //add package flag
                ret->flags |= SYN;
                ret->length = strlen(ptr->serial);

                //copy serial to payload
                strncpy(reinterpret_cast<char *>(ret->payload), ptr->serial, ret->length);
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

        template<typename T>
        static void encodeFlag(Head::Ptr &head, Flags flag, const T *t)
        {
            //static_assert(is_base_of_v<Package, T>(head, t));

            //add package flag
            head->flags |= flag;

            //set length of package
            head->length = sizeof(T);

            //copy structure to payload
            memcpy(reinterpret_cast<void *>(head->payload), reinterpret_cast<const void *>(t), head->length);
        }
#pragma clang diagnostic pop

    }
}
