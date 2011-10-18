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

#include <iostream>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Linker.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/system_error.h>
#include <llvm/ADT/OwningPtr.h>

#include "program/Kernel.h"
#include "FunctionRunner.h"

extern void* lookup_function(const std::string&);

namespace clorene
{

FunctionRunner::FunctionRunner(llvm::Module* module,
                               const std::string& functionName,
                               llvm::LLVMContext& ctxt,
                               bool linkStdlib) :
    module_(module),
    functionName_(functionName),
    linkStdlib_(linkStdlib)
{
    init();
    initEngineAndFunction();
}

FunctionRunner::FunctionRunner(const std::string& moduleName,
                               const std::string& functionName,
                               llvm::LLVMContext& ctxt,
                               bool linkStdlib) :
    functionName_(functionName),
    linkStdlib_(linkStdlib)
{
    init();
    llvm::OwningPtr<llvm::MemoryBuffer> bufptr;
    llvm::MemoryBuffer::getFile(moduleName, bufptr);

    module_ = llvm::ParseBitcodeFile(bufptr.get(), ctxt);

    if (!module_) {
        std::cerr << "Could not load module from bitcode file " << moduleName << std::endl;
    }

    initEngineAndFunction();
}

FunctionRunner::FunctionRunner(Kernel* kernel,
                               bool linkStdlib) :
    module_(kernel->getModule()),
    function_(kernel->getFunction()),
    args_(kernel->getArgs()),
    linkStdlib_(linkStdlib)
{
    init();
    initEngine();
}

void
FunctionRunner::initEngine()
{
    if (linkStdlib_) {
        llvm::Linker linker("program", module_);

        bool native;
        llvm::sys::Path mypath;
        mypath.set("stdlib.bc");

        //Linker returns false on success.
        if (!linker.LinkInFile(mypath, native)) {
            module_ = linker.releaseModule();
        } else {
            //Error in linking.
            std::cerr << "Error linking module." << std::endl;
        }
    }

    engine_ = llvm::ExecutionEngine::createJIT(module_);

    if (!engine_) {
        std::cerr << "Could not create engine " << std::endl;
    }

    engine_->InstallLazyFunctionCreator(&lookup_function);
}

void
FunctionRunner::initEngineAndFunction()
{
    initEngine();

    function_ = module_->getFunction(functionName_);

    if (!function_) {
        std::cerr << "Could not find function " << functionName_ << " in passed module." << std::endl;
    }

}

void
FunctionRunner::init()
{
    llvm::InitializeNativeTarget();
}

void
FunctionRunner::setArgs(std::vector<llvm::GenericValue> args)
{
    args_ = args;
}

void
FunctionRunner::resetArgs()
{
    args_.clear();
}

void
FunctionRunner::run()
{
    engine_->runFunction(function_, args_);
}

}

