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

#include "CL/cl.h"

class ApiFullTest: public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        for(size_t i = 0; i < 16; i++) {
            vals_[i] = i;
        }
        program_ = "__kernel void square(float *io)"
                   "{ int i = get_global_id(); io[i] = io[i] * io[i]; }\n";
        programcstr_ = program_.c_str();
    }

    std::string program_;
    const char* programcstr_;
    float vals_[16];
};

TEST_F(ApiFullTest, CompileAndRun)
{
    int error;
    cl_device_id device_id;

    cl_context context;
    cl_command_queue commandq;
    cl_program program;
    cl_kernel kernel;
    cl_mem buffer;

    context = clCreateContext(0, 1, &device_id,  NULL, NULL, &error);
    ASSERT_TRUE(context != NULL);

    commandq = clCreateCommandQueue(context, device_id, 0, &error);
    ASSERT_TRUE(commandq != NULL);

    program = clCreateProgramWithSource(context, 1, &programcstr_, NULL, &error);
    ASSERT_TRUE(program != NULL);

    error = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    ASSERT_TRUE(error == CL_SUCCESS);

    kernel = clCreateKernel(program, "square", &error);
    ASSERT_TRUE(kernel != NULL);
    ASSERT_TRUE(error == CL_SUCCESS);

    buffer = clCreateBuffer(context, CL_MEM_ALLOC_HOST_PTR, sizeof(float) * 16, NULL, NULL);
    ASSERT_TRUE(buffer != NULL);

    error = clEnqueueWriteBuffer(commandq, buffer, CL_TRUE, 0, sizeof(float) * 16, vals_, 0, NULL, NULL);
    ASSERT_TRUE(error == CL_SUCCESS);

    error = clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer);
    ASSERT_TRUE(error == CL_SUCCESS);

    size_t numItems = 16;
    error = clEnqueueNDRangeKernel(commandq, kernel, 1, NULL, NULL, &numItems, 0, NULL, NULL);
    ASSERT_TRUE(error == CL_SUCCESS);

    float result[16];
    error = clEnqueueReadBuffer(commandq, buffer, CL_TRUE, 0, sizeof(float) * 16, result, 0, NULL, NULL);
    ASSERT_TRUE(error == CL_SUCCESS);

    for (size_t i = 0; i < 16; i++) {
        EXPECT_EQ(result[i], i*i);
    }
}

