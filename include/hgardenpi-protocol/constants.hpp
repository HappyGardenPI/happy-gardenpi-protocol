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

#include <cstdlib>

namespace hgardenpi::protocol
{
    inline namespace v1
    {

        /**
         * Flags used in Head
         */
        enum Flags : uint8_t
        {
            //only one flags/packages
            NOT_SET = 0x00,
            /**
             * @brief Synchronization package for start communication
             * @note this flag can contain only one flag/package
             */
            SYN = 0x01,
            /**
             * @brief Certificare package contain certificate for enable point to point communication
             * @note this flag can contain only one flag/package
             */
            CRT = 0x02,
            /**
             * @brief Aggregation package contain info about it
             * @note this flag can contain only one flag/package
             */
            AGG = 0x04,
            /**
             * @brief Station package contain info about it
             * @note this flag can contain only one flag/package
             */
            STA = 0x08,
            /**
             * @brief End package, empty package for end communication
             * @note this flag can contain only one flag/package
             */
            FIN = 0x10,

            //flags
            /**
             * @brief Partial package, empty package for end communication
             * @note this flag can be added to flag/package to decoration of the information passed
             */
            PAR = 0x20,
            /**
             * @brief End package, empty package for end communication
             * @note this flag can be added to flag/package to decoration of the information passed
             */
            ACK = 0x40,
        };

        /**
         * @brief Status of an element in the project
         */
        enum class Status : uint8_t
        {
            /**
             * @brief element not active
             */
            UNACTIVE = 0,
            /**
             * @brief element active
             */
            ACTIVE,
            /**
             * @brief element error
             */
            ERROR,
        };

        /**
         * @brief max payload size
         */
        constexpr const inline uint8_t PACKAGE_MAX_PAYLOAD_SIZE = 255;

        /**
         * @brief max serial size
         */
        constexpr const inline uint8_t PACKAGE_MAX_SERIAL_SIZE = 32;

    }
}