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

#include <memory>

#include <hgardenpi-protocol/constants.hpp>

namespace hgardenpi::protocol
{
    inline namespace v2
    {
        using std::shared_ptr;

        class Package;

        /**
         * Head of data
         */
#pragma pack(push, n)
        struct Head final
        {
            /**
             * @brief Shared pointer of Head
             */
            typedef shared_ptr<Head> Ptr;

            /**
             * @brief Protocol version
             */
            uint8_t version = 0x00;
            /**
             * @brief Flags of transmission
             */
            uint8_t flags = NOT_SET;
            /**
             * @brief Transmission id
             */
            uint8_t id = 0;
            /**
             * @brief Data length
             */
            uint8_t length = 0;
            /**
             * @brief Payload data
             */
            uint8_t *payload = nullptr;
            /**
             * @brief CRC16 XMODEM calculate with version + flags + id + length + payload
             */
            uint16_t crc16 = 0;

            inline ~Head()
            {
                if (payload)
                {
                    delete[] payload;
                    payload = nullptr;
                }
            }

            /**
             * @brief Return payload in HEX format
             * @return sting HEX format
             */
            [[nodiscard]] std::string getHexPayload() const noexcept;

            /**
             * @brief Deserialize from buffer to Aggregation
             * @param chunkOfPackage if package is split more set de current package
             * @return new instance of Package null if something goes wrong, to deallocate
             * @throw exception if there are some memory error
             */
            [[nodiscard]] Package * deserialize(uint8_t chunkOfPackage = 0) const;
        };

        typedef std::vector<Head::Ptr> Heads;
#pragma pack(pop)
    }
}
