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
#include "runtime/Engine.h"

class SimpleFloatVecTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        val_[0] = -3;
        val_[1] = -5;
        program_ = "float add(float2 vec) { return vec[0] + vec[1]; }\n"
                   "void fill(float* a, float* b)\n"
                   "{ float2 av; av[0] = a[0]; av[1] = a[1]; *b = add(av); }\n";

        args_.push_back(llvm::GenericValue((void*)(&val_)));
        args_.push_back(llvm::GenericValue((void*)(&res_)));
    }

    llvm::LLVMContext ctxt_;
    std::string program_;
    float val_[2];
    float res_;
    std::vector<llvm::GenericValue> args_;
};

TEST_F(SimpleFloatVecTest, CompileAndRun)
{
    clorene::Compiler compiler;

    llvm::Module* module = compiler.compile(program_);

    ASSERT_TRUE(module != 0);

    clorene::FunctionRunner runner(module, "fill", ctxt_);

    runner.setArgs(args_);

    clorene::Engine e(1);
    e.addWorker(&runner, 0);

    e.waitForIdle();

    EXPECT_EQ(res_, -8);
}

