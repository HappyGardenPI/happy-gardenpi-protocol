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

#include <hgardenpi-protocol/packages/package.hpp>

#include <utility>
#include <string>

#include <hgardenpi-protocol/constants.hpp>

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
            uint8_t descriptionSize = 0;
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
            uint8_t startSize = 0;
            /**
             * @brief start scheduling period if enhanced
             */
            char *start = nullptr;
            /**
             * @brief length of end
             */
            uint8_t endSize = 0;
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

            [[nodiscard]] string getDescription() const noexcept;

            [[nodiscard]] string getStart() const noexcept;

            [[nodiscard]] string getEnd() const noexcept;

            /**
             * Serialize self to buffer
             * @return self serialized
             */
            [[nodiscard]] Buffer serialize() const;

            /**
             * Deserialize from buffer to Aggregation
             * @return new instance of Aggregation or nullptr if error, to deallocate
             */
            [[nodiscard]] static Aggregation * deserialize(const uint8_t *buffer) noexcept;
        };
#pragma pack(pop)
    }
}
