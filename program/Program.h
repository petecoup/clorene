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

#ifndef PROGRAM_PROGRAM_H_
#define PROGRAM_PROGRAM_H_

#include <string>
#include <map>
#include <CL/cl.h>

namespace llvm
{

class Module;
class Function;

}

namespace clorene
{

class Kernel;

class Program
{
public:
    Program(cl_uint count, const char** strings, const size_t* lengths);

    cl_int build();
    cl_int createKernels(cl_uint num_kernels, cl_kernel* kernels, cl_uint* num_kernels_ret);

    cl_kernel createKernel(const char* name, cl_int* errcode_ret);
private:
    std::string programSrc_;
    llvm::Module* compiledModule_;

    std::map<std::string, Kernel*> kernels_;
};

}

#endif

