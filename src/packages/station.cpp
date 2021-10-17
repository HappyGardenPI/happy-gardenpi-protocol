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

#include "hgardenpi-protocol/packages/station.hpp"

#include <stdexcept>
#include <memory>
#include <cstring>
#include <limits>
using namespace std;

#include "hgardenpi-protocol/constants.hpp"

namespace hgardenpi::protocol
{
    inline namespace v2
    {

        string Station::getName() const noexcept
        {
            HGARDENPI_PROTOCOL_GETTER(name, nameLen)
        }

        void Station::setName(const string &name) noexcept
        {
            HGARDENPI_PROTOCOL_SETTER(name, nameLen)
        }

        string Station::getDescription() const noexcept
        {
            HGARDENPI_PROTOCOL_GETTER(description, descriptionLen)
        }

        void Station::setDescription(const string &description) noexcept
        {
            HGARDENPI_PROTOCOL_SETTER(description, descriptionLen)
        }

        Buffer Station::serialize() const
        {

            uint8_t *buf = nullptr;
            size_t size = 0;

            //calculate size fo allocate buffer
            size += sizeof(uint8_t); //id
            size += sizeof(uint8_t); //nameLen
            if (name && nameLen > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
            {
                size += static_cast<int>(numeric_limits<uint8_t>::max());
            } else
            {
                size += nameLen;
            }
            size += sizeof(bool); //name
            size += sizeof(uint8_t); //descriptionLen
            if (description && descriptionLen > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
            {
                size += static_cast<int>(numeric_limits<uint8_t>::max());
            } else
            {
                size += descriptionLen;
            }
            size += sizeof(bool); //description

            size += sizeof(uint8_t); //relayNumber
            size += sizeof(uint32_t); //wateringTime

            size += sizeof(bool); //wateringTimeLeft
            size += sizeof(uint32_t); //weight
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

            memcpy(buf + size, &nameLen, sizeof(uint8_t));
            size += sizeof(uint8_t);

            if (name)
            {
                if (name && nameLen > static_cast<uint8_t>(numeric_limits<uint8_t>::max()))
                {
                    memcpy(buf + size, name, static_cast<uint8_t>(numeric_limits<uint8_t>::max()));
                    size += static_cast<uint8_t>(numeric_limits<uint8_t>::max());
                } else
                {
                    memcpy(buf + size, name, nameLen);
                    size += nameLen * sizeof(uint8_t);
                }
            }

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

            memcpy(buf + size, &relayNumber, sizeof(uint8_t));
            size += sizeof(uint8_t);

            memcpy(buf + size, &wateringTime, sizeof(uint32_t));
            size += sizeof(uint32_t);

            memcpy(buf + size, &wateringTimeLeft, sizeof(uint32_t));
            size += sizeof(uint32_t);

            memcpy(buf + size, &weight, sizeof(uint16_t));
            size += sizeof(uint16_t);

            memcpy(buf + size, &status, sizeof(status));

            return {shared_ptr<uint8_t []>(buf), size};
        }

        Station *Station::deserialize(const uint8_t *buffer, uint8_t, uint8_t)
        {
            return nullptr;
        }
    }
}