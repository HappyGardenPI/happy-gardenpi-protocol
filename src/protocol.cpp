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
#include <hgardenpi-protocol/packages/station.hpp>
#include <hgardenpi-protocol/packages/synchro.hpp>

namespace hgardenpi::protocol
{
    inline namespace v1
    {


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
            if (ret->flags > 31)
            {
                throw runtime_error("head flags out of range");
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

        vector<Head::Ptr> encode(const vector<Package *> &packages)
        {
            if (packages.empty())
            {
                throw runtime_error("packages empty");
            }
            vector<Head::Ptr> ret;
            vector<uint8_t *> payload;


            for(auto it : packages)
            {
                if (dynamic_cast<Synchro *>(it))
                {
                    cout << "Synchro" << endl;
                }
                else if (dynamic_cast<Aggregation *>(it))
                {
                    cout << "Aggregation" << endl;
                }
                else if (dynamic_cast<Station *>(it))
                {
                    cout << "Station" << endl;
                }
                else
                {
                    throw runtime_error("class not child of Package");
                }
            }

            for(auto it : packages)
            {
                delete it;
            }
            return ret;
        }
    }
}
