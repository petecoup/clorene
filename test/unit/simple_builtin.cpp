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

class SimpleBuiltinTest: public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        val_[0] = -99;
        val_[1] = -88;
        program_ = "int get_global_id(); void fill(float* a) { int i = get_global_id(); a[i] = i; }\n";

        args_.push_back(llvm::GenericValue((void*)(&val_)));
    }

    llvm::LLVMContext ctxt_;
    std::string program_;
    float val_[2];

    std::vector<llvm::GenericValue> args_;
};

TEST_F(SimpleBuiltinTest, CompileAndRun)
{
    clorene::Compiler compiler;

    llvm::Module* module = compiler.compile(program_);

    ASSERT_TRUE(module != 0);

    clorene::FunctionRunner runner(module, "fill", ctxt_);

    runner.setArgs(args_);

    clorene::Engine e(2);
    e.addWorker(&runner, 0);
    e.addWorker(&runner, 1);

    e.waitForIdle();

    EXPECT_EQ(val_[0], 0);
    EXPECT_EQ(val_[1], 1);
}

