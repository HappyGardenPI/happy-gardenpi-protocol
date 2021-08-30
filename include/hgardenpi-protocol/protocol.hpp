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
#include <tuple>

#include <hgardenpi-protocol/constants.hpp>
#include <hgardenpi-protocol/head.hpp>


namespace hgardenpi::protocol
{
    inline namespace v1
    {
        using std::vector;
        using std::tuple;

        struct Package;

        /**
         * Decode a buffer contain a Happy GardenPI Head
         * @param data buffer
         * @return Head instance
         * @throw runtime_exception if something goes wrong
         */
        [[maybe_unused]] Head::Ptr decode(const uint8_t *data);

         /**
          * Encode a buffer contain a Happy GardenPI Head
          * @param package package to send, it will be deleted automatically
          * @param additionalFags additional flags to decorate package
          * @return a vector of Head to send
          * @throw runtime_exception if something goes wrong
          */
         [[maybe_unused]]  vector<Head::Ptr> encode(Package * package, Flags additionalFags = NOT_SET);

         /**
          * Convert a head::Ptr to buffer ready to send
           * @param head head to send
          * @return uint8_t allocated buffer ready to send, to deallocate
          * @throw runtime_exception if something goes wrong
          */
         [[maybe_unused]] tuple<uint8_t *, size_t> fromHeadToBuffer(const Head::Ptr &head);

        /**
        * Convert a head::Ptr to buffer ready to send
         * @param head head to send
        * @return uint8_t allocated buffer ready to send, to deallocate
        * @throw runtime_exception if something goes wrong
        */
        [[maybe_unused]] inline tuple<uint8_t *, size_t> fromHeadToBuffer(const Head::Ptr &&head)
        {
            return move(fromHeadToBuffer(head));
        }
    }
}


#pragma clang diagnostic pop