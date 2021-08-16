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

#include <gtest/gtest.h>

#include <hgardenpi-protocol/protocol.hpp>

using namespace hgardenpi::protocol;

// Demonstrate some basic assertions.
TEST(SendTest, BasicSend)
{
    const uint8_t data[]{0x11, 0x01, 0x0F, 0x63,0x69,0x61,0x6f,0x5f,0x73,0x6f,0x6e,0x6f,0x5f,0x70,0x69,0x70,0x70,0x6f, 0xbe, 0x7a};

    auto head = decode(data, 20);

    EXPECT_EQ(head->version, 1);
    EXPECT_EQ(head->flags, 1);
    EXPECT_EQ(head->txId, 1);
    EXPECT_EQ(head->length, 15);
    EXPECT_EQ(head->crc16, 31422);

}
