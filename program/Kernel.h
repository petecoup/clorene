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

#ifndef PROGRAM_KERNEL_H_
#define PROGRAM_KERNEL_H_

#include <vector>
#include <llvm/ExecutionEngine/GenericValue.h>

namespace llvm
{

class Function;
class Module;

};

namespace clorene
{

class Kernel
{
public:
    Kernel(llvm::Function* function, llvm::Module* hostModule);
    ~Kernel();

    bool setKernelArg(size_t index, llvm::GenericValue value);

    void call();

    llvm::Module* getModule();
    llvm::Function* getFunction();
    const std::vector<llvm::GenericValue>& getArgs() const;

private:
    llvm::Function* function_;
    llvm::Module* hostModule_;
    std::vector<llvm::GenericValue> args_;
};

}

#endif

