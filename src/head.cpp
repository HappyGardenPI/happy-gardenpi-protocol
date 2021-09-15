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
// Created by Antonio Salsi on 15/09/21.
//

#include <hgardenpi-protocol/head.hpp>
#include <hgardenpi-protocol/packages/aggregation.hpp>
#include <hgardenpi-protocol/packages/certificate.hpp>
#include <hgardenpi-protocol/packages/finish.hpp>
#include <hgardenpi-protocol/packages/station.hpp>
#include <hgardenpi-protocol/packages/synchro.hpp>
#include <hgardenpi-protocol/packages/error.hpp>

namespace hgardenpi::protocol
{
    inline namespace v1
    {

        [[nodiscard]] Package *Head::deserialize() const noexcept
        {
            Package * ret = nullptr;
            //check which child package was packaged
            if (flags & AGG) //is Flags::AGG package
                ret = Aggregation::deserialize(payload);
            else if (flags & CRT) //is Flags::CRT package
                ret = Certificate::deserialize(payload);
            else if (flags & FIN) //is Flags::FIN package
            {

            } else if (flags & STA) //is Flags::STA package
            {

            } else if (flags & ERR) //is Flags::ERR package
            {

            } else if (flags & SYN) //is Flags::SYN package
            {

            }
            return ret;
        }

    }
}