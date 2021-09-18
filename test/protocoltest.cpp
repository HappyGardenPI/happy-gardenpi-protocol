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

#include <fstream>
#include <string>
using namespace std;

#include <hgardenpi-protocol/protocol.hpp>
#include <hgardenpi-protocol/packages/aggregation.hpp>
#include <hgardenpi-protocol/packages/certificate.hpp>
#include <hgardenpi-protocol/packages/finish.hpp>
#include <hgardenpi-protocol/packages/station.hpp>
#include <hgardenpi-protocol/packages/synchro.hpp>
#include <hgardenpi-protocol/packages/error.hpp>
#include <hgardenpi-protocol/utilities/stringutils.hpp>
using namespace hgardenpi::protocol;

TEST(ProtocolTest, encodeAGG)
{
    auto agg = new Aggregation;

    agg->id = 23;
    agg->setDescription("desc");
    agg->setStart("start");
    agg->setEnd("end");
    agg->schedule.minute = 30;
    agg->schedule.hour = 13;
    agg->schedule.days = 0b0111'1111;
    agg->sequential = false;
    agg->weight = 20;
    agg->status = hgardenpi::protocol::v1::Status::UNACTIVE;

    auto enc = encode(agg, SYN);
    EXPECT_EQ(enc.size(), 1);

    auto head = decode(enc[0].first);
    EXPECT_EQ(head->flags, AGG | SYN);



    if (auto *ptr = dynamic_cast<Aggregation *>(head->deserialize()))
    {
        EXPECT_TRUE(ptr->getDescription() == string("desc"));
        EXPECT_TRUE(ptr->getStart() == string("start"));
        EXPECT_TRUE(ptr->getEnd() == string("end"));
        EXPECT_EQ(ptr->schedule.minute, 30);
        EXPECT_EQ(ptr->schedule.hour, 13);
        EXPECT_EQ(ptr->schedule.days, 0b0111'1111);
        EXPECT_EQ(ptr->sequential, false);
        EXPECT_EQ(ptr->weight, 20);
        EXPECT_EQ(ptr->status, hgardenpi::protocol::v1::Status::UNACTIVE);
        delete ptr;
    }
}

TEST(ProtocolTest, encodeCRT)
{
    string crtExample = "ssh-rsa AAAAB3NzaC1yc2EAAAABJQAAAQB/nAmOjTmezNUDKYvEeIRf2YnwM9/uUG1d0BYsc8/tRtx+RGi7N2lUbp728MXGwdnL9od4cItzky/zVdLZE2cycOa18xBK9cOWmcKS0A8FYBxEQWJ/q9YVUgZbFKfYGaGQxsER+A0w/fX8ALuk78ktP31K69LcQgxIsl7rNzxsoOQKJ/CIxOGMMxczYTiEoLvQhapFQMs3FL96didKr/QbrfB1WT6s3838SEaXfgZvLef1YB2xmfhbT9OXFE3FXvh2UPBfN+ffE7iiayQf/2XR+8j4N4bW30DiPtOQLGUrH1y5X/rpNZNlWW2+jGIxqZtgWg7lTy3mXy5x836Sj/6L";

    auto crt = new Certificate;
    crt->setCertificate(crtExample);

    auto enc = encode(crt, ACK);
    EXPECT_EQ(enc.size(), 3);

    string crtRet;
    uint16_t i = 0;
    for (auto &&buffer : enc)
    {
        auto head = decode(buffer.first);
        if (head->flags & FIN && head->flags & ACK)
        {
            EXPECT_EQ(head->flags, FIN | ACK | PRT);
            break;
        }
        if (head->flags & CRT && head->flags & ACK && head->flags & PRT)
        {
            EXPECT_EQ(head->flags, CRT | ACK | PRT);
            if (auto *ptr = dynamic_cast<Certificate *>(head->deserialize(i)))
            {
                crtRet += ptr->getCertificate();
                delete ptr;
            }
            i++;
        }
    }
    EXPECT_TRUE(crtExample == crtRet);
}

TEST(ProtocolTest, encodeERR)
{
    string msgExample = "ssh-rsa 23232323 ERR AAAAB3NzaC1yc2EAAAABJQAAAQB/nAmOjTmezNUDKYvEeIRf2YnwM9/uUG1d0BYsc8/tRtx+RGi7N2lUbp728MXGwdnL9od4cItzky/zVdLZE2cycOa18xBK9cOWmcKS0A8FYBxEQWJ/q9YVUgZbFKfYGaGQxsER+A0w/fX8ALuk78ktP31K69LcQgxIsl7rNzxsoOQKJ/CIxOGMMxczYTiEoLvQhapFQMs3FL96didKr/QbrfB1WT6s3838SEaXfgZvLef1YB2xmfhbT9OXFE3FXvh2UPBfN+ffE7iiayQf/2XR+8j4N4bW30DiPtOQLGUrH1y5X/rpNZNlWW2+jGIxqZtgWg7lTy3mXy5x836Sj/6L";

    auto crt = new Error;
    crt->setMsg(msgExample);

    auto enc = encode(crt, ACK);
    EXPECT_EQ(enc.size(), 3);

    string msgRet;
    uint16_t i = 0;
    for (auto &&buffer : enc)
    {
        auto head = decode(buffer.first);
        if (head->flags & FIN && head->flags & ACK)
        {
            EXPECT_EQ(head->flags, FIN | ACK | PRT);
            break;
        }
        if (head->flags & ERR && head->flags & ACK && head->flags & PRT)
        {
            EXPECT_EQ(head->flags, ERR | ACK | PRT);
            if (auto *ptr = dynamic_cast<Certificate *>(head->deserialize(i)))
            {
                msgRet += ptr->getCertificate();
                delete ptr;
            }
            i++;
        }
    }
    EXPECT_TRUE(msgExample == msgRet);
}


TEST(ProtocolTest, encodeFIN)
{
//    auto fin1 = new Finish;
//    auto encode1 = encode(fin1);
//    EXPECT_EQ(encode1.size(), 1);
//    EXPECT_EQ(encode1.begin()->get()->flags, FIN);
//
//    auto fin2 = new Finish;
//    auto encode2 = encode(fin2, ACK);
//    EXPECT_EQ(encode2.size(), 1);
//    EXPECT_EQ(encode2.begin()->get()->flags, FIN | ACK);
}

TEST(ProtocolTest, encodeSTA)
{
//    auto sta1 = new Station;
//    sta1->name = "station1";
//    sta1->description = "description1";
//    sta1->relayNumber = 1;
//    sta1->wateringTime = 10;
//    sta1->wateringTimeLeft = 2;
//    auto encode1 = encode(sta1);
//
//    Station *ret1 = reinterpret_cast<Station *>(encode1.begin()->get()->payload);
//    EXPECT_EQ(encode1.size(), 1);
//    EXPECT_EQ(encode1.begin()->get()->flags, STA);
//    EXPECT_EQ(ret1->name, sta1->name);
//    EXPECT_EQ(ret1->description, sta1->description);
//    EXPECT_EQ(ret1->relayNumber, sta1->relayNumber);
//    EXPECT_EQ(ret1->wateringTime, sta1->wateringTime);
//    EXPECT_EQ(ret1->wateringTimeLeft, sta1->wateringTimeLeft);
//
//    auto sta2 = new Station;
//    sta2->name = "station2";
//    sta2->description = "description2";
//    sta2->relayNumber = 2;
//    sta2->wateringTime = 10;
//    sta2->wateringTimeLeft = 2;
//    auto encode2 = encode(sta2, ACK);
//
//    Station *ret2 = reinterpret_cast<Station *>(encode2.begin()->get()->payload);
//    EXPECT_EQ(encode2.size(), 1);
//    EXPECT_EQ(encode2.begin()->get()->flags, STA | ACK);
//    EXPECT_EQ(ret2->name, sta2->name);
//    EXPECT_EQ(ret2->description, sta2->description);
//    EXPECT_EQ(ret2->relayNumber, sta2->relayNumber);
//    EXPECT_EQ(ret2->wateringTime, sta2->wateringTime);
//    EXPECT_EQ(ret2->wateringTimeLeft, sta2->wateringTimeLeft);
}

TEST(ProtocolTest, encodeSYN)
{
    auto syn1 = new Synchro;
    syn1->serial = new char[6];
    syn1->serial[6] = 0;
    strncpy(syn1->serial, "test1", 6);

    auto encode1 = encode(syn1);
    EXPECT_EQ(encode1.size(), 1);

    auto decode1 = decode(encode1[0].first);
    EXPECT_EQ(decode1->flags, SYN);

    string payloadStr;
    for (int i = 0; i < decode1->length; i++)
    {
        payloadStr += decode1->payload[i];
    }

    EXPECT_TRUE(payloadStr == "test1");

    auto syn2 = new Synchro;
    syn2->serial = new char[6];
    syn2->serial[6] = 0;
    strncpy(syn2->serial, "test2", 6);

    auto encode2 = encode(syn2, ACK);
    EXPECT_EQ(encode2.size(), 1);

    auto decode2 = decode(encode2[0].first);
    EXPECT_EQ(decode2->flags, SYN | ACK);

    payloadStr = "";
    for (int i = 0; i < decode2->length; i++)
    {
        payloadStr += decode2->payload[i];
    }

    EXPECT_TRUE(payloadStr == "test2");
}
