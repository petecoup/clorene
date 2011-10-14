/*
 * Copyright (C) 2011 Peter Couperus
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <gtest/gtest.h>


class RuntimeExecutionTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        clbuffer_ = new clorene::Buffer(size_t(4));
        data_ = (char*)clbuffer_->data();
  
        data_[0] = 'a';
        data_[1] = 'b';
        data_[2] = 'c';
        data_[3] = 'd';
    }

    char* data_;
    clorene::Buffer* clbuffer_;
};

TEST_F(ReadMemoryCommandTest, ReadBufferCommand)
{
    char buffer[4];

    clorene::Command* readCmd = new clorene::ReadBuffer(clbuffer_, buffer, 4);

    readCmd->execute();
    
    EXPECT_EQ(buffer[0], 'a');
    EXPECT_EQ(buffer[1], 'b');
    EXPECT_EQ(buffer[2], 'c');
    EXPECT_EQ(buffer[3], 'd');
}

TEST_F(ReadMemoryCommandTest, ReadOffsetBufferCommand)
{
    char buffer[2];

    clorene::Command* readCmd = new clorene::ReadBuffer(clbuffer_, buffer, 2, 2);

    readCmd->execute();

    EXPECT_EQ(buffer[0], 'c');
    EXPECT_EQ(buffer[1], 'd');
}

TEST(WriteMemoryCommandTest, WriteBufferCommand)
{
    char buffer[4] = {'a','b','c','d'};

    clorene::Buffer* clbuffer = new clorene::Buffer(size_t(4));
    clorene::Command* writeCmd = new clorene::WriteBuffer(buffer, clbuffer, 4);

    writeCmd->execute();

    const char* data = (char *)clbuffer->data();
    EXPECT_EQ(data[0], 'a');
    EXPECT_EQ(data[1], 'b');
    EXPECT_EQ(data[2], 'c');
    EXPECT_EQ(data[3], 'd');
}

TEST(WriteMemoryCommandTest, WriteOffsetBufferCommand)
{
    char buffer[2] = {'a','b'};
    
    clorene::Buffer* clbuffer = new clorene::Buffer(size_t(4));
    char* data = (char*)clbuffer->data();
    data[0] = data[1] = data[2] = data[3] = 'x';

    clorene::Command* writeCmd = new clorene::WriteBuffer(buffer, clbuffer, 2, 2);

    writeCmd->execute();

    EXPECT_EQ(data[0], 'x');
    EXPECT_EQ(data[1], 'x');
    EXPECT_EQ(data[2], 'a');
    EXPECT_EQ(data[3], 'b');
}

