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

#ifndef MEMORY_MEMORY_OBJECT_FACTORY_H_
#define MEMORY_MEMORY_OBJECT_FACTORY_H_

#include <set>

#include <stddef.h>

#include <CL/cl.h>

namespace clorene
{

class MemoryObject;

class MemoryObjectFactory
{
public:
    MemoryObject* createBuffer(cl_mem_flags flags,
                               size_t size,
                               void* host_ptr,
                               cl_int* errcode);

    MemoryObject* createSubBuffer(cl_mem buf,
                                  cl_mem_flags flags,
                                  cl_buffer_create_type buffer_create_type,
                                  const void* buffer_create_info,
                                  cl_int* errcode);

    MemoryObject* createImage2D(cl_mem_flags flags,
                                const cl_image_format* image_format,
                                size_t image_width,
                                size_t image_height,
                                size_t image_row_pitch,
                                void* host_ptr,
                                cl_int* errcode);

    MemoryObject* createImage3D(cl_mem_flags flags,
                                const cl_image_format* image_format,
                                size_t image_width,
                                size_t image_height,
                                size_t image_depth,
                                size_t image_row_pitch,
                                size_t image_slice_pitch,
                                void* host_ptr,
                                cl_int* errcode);

    cl_int retainMemObject(cl_mem memobj);

    cl_int releaseMemObject(cl_mem memobj);

    cl_int getSupportedImageFormats(cl_mem_flags flags,
                                    cl_mem_object_type image_type,
                                    cl_uint num_entries,
                                    cl_image_format* image_formats,
                                    cl_uint* num_image_formats);

    cl_int getMemObjectInfo(cl_mem memobj,
                            cl_mem_info param_name,
                            size_t param_value_size,
                            void* param_value,
                            size_t* param_value_size_ret);

    cl_int getImageInfo(cl_mem memobj,
                        cl_image_info param_name,
                        size_t param_value_size,
                        void* param_value,
                        size_t* param_value_size_ret);

    cl_int setMemObjectDestructorCallback(cl_mem memobj,
                                          void(CL_CALLBACK* pfn_notify)(cl_mem,void*),
                                          void* user_data );

protected:
    typedef std::set<MemoryObject*> MemObjectContainer;
    MemObjectContainer objects_;
};

}

#endif

