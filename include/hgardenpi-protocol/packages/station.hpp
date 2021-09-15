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
             * @brief name of station
             */
            string name;
            /**
             * @brief description of station
             */
             string description;
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
        };
#pragma pack(pop)
    }
}
