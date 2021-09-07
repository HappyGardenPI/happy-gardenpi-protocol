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

TEST(ProtocolTest, encodeAGG)
{
    auto agg1 = new Aggregation;


    agg1->id = 23;
    agg1->descriptionSize = strlen("descrizione");
    agg1->description = new char [agg1->descriptionSize];
    strncpy(agg1->description, "descrizione", agg1->descriptionSize);
    agg1->schedule.minute = 30;
    agg1->schedule.hour = 13;
    agg1->schedule.days = 0b01111111;

    auto encode1 = encode(agg1);
    EXPECT_EQ(encode1.size(), 1);

    cout << stringHexToString(get<0>(encode1[0]), get<1>(encode1[0])) << endl;

    auto decode1 = decode(get<0>(encode1[0]));
//    EXPECT_EQ(get<0>(encode1.begin()), AGG);

//    Aggregation *ret1 = reinterpret_cast<Aggregation *>(encode1.begin()->get()->payload);
//    EXPECT_EQ(agg1->description, ret1->description);
//    EXPECT_EQ(agg1->schedule.minute, ret1->schedule.minute);
//    EXPECT_EQ(agg1->schedule.hour, ret1->schedule.hour);
//    EXPECT_EQ(agg1->schedule.days, ret1->schedule.days);
//
//    auto agg2 = new Aggregation;
//    agg2->description = "description1";
//    agg2->schedule.minute = 35;
//    agg2->schedule.hour = 14;
//    agg2->schedule.days = 0b01100111;
//
//    auto encode2 = encode(agg2, ACK);
//    EXPECT_EQ(encode2.size(), 1);
//    EXPECT_EQ(encode2.begin()->get()->flags, AGG | ACK);
//
//    Aggregation *ret2 = reinterpret_cast<Aggregation *>(encode2.begin()->get()->payload);
//    EXPECT_EQ(ret2->description, agg2->description);
//    EXPECT_EQ(ret2->schedule.minute, agg2->schedule.minute);
//    EXPECT_EQ(ret2->schedule.hour, agg2->schedule.hour);
//    EXPECT_EQ(ret2->schedule.days, agg2->schedule.days);
}

TEST(ProtocolTest, encodeCRT)
{
//    string crtExample = "ssh-rsa AAAAB3NzaC1yc2EAAAABJQAAAQB/nAmOjTmezNUDKYvEeIRf2YnwM9/uUG1d0BYsc8/tRtx+RGi7N2lUbp728MXGwdnL9od4cItzky/zVdLZE2cycOa18xBK9cOWmcKS0A8FYBxEQWJ/q9YVUgZbFKfYGaGQxsER+A0w/fX8ALuk78ktP31K69LcQgxIsl7rNzxsoOQKJ/CIxOGMMxczYTiEoLvQhapFQMs3FL96didKr/QbrfB1WT6s3838SEaXfgZvLef1YB2xmfhbT9OXFE3FXvh2UPBfN+ffE7iiayQf/2XR+8j4N4bW30DiPtOQLGUrH1y5X/rpNZNlWW2+jGIxqZtgWg7lTy3mXy5x836Sj/6L";
//
//    auto err1 = new Certificate;
//    err1->certificate = crtExample;
//
//    auto encode1 = encode(err1);
//    EXPECT_EQ(encode1.size(), 3);
//    EXPECT_EQ(encode1[0]->flags, CRT | PRT);
//    EXPECT_EQ(encode1[1]->flags, CRT | PRT);
//    EXPECT_EQ(encode1[2]->flags, FIN);
//
//    char * payload1 = new char[encode1[0]->length];
//    memcpy(payload1, encode1[0]->payload, encode1[0]->length);
//
//    char * payload2 = new char[encode1[1]->length];
//    memcpy(payload2, encode1[1]->payload, encode1[1]->length);
//
//    EXPECT_EQ(memcmp(&crtExample[0], payload1, encode1[0]->length), 0);
//    EXPECT_EQ(memcmp(&crtExample[encode1[0]->length], payload2, encode1[1]->length), 0);
//
//    delete[] payload1;
//    payload1 = nullptr;
//    delete[] payload2;
//    payload2 = nullptr;
//
//    auto err2 = new Certificate;
//    err2->certificate = crtExample;
//
//    auto encode2 = encode(err2, ACK);
//    EXPECT_EQ(encode2.size(), 3);
//    EXPECT_EQ(encode2[0]->flags, CRT | PRT | ACK);
//    EXPECT_EQ(encode2[1]->flags, CRT | PRT | ACK);
//    EXPECT_EQ(encode2[2]->flags, FIN | ACK);
//
//    payload1 = new char[encode2[0]->length];
//    memcpy(payload1, encode2[0]->payload, encode2[0]->length);
//
//    payload2 = new char[encode2[1]->length];
//    memcpy(payload2, encode2[1]->payload, encode2[1]->length);
//
//    EXPECT_EQ(memcmp(&crtExample[0], payload1, encode2[0]->length), 0);
//    EXPECT_EQ(memcmp(&crtExample[encode2[0]->length], payload2, encode2[1]->length), 0);
//
//    delete[] payload1;
//    payload1 = nullptr;
//    delete[] payload2;
//    payload2 = nullptr;

}

