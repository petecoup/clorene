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

#include "api.h"
#include "memory/MemoryObjectFactory.h"
#include "memory/Buffer.h"
#include "command_queue/CommandQueueFactory.h"
#include "command_queue/ReadBuffer.h"
#include "command_queue/WriteBuffer.h"
#include "program/ProgramFactory.h"
#include "program/Kernel.h"
#include "runtime/Engine.h"
#include "Context.h"
#include "ContextFactory.h"

#include <llvm/Support/TargetSelect.h>

cl_int
clGetPlatformIDs(cl_uint num_entries,
                 cl_platform_id* platforms,
                 cl_uint* num_platforms)
{
    llvm::InitializeNativeTarget();

    if (platforms == NULL) {
        *num_platforms = 1;
    } else if (num_entries == 1) {
        //TODO: fill out the platform.
    } else {
        return CL_INVALID_VALUE;
    }
    return CL_SUCCESS;
}

cl_int
clGetDeviceIDs(cl_platform_id platform,
               cl_device_type device_type,
               cl_uint num_entries,
               cl_device_id* devices,
               cl_uint* num_devices)
{
    switch (device_type) {
        case CL_DEVICE_TYPE_CPU:
        case CL_DEVICE_TYPE_DEFAULT:
        case CL_DEVICE_TYPE_ALL:
        {
            if (devices == NULL) {
                *num_devices = 1;
            } else if (num_entries == 1) {
                //TODO: fill in values.
            } else {
                return CL_INVALID_VALUE;
            }
            break;
        }
        case CL_DEVICE_TYPE_GPU:
        case CL_DEVICE_TYPE_ACCELERATOR:
        default:
        {
            return CL_INVALID_DEVICE_TYPE;
        }
    }
    return CL_SUCCESS;
}

cl_context
clCreateContext(const cl_context_properties* context_properties,
                cl_uint num_devices,
                const cl_device_id* devices,
                void (CL_CALLBACK * pfn_notify)(const char* errinfo,
                                                const void* private_info,
                                                size_t cb,
                                                void* user_data),
                void* user_data,
                cl_int* errcode_ret)
{
    //Where should this get hooked in?
    clorene::ContextFactory f;

    //TODO: hook this in with a device.
    clorene::Context* context = f.createContextForDevice(0);
    return (cl_context)context;
}
                
cl_mem
clCreateBuffer(cl_context context,
               cl_mem_flags flags,
               size_t size,
               void* ptr,
               cl_int* errcode)
{
    clorene::Context* ctxt = (clorene::Context*)context;        
    return (cl_mem)ctxt->memoryObjectFactory_->createBuffer(flags, size, ptr, errcode);
}

cl_program
clCreateProgramWithSource(cl_context context,
                          cl_uint count,
                          const char** strings,
                          const size_t* lengths,
                          cl_int* errcode_ret)
{
    clorene::Context* ctxt = (clorene::Context*)context;
    return (cl_program)ctxt->programFactory_->createProgram(count,
                                                            strings,
                                                            lengths,
                                                            errcode_ret);
}

cl_command_queue
clCreateCommandQueue(cl_context context,
                     cl_device_id device,
                     cl_command_queue_properties properties,
                     cl_int* errcode_ret)
{
    clorene::Context* ctxt = (clorene::Context*)context;
    return (cl_command_queue)ctxt->commandQueueFactory_->createCommandQueue(device, properties, errcode_ret);
}

cl_int
clBuildProgram(cl_program program,
  	       cl_uint num_devices,
  	       const cl_device_id* device_list,
  	       const char *options,
  	       void (*pfn_notify)(cl_program, void* user_data),
  	       void* user_data)
{
    clorene::Program* prg = (clorene::Program*)program;
    return prg->build();
}

cl_int
clGetProgramBuildInfo(cl_program program,
                      cl_device_id device,
                      cl_program_build_info param_name,
                      size_t param_value_size,
                      void* param_value,
                      size_t* param_value_size_ret)
{
    return CL_SUCCESS;
}

cl_int
clCreateKernelsInProgram(cl_program program,
                         cl_uint num_kernels,
                         cl_kernel* kernels,
                         cl_uint* num_kernels_ret)
{
    clorene::Program* prg = (clorene::Program*)program;
    return prg->createKernels(num_kernels, kernels, num_kernels_ret);
}

