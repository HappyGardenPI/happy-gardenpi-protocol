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
// Created by Antonio Salsi on 11/09/21.
//


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"

#include "hgardenpi-protocol/packages/aggregation.hpp"

#include <limits>
#include <new>
#include <stdexcept>
#include <cstring>
using namespace std;

#include "hgardenpi-protocol/constants.hpp"

namespace hgardenpi::protocol
{
    inline namespace v2
    {
        [[nodiscard]] string Aggregation::getDescription() const noexcept
        {
            HGARDENPI_PROTOCOL_GETTER(description, descriptionLen)
        }

        [[nodiscard]] string Aggregation::getStart() const noexcept
        {
            HGARDENPI_PROTOCOL_GETTER(start, startLen)
        }

        [[nodiscard]] string Aggregation::getEnd() const noexcept
        {
            HGARDENPI_PROTOCOL_GETTER(end, endLen)
        }

        void Aggregation::setDescription(const string &description) noexcept
        {
            HGARDENPI_PROTOCOL_SETTER(description, descriptionLen)
        }

        void Aggregation::setStart(const string &start) noexcept
        {
            HGARDENPI_PROTOCOL_SETTER(start, startLen)
        }

        void Aggregation::setEnd(const string &end) noexcept
        {
            HGARDENPI_PROTOCOL_SETTER(end, endLen)
        }

        Buffer Aggregation::serialize() const
        {
            uint8_t *buf = nullptr;
            size_t size = 0;

            //calculate size fo allocate buffer
            size += sizeof(uint8_t); //id
            size += sizeof(uint8_t); //descriptionSize
            if (description && descriptionLen > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
            {
                size += static_cast<int>(numeric_limits<uint8_t>::max());
            } else
            {
                size += descriptionLen;
            }
            size += sizeof(bool); //manual
            size += sizeof(Schedule); //schedule
            size += sizeof(uint8_t); //startSize
            if (start && startLen > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
            {
                size += static_cast<int>(numeric_limits<uint8_t>::max());
            } else
            {
                size += startLen;
            }
            size += sizeof(endLen); //endSize
            if (end && endLen > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
            {
                size += static_cast<int>(numeric_limits<uint8_t>::max());
            } else
            {
                size += endLen;
            }
            size += sizeof(bool); //sequential
            size += sizeof(uint16_t); //weight
            size += sizeof(Status); //status

            //alloc buffer
            buf = new(nothrow) uint8_t[size];
            if (!buf)
            {
                throw runtime_error("no memory for serialize");
            }
            memset(buf, 0, size);


            size = 0;
            memcpy(buf + size, &id, sizeof(uint8_t));
            size += sizeof(uint8_t);
            memcpy(buf + size, &descriptionLen, sizeof(uint8_t));
            size += sizeof(uint8_t);
            if (descriptionLen)
            {
                if (description && descriptionLen > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
                {
                    memcpy(buf + size, description, static_cast<uint8_t>(numeric_limits<uint8_t>::max()));
                    size += static_cast<uint8_t>(numeric_limits<uint8_t>::max());
                } else
                {
                    memcpy(buf + size, description, descriptionLen);
                    size += descriptionLen * sizeof(uint8_t);
                }
            }
            memcpy(buf + size, &manual, sizeof(bool));
            size += sizeof(bool);
            memcpy(buf + size, &schedule, sizeof(schedule));
            size += sizeof(schedule);
            memcpy(buf + size, &startLen, sizeof(uint8_t));
            size += sizeof(uint8_t);
            if (startLen)
            {
                if (start && startLen > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
                {
                    memcpy(buf + size, start, static_cast<uint8_t>(numeric_limits<uint8_t>::max()));
                    size += static_cast<uint8_t>(numeric_limits<uint8_t>::max());
                } else
                {
                    memcpy(buf + size, start, startLen);
                    size += startLen * sizeof(uint8_t);
                }
            }
            memcpy(buf + size, &endLen, sizeof(uint8_t));
            size += sizeof(uint8_t);
            if (endLen)
            {
                if (end && endLen > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
                {
                    memcpy(buf + size, end, static_cast<uint8_t>(numeric_limits<uint8_t>::max()));
                    size += static_cast<uint8_t>(numeric_limits<uint8_t>::max());
                } else
                {
                    memcpy(buf + size, end, endLen);
                    size += endLen * sizeof(uint8_t);
                }
            }
            memcpy(buf + size, &sequential, sizeof(bool));
            size += sizeof(bool);
            memcpy(buf + size, &weight, sizeof(uint16_t));
            size += sizeof(uint16_t);
            memcpy(buf + size, &status, sizeof(status));

            return {shared_ptr<uint8_t []>(buf), size};
        }

        Aggregation * Aggregation::deserialize(const uint8_t *buffer, uint8_t len, uint8_t)
        {
            if (!buffer)
            {
                return nullptr;
            }
            size_t size = 0;

            //cout << stringHexToString(buffer, len) << endl;

            auto *ret = new Aggregation;
            if (!ret)
            {
                throw runtime_error("no memory for aggregation");
            }
            ret->id = buffer[size];
            size += sizeof(uint8_t); //id
            ret->descriptionLen = buffer[size];
            size += sizeof(uint8_t); //descriptionSize
            if (ret->descriptionLen > 0)
            {
                ret->description = new char[ret->descriptionLen];
                memset(ret->description, 0, ret->descriptionLen);
                memcpy(ret->description, buffer + size, ret->descriptionLen);
                size += ret->descriptionLen * sizeof(uint8_t); //description
            }
            ret->manual = buffer[size];
            size += sizeof(bool); //manual
            memcpy(&ret->schedule, buffer + size, sizeof(schedule));
            size += sizeof(Schedule); //Schedule
            ret->startLen = buffer[size];
            size += sizeof(uint8_t); //startSize
            if (ret->startLen > 0)
            {
                ret->start = new char[ret->startLen];
                memset(ret->start, 0, ret->startLen);
                memcpy(ret->start, buffer + size, ret->startLen);
                size += ret->startLen * sizeof(uint8_t); //start
            }
            ret->endLen = buffer[size];
            size += sizeof(uint8_t); //endSize
            if (ret->endLen > 0)
            {
                ret->end = new char[ret->endLen];
                memset(ret->end, 0, ret->endLen);
                memcpy(ret->end, buffer + size, ret->endLen);
                size += ret->endLen * sizeof(uint8_t); //end
            }
            ret->sequential = buffer[size];
            size += sizeof(uint8_t); //sequential
            ret->weight = buffer[size];
            size += sizeof(uint8_t); //weight
            memcpy(&ret->status, buffer + size, sizeof(Status));

            return ret;
        }
    }
}
#pragma clang diagnostic pop