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

#include <iostream>
#include <string>
using namespace std;

#include <hgardenpi-protocol/protocol.hpp>
#include <hgardenpi-protocol/packages/aggregation.hpp>
#include <hgardenpi-protocol/packages/certificate.hpp>
#include <hgardenpi-protocol/packages/finish.hpp>
#include <hgardenpi-protocol/packages/station.hpp>
#include <hgardenpi-protocol/packages/synchro.hpp>
using namespace hgardenpi::protocol;


TEST(ProtocolTest, decode)
{
    const uint8_t data[]{0x01, 0x01, 0x0F, 0x63, 0x69, 0x61, 0x6f, 0x5f, 0x73, 0x6f, 0x6e, 0x6f, 0x5f, 0x70, 0x69, 0x70,
                         0x70, 0x6f, 0x41, 0x88};

    auto head = decode(data);

    EXPECT_EQ(head->version, 0);
    EXPECT_EQ(head->flags, 1);
    EXPECT_EQ(head->id, 1);
    EXPECT_EQ(head->length, 15);
    EXPECT_EQ(head->crc16, 34881);

}

TEST(ProtocolTest, encodeFIN)
{
    auto fin1 = new Finish;
    auto encode1 = encode(fin1);
//    EXPECT_EQ(encode1->flags, FIN);

    auto fin2 = new Finish;
    auto encode2 = encode(fin2, ACK);

//    EXPECT_EQ(encode2->flags, FIN | ACK);
}

TEST(ProtocolTest, encodeSYN)
{
    auto syn1 = new Synchro;
    syn1->serial = new char[5];
    strncpy(syn1->serial, "test1", 5);

    auto encode1 = encode(syn1);
//    EXPECT_EQ(encode1->flags, SYN);
//    EXPECT_TRUE(string(reinterpret_cast<char *>(encode1->payload)) == "test1");


    auto syn2 = new Synchro;
    syn2->serial = new char[5];
    strncpy(syn1->serial, "test2", 5);

    auto encode2 = encode(syn2, ACK);
//    EXPECT_EQ(encode2->flags, SYN | ACK);
//    EXPECT_TRUE(string(reinterpret_cast<char *>(encode2->payload)) == "test2");
}