cl_kernel
clCreateKernel(cl_program program,
               const char* kernel_name,
               cl_int* errcode_ret)
{
    clorene::Program* prg = (clorene::Program*)program;
    return (cl_kernel)prg->createKernel(kernel_name, errcode_ret);
}

cl_int
clSetKernelArg(cl_kernel kernel,
               cl_uint arg_index,
               size_t arg_size,
               const void* arg_value)
{
    clorene::Kernel* clkernel = (clorene::Kernel*)kernel;
    const clorene::Buffer** clbuf = (const clorene::Buffer**)arg_value;

    void* buf;
    buf = (void*)(*clbuf)->data();

    //TODO: For now (just to get things off of the ground),
    //all items passed to clSetKernelArg will be &buf,
    // where buf is a buffer.
    llvm::GenericValue g(buf);

    clkernel->setKernelArg(arg_index, g);

    return CL_SUCCESS;
}

cl_int
clReleaseMemObject(cl_mem memobj)
{
    return CL_SUCCESS;
}

cl_int
clReleaseProgram(cl_program program)
{
    return CL_SUCCESS;
}

cl_int
clReleaseKernel(cl_kernel kernel)
{
    return CL_SUCCESS;
}

cl_int
clReleaseCommandQueue(cl_command_queue command_queue)
{
    return CL_SUCCESS;
}

cl_int
clReleaseContext(cl_context context)
{
    return CL_SUCCESS;
}

cl_int
clFinish(cl_command_queue command_queue)
{
    return CL_SUCCESS;
}

cl_int
clEnqueueWriteBuffer(cl_command_queue command_queue,
                     cl_mem buffer,
                     cl_bool blocking_write,
                     size_t offset,
                     size_t cb,
                     const void* ptr,
                     cl_uint num_events_in_wait_list,
                     const cl_event* event_wait_list,
                     cl_event* event)
{
    //Create the write buffer command, and put it in the command_queue

    clorene::Buffer* clbuffer = (clorene::Buffer*)buffer;
    clorene::Command* writeCmd = new clorene::WriteBuffer(ptr, clbuffer, cb);

    writeCmd->execute();

    return CL_SUCCESS;
}

cl_int
clEnqueueReadBuffer(cl_command_queue command_queue,
                    cl_mem buffer,
                    cl_bool blocking_read,
                    size_t offset,
                    size_t cb,
                    void* ptr,
                    cl_uint num_events_in_wait_list,
                    const cl_event* event_wait_list,
                    cl_event* event)
{
    //Create the read buffer command, and put it in the command_queue

    clorene::Buffer* clbuffer = (clorene::Buffer*)buffer;
    clorene::Command* readCmd = new clorene::ReadBuffer(clbuffer, ptr, cb);

    readCmd->execute();

    return CL_SUCCESS;
}

cl_int
clEnqueueNDRangeKernel(cl_command_queue command_queue,
                       cl_kernel kernel,
                       cl_uint work_dim,
                       const size_t* global_work_offset,
                       const size_t* global_work_size,
                       const size_t* local_work_size,
                       cl_uint num_events_in_wait_list,
                       const cl_event* event_wait_list,
                       cl_event* event)
{
    clorene::Kernel* clkernel = (clorene::Kernel*)kernel;

    if (clkernel == NULL) {
        return CL_INVALID_KERNEL;
    }

    if (global_work_offset != NULL) {
        return CL_INVALID_GLOBAL_OFFSET;
    }

    if (work_dim != 1) {
        //Right now, only support 1 dimensional work dimensions.
        return CL_INVALID_WORK_DIMENSION;
    }

    if (local_work_size == NULL) {
        return CL_INVALID_WORK_GROUP_SIZE;
    }

    size_t work_size = local_work_size[0];

    {
        clorene::Engine* engine = new clorene::Engine(work_size);
        engine->addWorkGroup(clkernel, work_size);
        engine->waitForIdle();
    }

    return CL_SUCCESS;
}

cl_int
clGetKernelWorkGroupInfo(cl_kernel kernel,
                         cl_device_id device,
                         cl_kernel_work_group_info param_name,
                         size_t param_value_size,
                         void* param_value,
                         size_t* param_value_size_ret)
{
    return CL_SUCCESS;
}


