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

#ifndef FUNCTION_RUNNER_H_
#define FUNCTION_RUNNER_H_

#include <string>
#include <vector>

#include <llvm/ExecutionEngine/GenericValue.h>

namespace llvm
{

class Module;
class ExecutionEngine;
class Function;
class LLVMContext;

}

namespace clorene
{

class Kernel;

class FunctionRunner
{
public:
    FunctionRunner(llvm::Module* module,
                   const std::string& functionName,
                   llvm::LLVMContext& ctxt,
                   bool linkStdlib = false);

    FunctionRunner(const std::string& moduleName,
                   const std::string& functionName,
                   llvm::LLVMContext& ctxt,
                   bool linkStdlib = false);

    FunctionRunner(Kernel* kernel,
                   bool linkStdlib = false);

    void setArgs(std::vector<llvm::GenericValue> args);
    void resetArgs();
    void run();

protected:
    void init();
    void initEngine();
    void initEngineAndFunction();

private:
    llvm::Module* module_;
    llvm::ExecutionEngine* engine_;
    llvm::Function* function_;
    std::string functionName_;
    std::vector<llvm::GenericValue> args_;
    bool linkStdlib_;
};

}

#endif

