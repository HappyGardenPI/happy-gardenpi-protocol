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
    inline namespace v1
    {
        using std::string;

#pragma pack(push, n)
        /**
         * @brief Package for manage certificate, linked to Flags::CRT
         */
        struct Certificate final : public Package
        {

            /**
             * @brief data payload length
             */
            uint16_t length = 0;
            /**
             * @brief data payload
             */
            char *certificate = nullptr;

            inline ~Certificate() noexcept override
            {
                if (certificate)
                {
                    delete [] certificate;
                    certificate = nullptr;
                }
            }

            /**
             * Serialize self to buffer
             * @return self serialized
             */
            [[nodiscard]] Buffer serialize() const override;

            /**
             * @brief Deserialize from buffer to Certificate
             * @param buffer of data
             * @param length of data
             * @param chunkOfPackage number of chunk id  is split in more chunks
             * @return new instance of Certificate or nullptr if error, to deallocate
             */
            [[nodiscard]] static Certificate * deserialize(const uint8_t *buffer, uint8_t length , uint8_t chunkOfPackage);

            /**
             * @brief Get certificate
             * @return certificate
             */
            [[maybe_unused]] [[nodiscard]] string getCertificate() const noexcept;

            /**
             * @brief Set certificate
             * @param certificate
             */
            [[maybe_unused]] void setCertificate(const string &certificate) noexcept;

            /**
             * @brief Set certificate
             * @param certificate
             */
            [[maybe_unused]] inline void setCertificate(const string &&certificate) noexcept
            {
                setCertificate(certificate);
            }
        };
#pragma pack(pop)
    }
}

#pragma clang diagnostic pop