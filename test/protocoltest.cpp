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

#include <string>
using namespace std;

#include <hgardenpi-protocol/protocol.hpp>
#include <hgardenpi-protocol/packages/aggregation.hpp>
#include <hgardenpi-protocol/packages/data.hpp>
#include <hgardenpi-protocol/packages/finish.hpp>
#include <hgardenpi-protocol/packages/station.hpp>
#include <hgardenpi-protocol/packages/synchro.hpp>
#include <hgardenpi-protocol/packages/error.hpp>
#include <hgardenpi-protocol/utilities/stringutils.hpp>
#include <hgardenpi-protocol/utilities/numberutils.hpp>
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
    agg->status = hgardenpi::protocol::v2::Status::UNACTIVE;

    auto enc = encode(agg, ACK);

    delete agg;

    EXPECT_EQ(enc.size(), 1);

    auto head = decode(enc[0].first.get());
    EXPECT_EQ(head->flags, AGG | ACK);

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
        EXPECT_EQ(ptr->status, Status::UNACTIVE);
        delete ptr;
    }


}

TEST(ProtocolTest, encodeDAT)
{
    string datExample = "ssh-rsa AAAAB3NzaC1yc2EAAAABJQAAAQB/nAmOjTmezNUDKYvEeIRf2YnwM9/uUG1d0BYsc8/tRtx+RGi7N2lUbp728MXGwdnL9od4cItzky/zVdLZE2cycOa18xBK9cOWmcKS0A8FYBxEQWJ/q9YVUgZbFKfYGaGQxsER+A0w/fX8ALuk78ktP31K69LcQgxIsl7rNzxsoOQKJ/CIxOGMMxczYTiEoLvQhapFQMs3FL96didKr/QbrfB1WT6s3838SEaXfgZvLef1YB2xmfhbT9OXFE3FXvh2UPBfN+ffE7iiayQf/2XR+8j4N4bW30DiPtOQLGUrH1y5X/rpNZNlWW2+jGIxqZtgWg7lTy3mXy5x836Sj/6L";

    auto dat = new Data;
    dat->setPayload(datExample);

    auto enc = encode(dat, ACK);

    delete dat;

    EXPECT_EQ(enc.size(), 3);

    string datRet;
    uint16_t i = 0;
    for (auto &&buffer : enc)
    {
        auto head = decode(buffer.first.get());
        if (head->flags & FIN && head->flags & ACK)
        {
            EXPECT_EQ(head->flags, FIN | ACK | CKN);
            break;
        }
        if (head->flags & DAT && head->flags & ACK && head->flags & CKN)
        {
            EXPECT_EQ(head->flags, DAT | ACK | CKN);
            if (auto *ptr = dynamic_cast<Data *>(head->deserialize(i)))
            {
                datRet += ptr->getChunk();
                delete ptr;
            }
            i++;
        }
    }

    EXPECT_TRUE(datExample == datRet);
}


TEST(ProtocolTest, encodeERR)
{
    string msgExample = move(generateRandomString(260));

    auto err = new Error;
    err->setMsg(msgExample);

    auto enc = encode(err, ACK);
    EXPECT_EQ(enc.size(), 3);

    string msgRet;
    uint16_t i = 0;
    for (auto &&buffer : enc)
    {
        auto head = decode(buffer.first.get());
        if (head->flags & FIN && head->flags & ACK)
        {
            EXPECT_EQ(head->flags, FIN | ACK | CKN);
            break;
        }
        if (head->flags & ERR && head->flags & ACK && head->flags & CKN)
        {
            EXPECT_EQ(head->flags, ERR | ACK | CKN);
            if (auto *ptr = dynamic_cast<Error *>(head->deserialize(i)))
            {
                string &&s = ptr->getChunk();
                msgRet += s;
                delete ptr;
            }
            i++;
        }
    }

    delete err;

    EXPECT_TRUE(msgExample == msgRet);
}



TEST(ProtocolTest, encodeFIN)
{
    auto fin = new Finish;

    auto enc = encode(fin, ACK);
    EXPECT_EQ(enc.size(), 1);

    auto head = decode(enc[0].first.get());
    EXPECT_EQ(head->flags, FIN | ACK);

    delete fin;
}

TEST(ProtocolTest, encodeSTA)
{
    auto sta = new Station;
    sta->setName("Name");
    sta->setDescription("Description");
    sta->relayNumber = 1;
    sta->wateringTime = 10;
    sta->wateringTimeLeft = 2;
    sta->weight = 30;
    sta->status = Status::INSERT;
    auto encode1 = encode(sta);

    auto enc = encode(sta, ACK);

    delete sta;

    EXPECT_EQ(enc.size(), 1);

    auto head = decode(enc[0].first.get());
    EXPECT_EQ(head->flags, STA | ACK);

    if (auto *ptr = dynamic_cast<Station *>(head->deserialize()))
    {

        EXPECT_TRUE(ptr->getName() == string("Name"));
        EXPECT_TRUE(ptr->getDescription() == string("Description"));
        EXPECT_EQ(ptr->relayNumber, 1);
        EXPECT_EQ(ptr->wateringTime, 10);
        EXPECT_EQ(ptr->wateringTimeLeft, 2);
        EXPECT_EQ(ptr->weight, 30);
        EXPECT_EQ(ptr->status, Status::UNACTIVE);
        delete ptr;
    }

}


