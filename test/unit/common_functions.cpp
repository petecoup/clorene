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

#include <llvm/LLVMContext.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/MemoryBuffer.h>

#include "program/Compiler.h"
#include "runtime/FunctionRunner.h"

class CommonFunctionsTest: public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        valx_[0] = 1.0;
        valx_[1] = 4.0;
        valx_[2] = 10.0;
        valx_[3] = 16.0;
        valy_[0] = 2.0;
        valy_[1] = 3.0;
        valy_[2] = 20.0;
        valy_[3] = 30.0;
        resultv_[0] = resultv_[1] = resultv_[2] = resultv_[3] = 0.0;
        fconst = 12.0;

        program_ = "void funcexec(float* a, float* b, float* rv) {\n"
                   " float2 f2; float3 f3; float4 f4;\n"
                   " float2 g2; float3 g3; float4 g4;\n"
                   " float2 r2; float3 r3; float4 r4;\n"
                   " f2[0] = f3[0] = f4[0] = a[0];\n"
                   " g2[0] = g3[0] = g4[0] = b[0];\n"
                   " f2[1] = f3[1] = f4[1] = a[1];\n"
                   " g2[1] = g3[1] = g4[1] = b[1];\n"
                   " f3[2] = f4[2] = a[2];\n"
                   " g3[2] = g4[2] = b[2];\n"
                   " f4[3] = a[3];\n"
                   " g4[3] = b[3];\n";
    }

    void buildAndExecute()
    {
        args_.push_back(llvm::GenericValue((void*)(&valx_)));
        args_.push_back(llvm::GenericValue((void*)(&valy_)));
        args_.push_back(llvm::GenericValue((void*)(&resultv_)));
        clorene::Compiler compiler;
        llvm::Module* module = compiler.compile(fullProgram_);
        ASSERT_TRUE(module != 0);

        clorene::FunctionRunner runner(module, "funcexec", ctxt_, true);

        runner.setArgs(args_);
        runner.run();
    }

    llvm::LLVMContext ctxt_;
    std::string program_;
    std::string fullProgram_;
    float valx_[4];
    float valy_[4];
    float resultv_[4];
    float result_;
    
    float fconst;

    std::vector<llvm::GenericValue> args_;
};

TEST_F(CommonFunctionsTest, Max2Test)
{
    fullProgram_ = program_ + std::string(
                            " r2 = max(f2,g2);\n"
                            " rv[0] = r2[0]; rv[1] = r2[1]; }\n" );

    buildAndExecute();

    EXPECT_EQ(resultv_[0], 2.0);
    EXPECT_EQ(resultv_[1], 4.0);
    EXPECT_EQ(resultv_[2], 0.0);
    EXPECT_EQ(resultv_[3], 0.0);
}

TEST_F(CommonFunctionsTest, Max3Test)
{
    fullProgram_ = program_+ std::string(
                             " r3 = max(f3,g3);\n"
                             " rv[0] = r3[0]; rv[1] = r3[1];\n"
                             " rv[2] = r3[2];}\n" );
    buildAndExecute();

    EXPECT_EQ(resultv_[0], 2.0);
    EXPECT_EQ(resultv_[1], 4.0);
    EXPECT_EQ(resultv_[2], 20.0);
    EXPECT_EQ(resultv_[3], 0.0);    
}

TEST_F(CommonFunctionsTest, Max4Test)
{
    fullProgram_ = program_+ std::string(
                             " r4 = max(f4,g4);\n"
                             " rv[0] = r4[0]; rv[1] = r4[1];\n"
                             " rv[2] = r4[2]; rv[3] = r4[3]; }\n" );
    buildAndExecute();

    EXPECT_EQ(resultv_[0], 2.0);
    EXPECT_EQ(resultv_[1], 4.0);
    EXPECT_EQ(resultv_[2], 20.0);
    EXPECT_EQ(resultv_[3], 30.0);    
}

TEST_F(CommonFunctionsTest, Min2Test)
{
    fullProgram_ = program_ + std::string(
                            " r2 = min(f2,g2);\n"
                            " rv[0] = r2[0]; rv[1] = r2[1]; }\n" );

    buildAndExecute();

    EXPECT_EQ(resultv_[0], 1.0);
    EXPECT_EQ(resultv_[1], 3.0);
    EXPECT_EQ(resultv_[2], 0.0);
    EXPECT_EQ(resultv_[3], 0.0);
}

TEST_F(CommonFunctionsTest, Min3Test)
{
    fullProgram_ = program_+ std::string(
                             " r3 = min(f3,g3);\n"
                             " rv[0] = r3[0]; rv[1] = r3[1];\n"
                             " rv[2] = r3[2];}\n" );
    buildAndExecute();

    EXPECT_EQ(resultv_[0], 1.0);
    EXPECT_EQ(resultv_[1], 3.0);
    EXPECT_EQ(resultv_[2], 10.0);
    EXPECT_EQ(resultv_[3], 0.0);    
}

TEST_F(CommonFunctionsTest, Min4Test)
{
    fullProgram_ = program_+ std::string(
                             " r4 = min(f4,g4);\n"
                             " rv[0] = r4[0]; rv[1] = r4[1];\n"
                             " rv[2] = r4[2]; rv[3] = r4[3]; }\n" );
    buildAndExecute();

    EXPECT_EQ(resultv_[0], 1.0);
    EXPECT_EQ(resultv_[1], 3.0);
    EXPECT_EQ(resultv_[2], 10.0);
    EXPECT_EQ(resultv_[3], 16.0);    
}

