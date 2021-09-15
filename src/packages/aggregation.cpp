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

#include "hgardenpi-protocol/packages/aggregation.hpp"

#include <limits>
#include <new>
#include <stdexcept>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
using namespace std;

#include "hgardenpi-protocol/constants.hpp"

namespace hgardenpi::protocol
{
    inline namespace v1
    {
        static inline string bufferToString(const char *buffer, size_t size)
        {
            string ret;
            for (size_t i = 0; i < size; i++)
            {
                ret += buffer[i];
            }
            return ret;
        }

        [[nodiscard]] string Aggregation::getDescription() const noexcept
        {
            return move(bufferToString(description, descriptionSize));
        }

        [[nodiscard]] string Aggregation::getStart() const noexcept
        {
            return move(bufferToString(start, startSize));
        }

        [[nodiscard]] string Aggregation::getEnd() const noexcept
        {
            return move(bufferToString(end, endSize));
        }


        Buffer Aggregation::serialize() const
        {
            uint8_t *buf = nullptr;
            size_t size = 0;

            //calculate size fo allocate buffer
            size += sizeof(uint8_t); //id
            size += sizeof(uint8_t); //descriptionSize
            if (description && descriptionSize > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
            {
                size += static_cast<int>(numeric_limits<uint8_t>::max());
            } else
            {
                size += descriptionSize;
            }
            size += sizeof(bool); //manual
            size += sizeof(Schedule); //schedule
            size += sizeof(uint8_t); //startSize
            if (start && startSize > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
            {
                size += static_cast<int>(numeric_limits<uint8_t>::max());
            } else
            {
                size += startSize;
            }
            size += sizeof(endSize); //endSize
            if (end && endSize > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
            {
                size += static_cast<int>(numeric_limits<uint8_t>::max());
            } else
            {
                size += endSize;
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
            memcpy(buf + size, &descriptionSize, sizeof(uint8_t));
            size += sizeof(uint8_t);
            if (descriptionSize)
            {
                if (description && descriptionSize > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
                {
                    memcpy(buf + size, description, static_cast<uint8_t>(numeric_limits<uint8_t>::max()));
                    size += static_cast<uint8_t>(numeric_limits<uint8_t>::max());
                } else
                {
                    memcpy(buf + size, description, descriptionSize);
                    size += descriptionSize * sizeof(uint8_t);
                }
            }
            memcpy(buf + size, &manual, sizeof(bool));
            size += sizeof(bool);
            memcpy(buf + size, &schedule, sizeof(schedule));
            size += sizeof(schedule);
            memcpy(buf + size, &startSize, sizeof(uint8_t));
            size += sizeof(uint8_t);
            if (startSize)
            {
                if (start && startSize > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
                {
                    memcpy(buf + size, start, static_cast<uint8_t>(numeric_limits<uint8_t>::max()));
                    size += static_cast<uint8_t>(numeric_limits<uint8_t>::max());
                } else
                {
                    memcpy(buf + size, start, startSize);
                    size += startSize * sizeof(uint8_t);
                }
            }
            memcpy(buf + size, &endSize, sizeof(uint8_t));
            size += sizeof(uint8_t);
            if (endSize)
            {
                if (end && endSize > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
                {
                    memcpy(buf + size, end, static_cast<uint8_t>(numeric_limits<uint8_t>::max()));
                    size += static_cast<uint8_t>(numeric_limits<uint8_t>::max());
                } else
                {
                    memcpy(buf + size, end, endSize);
                    size += endSize * sizeof(uint8_t);
                }
            }
            memcpy(buf + size, &sequential, sizeof(bool));
            size += sizeof(bool);
            memcpy(buf + size, &weight, sizeof(uint16_t));
            size += sizeof(uint16_t);
            memcpy(buf + size, &status, sizeof(status));

            return {buf, size};
        }

        Aggregation * Aggregation::deserialize(const uint8_t *buffer) noexcept
        {
            if (!buffer)
            {
                return nullptr;
            }
            size_t size = 0;

            auto *ret = new Aggregation;
            ret->id = buffer[size];
            size += sizeof(uint8_t); //id
            ret->descriptionSize = buffer[size];
            size += sizeof(uint8_t); //descriptionSize
            if (ret->descriptionSize > 0)
            {
                ret->description = new char[ret->descriptionSize];
                memset(ret->description, 0, ret->descriptionSize);
                memcpy(ret->description, buffer + size, ret->descriptionSize);
                size += ret->descriptionSize * sizeof(uint8_t); //description
            }
            ret->manual = buffer[size];
            size += sizeof(bool); //manual
            memcpy(&ret->schedule, buffer + size, sizeof(schedule));
            size += sizeof(Schedule); //Schedule
            ret->startSize = buffer[size];
            size += sizeof(uint8_t); //startSize
            if (ret->startSize > 0)
            {
                ret->start = new char[ret->startSize];
                memset(ret->start, 0, ret->startSize);
                memcpy(ret->start, buffer + size, ret->startSize);
                size += ret->startSize * sizeof(uint8_t); //start
            }
            ret->endSize = buffer[size];
            size += sizeof(uint8_t); //endSize
            if (ret->endSize > 0)
            {
                ret->end = new char[ret->endSize];
                memset(ret->end, 0, ret->endSize);
                memcpy(ret->end, buffer + size, ret->endSize);
                size += ret->endSize * sizeof(uint8_t); //end
            }
            ret->sequential = buffer[size];
            size += sizeof(uint8_t); //sequential
            ret->weight = buffer[size];
            size += sizeof(uint8_t); //weight
            memcpy(&ret->status, buffer + size, sizeof(Status));

            return ret;
        }

        void Aggregation::setDescription(const string &description) noexcept
        {
            descriptionSize = description.size();
            this->description = new char [descriptionSize];
            memset(this->description, 0, descriptionSize);
            memcpy(this->description, &description[0], descriptionSize);
        }

        void Aggregation::setStart(const string &start) noexcept
        {
            startSize = start.size();
            this->start = new char [startSize];
            memset(this->start, 0, startSize);
            memcpy(this->start, &start[0], startSize);
        }

        void Aggregation::setEnd(const string &end) noexcept
        {
            endSize = end.size();
            this->end = new char [endSize];
            memset(this->end, 0, endSize);
            memcpy(this->end, &end[0], endSize);
        }
    }
}
#pragma clang diagnostic pop