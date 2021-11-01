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


#include  <utility>
#include  <stdexcept>

#include <hgardenpi-protocol/constants.hpp>
#include <hgardenpi-protocol/head.hpp>
#include <hgardenpi-protocol/packages/package.hpp>


namespace hgardenpi::protocol
{
    inline namespace v2
    {
        using std::pair;
        using std::runtime_error;

        struct Package;

        /**
         * Encode a buffer contain a Happy GardenPI Head
         * @param package package to send, it will be deleted automatically
         * @param additionalFags additional flags to decorate package
         * @return a vector of buffer to send
         * @throw runtime_exception if something goes wrong
         */
        [[maybe_unused]]  Buffers encode(Package *package, Flags additionalFags = NOT_SET);

        /**
        * Decode a buffer contain a Happy GardenPI Head
        * @param data buffer
        * @return Head instance
        * @throw runtime_exception if something goes wrong
        */
        [[maybe_unused]] Head::Ptr decode(const uint8_t *data);

        /**
        * Decode a buffer contain a Happy GardenPI Head
        * @param data buffer
        * @return Head instance
        * @throw runtime_exception if something goes wrong
        */
        [[maybe_unused]] inline Head::Ptr decode(const Buffer &data)
        {
            return decode(data.first.get());
        }

        /**
        * Decode first buffer of vector of buffer that contain a Happy GardenPI Head
        * @param data buffers
        * @return Head instance
        * @throw runtime_exception if something goes wrong
        */
        [[maybe_unused]] inline Head::Ptr decodeFirst(const Buffers &buffers)
        {
            if (buffers.empty())
            {
                throw runtime_error("buffers empty");
            }
            return decode(buffers[0].first.get());
        }


        /**
         * @brief Update id to buffer to identificate package
         * @param buffer will be modified
         * @param id id to assign
         */
        [[maybe_unused]] void updateIdToBufferEncoded(Buffer &buffer, uint8_t id);

        /**
         * @brief Update id to buffer to identificate packages
         * @param buffers will be modified
         * @param id id to assign
         */
        [[maybe_unused]] inline void updateIdToBufferEncoded(Buffers &buffers, uint8_t id)
        {
            for (auto &&it: buffers)
            {
                updateIdToBufferEncoded(it, id);
            }
        }

        /**
         * Get lib version
         * @param major release reference
         * @param minor release reference
         * @param patch release reference
         */
        [[maybe_unused]] void getVersion(int &major, int &minor, int &patch);

        /**
         * Compose a decoded package
         * @param heads of package ptr
         * @return a pair with type of package and pointer of them
         */
        [[maybe_unused]] pair <Flags, Package::Ptr> composeDecodedChunks(const Heads &heads);

        /**
         * Check if the data transmission is ended
         * @param head package
         * @return true if end communication
         */
        [[maybe_unused]] bool endCommunication(const Head::Ptr &head) noexcept;

    }
}


#pragma clang diagnostic pop