TEST(ProtocolTest, encodeSYN)
{
    auto syn = new Synchro;
    syn->setSerial("serial123456789");

    auto enc = encode(syn, ACK);
    EXPECT_EQ(enc.size(), 1);

    auto head = decode(enc[0].first.get());
    EXPECT_EQ(head->flags, SYN | ACK);

    if (auto *ptr = dynamic_cast<Synchro *>(head->deserialize()))
    {
        EXPECT_TRUE(ptr->getSerial() == "serial123456789");
        delete ptr;
    }

    delete syn;
}

TEST(ProtocolTest, encodeChangePackageId)
{
    auto syn = new Synchro;

    string &&random = generateRandomString(128);

    syn->setSerial(random);

    auto enc = encode(syn, ACK);
    EXPECT_EQ(enc.size(), 1);

    updateIdToBufferEncoded(enc[0], 37);

    auto head = decode(enc[0].first.get());
    EXPECT_EQ(head->flags, SYN | ACK);

    EXPECT_EQ(head->id, 37);

    if (auto *ptr = dynamic_cast<Synchro *>(head->deserialize()))
    {
        EXPECT_TRUE(ptr->getSerial() == random);
        delete ptr;
    }

    delete syn;
}

TEST(ProtocolTest, endCommunication)
{
    auto fin = new Finish;
    auto encFin = encode(fin, ACK);
    auto headFin = decode(encFin[0].first.get());
    ASSERT_TRUE(::endCommunication(headFin));

    auto err = new Error;
    err->setMsg(generateRandomString(260));
    auto encErr = encode(err, ACK);
    auto headErr = decode(encErr[0].first.get());
    ASSERT_FALSE(::endCommunication(headErr));
    headErr = decode(encErr[1].first.get());
    ASSERT_FALSE(::endCommunication(headErr));
    headErr = decode(encErr[2].first.get());
    ASSERT_TRUE(::endCommunication(headErr));

    delete fin;
    delete err;
}

TEST(ProtocolTest, composeDecodedChunks)
{
    auto sta = new Station;
    sta->setName("Name");
    sta->setDescription("Description");
    sta->relayNumber = 1;
    sta->wateringTime = 10;
    sta->wateringTimeLeft = 2;
    sta->weight = 30;
    sta->status = Status::INSERT;
    auto encSta = encode(sta, ACK);
    auto headSta = decode(encSta[0].first.get());
    auto pkgSta = composeDecodedChunks({headSta});

    if (shared_ptr<Station> ptr = std::dynamic_pointer_cast<Station>( composeDecodedChunks({headSta}).second ))
    {
        EXPECT_TRUE(ptr->getName() == string("Name"));
        EXPECT_TRUE(ptr->getDescription() == string("Description"));
        EXPECT_EQ(ptr->relayNumber, 1);
        EXPECT_EQ(ptr->wateringTime, 10);
        EXPECT_EQ(ptr->wateringTimeLeft, 2);
        EXPECT_EQ(ptr->weight, 30);
        EXPECT_EQ(ptr->status, Status::UNACTIVE);
    }

    {
        auto data = new Data;
        auto &&payload = generateRandomString(260);
        data->setPayload(payload);
        auto encDat = encode(data, ACK);

        Heads heads;
        heads.push_back(move(decode(encDat[0].first.get())));
        heads.push_back(move(decode(encDat[1].first.get())));
        heads.push_back(move(decode(encDat[2].first.get())));

        auto &&[flags, pkg] = composeDecodedChunks(heads);
        if (shared_ptr<Data> ptr = std::dynamic_pointer_cast<Data>(pkg ))
        {
            EXPECT_TRUE(ptr->getPayload() == payload);
        }
        delete data;
    }

    {
        auto err = new Error;
        auto &&msg = generateRandomString(260);
        err->setMsg(msg);
        auto encErr = encode(err, ACK);

        Heads heads;
        heads.push_back(move(decode(encErr[0].first.get())));
        heads.push_back(move(decode(encErr[1].first.get())));
        heads.push_back(move(decode(encErr[2].first.get())));

        auto &&[flags, pkg] = composeDecodedChunks(heads);
        if (shared_ptr<Error> ptr = std::dynamic_pointer_cast<Error>( pkg ))
        {
            EXPECT_TRUE(ptr->getMsg() == msg);
        }
        delete err;
    }

    {
        auto err = new Error;
        auto &&msg = generateRandomString(100);
        err->setMsg(msg);
        auto encErr = encode(err, ACK);

        Heads heads;
        heads.push_back(move(decode(encErr[0].first.get())));

        auto &&[flags, pkg] = composeDecodedChunks(heads);
        if (shared_ptr<Error> ptr = std::dynamic_pointer_cast<Error>( pkg ))
        {
            EXPECT_TRUE(ptr->getMsg() == msg);
        }
        delete err;
    }

    delete sta;

}

TEST(ProtocolTest, generateRandomIntegral)
{
    auto i = generateRandomIntegral<uint8_t>();

    EXPECT_GT(i, 0);

}