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
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma once

#include <vector>

#include <hgardenpi-protocol/constants.hpp>
#include <hgardenpi-protocol/head.hpp>
#include <hgardenpi-protocol/config.h>


namespace hgardenpi::protocol
{
    inline namespace v1
    {
        using std::vector;
        using std::tuple;

        struct Package;

        /**
         * Get version of lib
         * @return return a tuple with version
         */
        inline tuple<uint8_t, uint8_t, uint8_t> fetVersion() noexcept
        {
            return {HGARDENPI_PROTOCOL_VER_MAJOR, HGARDENPI_PROTOCOL_VER_MINOR, HGARDENPI_PROTOCOL_VER_PATCH};
        }

        /**
         * Decode a buffer contain a Happy GardenPI Head
         * @param data buffer
         * @param size od data
         * @return Head instance
         * @throw runtime_exception if something goes wrong
         */
         Head::Ptr decode(const uint8_t *data);

         /**
          * Encode a buffer contain a Happy GardenPI Head
          * @param package package to send, it will be deleted automatically
          * @param additionalFags additional flags to decorate package
          * @return a vector of Head to send
          * @throw runtime_exception if something goes wrong
          */
         vector<Head::Ptr> encode(Package * package, Flags additionalFags = NOT_SET);

    }
}


#pragma clang diagnostic pop