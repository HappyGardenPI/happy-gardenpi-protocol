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

namespace hgardenpi::protocol
{
    inline namespace v2
    {
        using std::string;

#pragma pack(push, n)
        /**
         * @brief Package for manage data, linked to Flags::DAT
         */
        struct Data final : public Package
        {

            /**
             * @brief data payload length
             */
            uint16_t length = 0;
            /**
             * @brief payload
             */
            char *payload = nullptr;

            /**
             * @brief data payload
             */
            char *chunk = nullptr;
            /**
             * @brief chunk length
             */
            uint8_t chunkLength = 0;

            inline ~Data() noexcept override
            {
                if (payload)
                {
                    delete [] payload;
                    payload = nullptr;
                }

                if (chunk)
                {
                    delete [] chunk;
                    chunk = nullptr;
                }
            }

            /**
             * Serialize self to buffer
             * @return self serialized
             */
            [[nodiscard]] Buffer serialize() const override;

            /**
             * @brief Deserialize from buffer to Data
             * @param buffer of data
             * @param length of data
             * @param chunkOfPackage number of chunk id  is split in more chunks
             * @return new instance of Data or nullptr if error, to deallocate
             * @throw exception if there are some memory error
             */
            [[nodiscard]] static Data * deserialize(const uint8_t *buffer, uint8_t length , uint8_t chunkOfPackage);

            /**
             * @brief Get payload
             * @return payload
             */
            [[maybe_unused]] [[nodiscard]] string getPayload() const noexcept;

            /**
             * @brief Set payload
             * @param payload
             */
            [[maybe_unused]] void setPayload(const string &payload) noexcept;

            /**
             * @brief Set payload
             * @param payload
             */
            [[maybe_unused]] inline void setPayload(const string &&payload) noexcept
            {
                setPayload(payload);
            }

            /**
             * @brief Get chunk message
             * @return chunk
             */
            [[maybe_unused]] [[nodiscard]] string getChunk() const noexcept;
        };
#pragma pack(pop)
    }
}

#pragma clang diagnostic pop