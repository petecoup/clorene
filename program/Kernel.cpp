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

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/Interpreter.h>

#include "Kernel.h"

namespace clorene
{

Kernel::Kernel(llvm::Function* function, llvm::Module* hostModule) :
    function_(function),
    hostModule_(hostModule)
{
}

Kernel::~Kernel()
{
}

bool
Kernel::setKernelArg(size_t index, llvm::GenericValue value)
{
    //TODO: error checking.
    args_.push_back(value);

    return true;
}

llvm::Module*
Kernel::getModule()
{
    return hostModule_;
}

llvm::Function*
Kernel::getFunction()
{
    return function_;
}

const std::vector<llvm::GenericValue>&
Kernel::getArgs() const
{
    return args_;
}

void
Kernel::call()
{
    llvm::ExecutionEngine* engine = llvm::ExecutionEngine::create(hostModule_, true);
    engine->runFunction(function_, args_);
}


}

