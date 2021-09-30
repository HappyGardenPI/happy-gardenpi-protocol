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
#include <hgardenpi-protocol/constants.hpp>

#include <string>

namespace hgardenpi::protocol
{
    inline namespace v1
    {

        using std::string;

        /**
         * @brief Package for manage aggregation, linked to Flags::STA
         */
#pragma pack(push, n)
        struct Station final : public Package
        {
            /**
            * @brief id in db
            */
            uint32_t id = 0;

            /**
            * @brief name length
            */
            uint16_t nameLen = 0;
            /**
             * @brief name of station
             */
            char *name = nullptr;
            /**
            * @brief description length
            */
            uint16_t descriptionLen = 0;
            /**
             * @brief description of station
             */
            char *description = nullptr;
            /**
             * @brief relay number association
             */
            uint8_t relayNumber = 0;
            /**
             * @brief watering time in minutes
             */
            uint32_t wateringTime = 0;
            /**
             * @brief watering time left in minutes
             * @note if greater than 0 the station running
             */
            uint32_t wateringTimeLeft = 0;
            /**
             * @brief for manage order of execution lighter is first then weightier
             */
            uint16_t weight = 0;
            /**
             * @brief status of station
             */
            Status status = Status::ACTIVE;

            inline ~Station() override
            {
                if (name)
                {
                    delete[] name;
                    name = nullptr;
                }
                if (description)
                {
                    delete[] description;
                    description = nullptr;
                }
            }

            /**
             * @brief Get name
             * @return msg
             */
            [[maybe_unused]] [[nodiscard]] string getName() const noexcept;

            /**
             * @brief Set name
             * @param name
             */
            [[maybe_unused]] void setName(const string &name) noexcept;

            /**
             * @brief Set name
             * @param name
             */
            [[maybe_unused]] inline void setName(const string &&name) noexcept
            {
                setName(name);
            }

            /**
             * @brief Get description
             * @return msg
             */
            [[maybe_unused]] [[nodiscard]] string getDescription() const noexcept;

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
             * Serialize self to buffer
             * @return self serialized
             */
            [[nodiscard]] Buffer serialize() const override;

            /**
             * @brief Deserialize from buffer to Station
             * @param buffer of data
             * @return new instance of Aggregation or nullptr if error, to deallocate
             */
            [[nodiscard]] static Station * deserialize(const uint8_t *buffer, uint8_t, uint8_t);
        };
#pragma pack(pop)
    }
}

#pragma clang diagnostic pop