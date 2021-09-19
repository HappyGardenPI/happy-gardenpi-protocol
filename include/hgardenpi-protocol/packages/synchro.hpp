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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"

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
         * @brief Synchro package utilize for init communication, linked to Flags::SYN
         */
#pragma pack(push, n)
        struct Synchro final : public Package
        {
            /**
             * @brief data payload length
             */
            uint16_t length = 0;

            /**
             * @brief serial of device
             */
            char *serial = nullptr;

            inline ~Synchro() noexcept override
            {
                if (serial)
                {
                    delete[] serial;
                    serial = nullptr;
                }
            }

            /**
 * @brief Get msg
 * @return msg
 */
            [[maybe_unused]] [[nodiscard]] string getSerial() const noexcept;

            /**
             * @brief Set serial
             * @param serial
             */
            [[maybe_unused]] void setSerial(const string &serial) noexcept;

            /**
             * @brief Set serial
             * @param serial
             */
            [[maybe_unused]] inline void setSerial(const string &&serial) noexcept
            {
                setSerial(serial);
            }

            /**
             * @brief Deserialize from buffer to Synchro
             * @param buffer of data
             * @return new instance of Aggregation or nullptr if error, to deallocate
             */
            [[nodiscard]] static Synchro * deserialize(const uint8_t *buffer, uint8_t, uint8_t) noexcept;

            /**
             * Serialize self to buffer
             * @return self serialized
             */
            [[nodiscard]] Buffer serialize() const override;
        };
#pragma pack(pop)
    }
}

#pragma clang diagnostic pop