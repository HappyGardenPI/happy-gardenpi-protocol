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

#pragma once

#include <string>

#include <hgardenpi-protocol/packages/package.hpp>
#include <hgardenpi-protocol/constants.hpp>

namespace hgardenpi::protocol
{
    inline namespace v1
    {
        using std::string;


        /**
         * @brief Package for finish communication, linked to Flags::FIN
         * @note not contain field
         */
#pragma pack(push, n)

        struct Finish final : public Package
        {
        public:

            /**
             * Serialize self to buffer
             * @return self serialized
             */
            [[nodiscard]] inline Buffer serialize() const override { return {nullptr, 0}; }

            /**
             * @brief Deserialize from buffer to Finish
             * @param buffer of data
             * @return new instance of Finish or nullptr if error, to deallocate
             */
            [[nodiscard]] static inline Finish * deserialize(const uint8_t *buffer, uint8_t, uint8_t) noexcept { return new Finish; }

        };

#pragma pack(pop)
    }
}
