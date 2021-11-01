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
#include <hgardenpi-protocol/packages/data.hpp>
#include <hgardenpi-protocol/packages/finish.hpp>
#include <hgardenpi-protocol/packages/station.hpp>
#include <hgardenpi-protocol/packages/synchro.hpp>
#include <hgardenpi-protocol/packages/error.hpp>
#include <hgardenpi-protocol/utilities/stringutils.hpp>

namespace hgardenpi::protocol
{
    inline namespace v2
    {

        [[nodiscard]] Package *Head::deserialize(uint8_t chunkOfPackage) const
        {
            Package * ret = nullptr;
            //check which child package was packaged
            if ((flags & AGG) == AGG) //is Flags::AGG package
                ret = Aggregation::deserialize(payload, length, chunkOfPackage);
            else if ((flags & ERR) == ERR) //is Flags::ERR package
                ret = Error::deserialize(payload, length, chunkOfPackage);
            else if ((flags & DAT) == DAT) //is Flags::DAT package
                ret = Data::deserialize(payload, length, chunkOfPackage);
            else if ((flags & FIN) == FIN) //is Flags::FIN package
                ret = Finish::deserialize(payload, length, chunkOfPackage);
            else if ((flags & STA) == STA) //is Flags::STA package
                ret = Station::deserialize(payload, length, chunkOfPackage);
            else if ((flags & SYN) == SYN) //is Flags::SYN package
                ret = Synchro::deserialize(payload, length, chunkOfPackage);
            return ret;
        }

        inline string Head::getPayload() const noexcept
        {
            return stringHexToString(payload, length);
        }

    }
}