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
            char *c = new(nothrow) char[nameLen + 1];
            memset(c, 0, nameLen + 1);
            memcpy(c, name, nameLen);
            string ret(c);
            delete [] c;
            return ret;
        }

        void Station::setName(const string &name) noexcept
        {
            nameLen = name.size();
            this->name = new char [nameLen];
            memset(this->name, 0, nameLen);
            memcpy(this->name, &name[0], nameLen);
        }

        string Station::getDescription() const noexcept
        {
            char *c = new(nothrow) char[descriptionLen + 1];
            memset(c, 0, descriptionLen + 1);
            memcpy(c, description, descriptionLen);
            string ret(c);
            delete [] c;
            return ret;
        }

        void Station::setDescription(const string &description) noexcept
        {
            descriptionLen = description.size();
            this->description = new char [descriptionLen];
            memset(this->description, 0, descriptionLen);
            memcpy(this->description, &description[0], descriptionLen);
        }

        Buffer Station::serialize() const
        {
            return hgardenpi::protocol::Buffer();
        }

        Station *Station::deserialize(const uint8_t *buffer, uint8_t, uint8_t) noexcept
        {
            return nullptr;
        }
    }
}