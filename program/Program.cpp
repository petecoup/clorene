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

#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Module.h>
#include "Program.h"
#include "Kernel.h"
#include "Compiler.h"

namespace clorene
{

Program::Program(cl_uint count, const char** lines, const size_t* lengths) :
    programSrc_()
{
    for (cl_uint i = 0; i < count; i++) {
        programSrc_ += lines[i];
    }
}

cl_int
Program::build()
{
    clorene::Compiler c;
    compiledModule_ =
        c.compile(programSrc_);

    if (compiledModule_ == 0) {
        return CL_BUILD_PROGRAM_FAILURE;
    }
    return CL_SUCCESS;
}

cl_int
Program::createKernels(cl_uint num_kernels, cl_kernel* kernels, cl_uint* num_kernels_ret)
{
    return CL_SUCCESS;
}

cl_kernel
Program::createKernel(const char* name, cl_int* errcode_ret)
{
    *errcode_ret = CL_SUCCESS;
    if (compiledModule_ == 0) {
        *errcode_ret = CL_INVALID_PROGRAM_EXECUTABLE;
        return 0;
    }

    llvm::Function* function = compiledModule_->getFunction(name);

    if (function == 0) {
        *errcode_ret = CL_INVALID_KERNEL_NAME;
        return 0;
    }

    //TODO: see if it is a kernel in the module, not just a function.
    
    Kernel* kernel = new Kernel(function, compiledModule_);
    kernels_.insert(std::make_pair(name, kernel));
    return (cl_kernel)kernel;
}

}

