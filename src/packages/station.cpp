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
// Created by Antonio Salsi on 19/09/21.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"

#include "hgardenpi-protocol/packages/station.hpp"

#include <stdexcept>
#include <memory>
#include <cstring>
using namespace std;

#include "hgardenpi-protocol/constants.hpp"

namespace hgardenpi::protocol
{
    inline namespace v1
    {

        string Station::getName() const noexcept
        {
            HGARDENPI_PROTOCOL_GETTER(name, nameLen)
        }

        void Station::setName(const string &name) noexcept
        {
            HGARDENPI_PROTOCOL_SETTER(name, nameLen)
        }

        string Station::getDescription() const noexcept
        {
            HGARDENPI_PROTOCOL_GETTER(description, descriptionLen)
        }

        void Station::setDescription(const string &description) noexcept
        {
            HGARDENPI_PROTOCOL_SETTER(description, descriptionLen)
        }

        Buffer Station::serialize() const
        {
            return hgardenpi::protocol::Buffer();
        }

        Station *Station::deserialize(const uint8_t *buffer, uint8_t, uint8_t)
        {
            return nullptr;
        }
    }
}