TEST(ProtocolTest, encodeERR)
{
//
//    string msgExample = "ssh-rsa AAAAB3NzaC1yc2EAAAABJQAAAQB/nAmOjTmezNUDKYvEeIRf2YnwM9/uUG1d0BYsc8/tRtx+RGi7N2lUbp728MXGwdnL9od4cItzky/zVdLZE2cycOa18xBK9cOWmcKS0A8FYBxEQWJ/q9YVUgZbFKfYGaGQxsER+A0w/fX8ALuk78ktP31K69LcQgxIsl7rNzxsoOQKJ/CIxOGMMxczYTiEoLvQhapFQMs3FL96didKr/QbrfB1WT6s3838SEaXfgZvLef1YB2xmfhbT9OXFE3FXvh2UPBfN+ffE7iiayQf/2XR+8j4N4bW30DiPtOQLGUrH1y5X/rpNZNlWW2+jGIxqZtgWg7lTy3mXy5x836Sj/6L-testtest";
//
//    auto err1 = new Error;
//    err1->msg = msgExample;
//
//    auto encode1 = encode(err1);
//    EXPECT_EQ(encode1.size(), 3);
//    EXPECT_EQ(encode1[0]->flags, ERR | PRT);
//    EXPECT_EQ(encode1[1]->flags, ERR | PRT);
//    EXPECT_EQ(encode1[2]->flags, FIN);
//
//    char * payload1 = new char[encode1[0]->length];
//    memcpy(payload1, encode1[0]->payload, encode1[0]->length);
//
//    char * payload2 = new char[encode1[1]->length];
//    memcpy(payload2, encode1[1]->payload, encode1[1]->length);
//
//    EXPECT_EQ(memcmp(&msgExample[0], payload1, encode1[0]->length), 0);
//    EXPECT_EQ(memcmp(&msgExample[encode1[0]->length], payload2, encode1[1]->length), 0);
//
//    delete[] payload1;
//    payload1 = nullptr;
//    delete[] payload2;
//    payload2 = nullptr;
//
//    auto err2 = new Error;
//    err2->msg = msgExample;
//
//    auto encode2 = encode(err2, ACK);
//    EXPECT_EQ(encode2.size(), 3);
//    EXPECT_EQ(encode2[0]->flags, ERR | PRT | ACK);
//    EXPECT_EQ(encode2[1]->flags, ERR | PRT | ACK);
//    EXPECT_EQ(encode2[2]->flags, FIN | ACK);
//
//    payload1 = new char[encode2[0]->length];
//    memcpy(payload1, encode2[0]->payload, encode2[0]->length);
//
//    payload2 = new char[encode2[1]->length];
//    memcpy(payload2, encode2[1]->payload, encode2[1]->length);
//
//    EXPECT_EQ(memcmp(&msgExample[0], payload1, encode2[0]->length), 0);
//    EXPECT_EQ(memcmp(&msgExample[encode2[0]->length], payload2, encode2[1]->length), 0);
//
//    delete[] payload1;
//    payload1 = nullptr;
//    delete[] payload2;
//    payload2 = nullptr;
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
//    auto syn1 = new Synchro;
//    syn1->serial = new char[5];
//    strncpy(syn1->serial, "test1", 5);
//
//    auto encode1 = encode(syn1);
//    EXPECT_EQ(encode1.size(), 1);
//    EXPECT_EQ(encode1.begin()->get()->flags, SYN);
//    EXPECT_TRUE(string(reinterpret_cast<char *>(encode1.begin()->get()->payload)) == "test1");
//
//    auto syn2 = new Synchro;
//    syn2->serial = new char[5];
//    strncpy(syn2->serial, "test2", 5);
//
//    auto encode2 = encode(syn2, ACK);
//    EXPECT_EQ(encode2.size(), 1);
//    EXPECT_EQ(encode2.begin()->get()->flags, SYN | ACK);
//    EXPECT_TRUE(string(reinterpret_cast<char *>(encode2.begin()->get()->payload)) == "test2");
}
