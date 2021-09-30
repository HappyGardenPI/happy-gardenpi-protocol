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
// Created by Antonio Salsi on 17/08/21.
//

#pragma once

#define HGARDENPI_PROTOCOL_SETTER(field, fieldLength)  \
fieldLength = field.size(); \
this->field = new char [fieldLength]; \
memset(this->field, 0, fieldLength); \
memcpy(this->field, &field[0], fieldLength);

#define HGARDENPI_PROTOCOL_GETTER(field, fieldLength)  \
char *c = new(nothrow) char[fieldLength + 1]; \
memset(c, 0, fieldLength + 1); \
memcpy(c, field, fieldLength); \
string ret(c); \
delete[] c; \
return ret;

#include <cstdint>

#include <hgardenpi-protocol/constants.hpp>

namespace hgardenpi::protocol
{
    inline namespace v1
    {

        /**
         * @brief base package class
         */
#pragma pack(push, n)
        struct Package
        {
            virtual inline ~Package() = default;

            /**
             * @brief Serialize self to buffer
             * @param buffer of data
             * @return self serialized
             */
            [[nodiscard]] virtual Buffer serialize() const = 0;
        };
#pragma pack(pop)
    }
}
