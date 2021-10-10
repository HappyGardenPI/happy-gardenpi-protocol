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

#include <hgardenpi-protocol/packages/package.hpp>

#include <utility>
#include <string>

namespace hgardenpi::protocol
{
    inline namespace v1
    {

        using std::string;

        /**
         * @brief Package for manage aggregation, linked to Flags::AGG
         */
#pragma pack(push, n)
        struct Aggregation final : public Package
        {
            /**
             * @brief id in db
             */
            uint32_t id = 0;
            /**
             * @brief length of description
             */
            uint8_t descriptionLen = 0;
            /**
             * @brief description of aggregation
             */
            char *description = nullptr;
            /**
             * @brief manual check if the aggregation start automatically or manually by follow fields
             */
            bool manual = true;
            /**
             * @brief scheduling data info
             */
            struct Schedule
            {
                /**
                 * @brief minute, values allowed 0 - 59
                 */
                uint8_t minute = 0; //0 - 59 or NOT_SET

                /**
                 * @brief minute, values allowed 0 - 23 or NOT_SET
                 */
                uint8_t hour = 0; //0 - 23 or NOT_SET

                /**
                 * @brief days, values allowed 0x01 - 0x7F or NOT_SET
                 */
                uint8_t days = 0x7F; //byte contains day enabled
            }
            /**
             * @brief Instance of schedule data
             */
            schedule;
            /**
             * @brief length of start
             */
            uint8_t startLen = 0;
            /**
             * @brief start scheduling period if enhanced
             */
            char *start = nullptr;
            /**
             * @brief length of end
             */
            uint8_t endLen = 0;
            /**
             * @brief end scheduling period if enhanced
             */
            char *end = nullptr;
            /**
             * @brief If true execute sequentially the station otherwise execute all station at the same time
             * @note not implemented in this version, may be in next version
             */
            bool sequential = true;
            /**
             * @brief for manage order of execution lighter is first then weightier
             */
            uint16_t weight = 0;
            /**
             * @brief status of station
             */
            Status status = Status::ACTIVE;

            inline ~Aggregation() noexcept override
            {
                if (description)
                {
                    delete[] description;
                    description = nullptr;
                }
                if (start)
                {
                    delete[] start;
                    start = nullptr;
                }
                if (end)
                {
                    delete[] end;
                    end = nullptr;
                }
            }

            /**
             * @brief Set description
             * @param description
             */
            [[maybe_unused]] void setDescription(const string &description) noexcept;

            /**
             * @brief Set description
             * @param description
             */
            [[maybe_unused]] inline void setDescription(const string &&description) noexcept
            {
                setDescription(description);
            }

            /**
             * @brief Set start
             * @param start
             */
            [[maybe_unused]] void setStart(const string &start) noexcept;

            /**
             * @brief Set start
             * @param start
             */
            [[maybe_unused]] inline void setStart(const string &&start) noexcept
            {
                setStart(start);
            }

            /**
             * @brief Set end
             * @param end
             */
            [[maybe_unused]] void setEnd(const string &end) noexcept;

            /**
             * @brief Set end
             * @param end
             */
            [[maybe_unused]] inline void setEnd(const string &&end) noexcept
            {
                setEnd(end);
            }

            /**
             * @brief Get description
             * @return description
             */
            [[maybe_unused]] [[nodiscard]] string getDescription() const noexcept;

            /**
             * @brief Get start
             * @return start
             */
            [[maybe_unused]] [[nodiscard]] string getStart() const noexcept;

            /**
             * @brief Get end
             * @return end
             */
            [[maybe_unused]] [[nodiscard]] string getEnd() const noexcept;

            /**
             * @brief Serialize self to buffer
             * @param buffer of data
             * @return self serialized
             */
            [[nodiscard]] Buffer serialize() const override;

            /**
             * @brief Deserialize from buffer to Aggregation
             * @param buffer of data
             * @param length of data
             * @param chunkOfPackage number of chunk id  is split in more chunks
             * @return new instance of Aggregation or nullptr if error, to deallocate
             * @throw exception if there are some memory error
             */
            [[nodiscard]] static Aggregation * deserialize(const uint8_t *buffer, uint8_t length, uint8_t chunkOfPackage);
        };
#pragma pack(pop)
    }
}

#pragma clang diagnostic pop