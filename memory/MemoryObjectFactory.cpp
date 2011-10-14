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

#include "MemoryObjectFactory.h"
#include "MemoryObject.h"
#include "Buffer.h"

namespace clorene
{

inline void setIfNotNull(cl_int* errcode, cl_int value)
{
    if (errcode)
        *errcode = value;
}

MemoryObject*
MemoryObjectFactory::createBuffer(cl_mem_flags flags,
                                  size_t size,
                                  void* host_ptr,
                                  cl_int* errcode_ret)
{
    setIfNotNull(errcode_ret, CL_SUCCESS);
    if (flags & CL_MEM_USE_HOST_PTR) {
        if (!host_ptr) {
            setIfNotNull(errcode_ret, CL_INVALID_HOST_PTR);
            return 0;
        } else {
            MemoryObject* newobj = new Buffer(host_ptr);
            objects_.insert(newobj);
            return newobj;
        }
    }

    if (flags & CL_MEM_ALLOC_HOST_PTR) {
        MemoryObject* newobj = new Buffer(size);
        objects_.insert(newobj);
        return newobj;
    }

    MemoryObject* newobj = new Buffer(size);
    objects_.insert(newobj);
    return newobj;

    //There should be a case which triggers this?
    setIfNotNull(errcode_ret, CL_INVALID_VALUE);
    return 0;
}

MemoryObject*
MemoryObjectFactory::createSubBuffer(cl_mem buffer,
                                     cl_mem_flags flags,
                                     cl_buffer_create_type buffer_create_type,
                                     const void* buffer_create_info,
                                     cl_int* errcode_ret)
{
    return 0;
}

MemoryObject*
MemoryObjectFactory::createImage2D(cl_mem_flags flags,
                                   const cl_image_format* image_format,
                                   size_t image_width,
                                   size_t image_height,
                                   size_t image_row_pitch,
                                   void* host_ptr,
                                   cl_int* errcode_ret)
{
    return 0;
}

MemoryObject*
MemoryObjectFactory::createImage3D(cl_mem_flags flags,
                                   const cl_image_format* image_format,
                                   size_t image_width,
                                   size_t image_height,
                                   size_t image_depth,
                                   size_t image_row_pitch,
                                   size_t image_slice_pitch,
                                   void* host_ptr,
                                   cl_int* errcode_ret)
{
    return 0;
}

cl_int
MemoryObjectFactory::retainMemObject(cl_mem memobj)
{
    if (objects_.find((MemoryObject*)memobj) != objects_.end()) {
        MemoryObject* obj = (MemoryObject*)memobj;
        obj->addRef();
        return CL_SUCCESS;
    } else {
        return CL_INVALID_MEM_OBJECT;
    }
}

cl_int
MemoryObjectFactory::releaseMemObject(cl_mem memobj)
{
    MemObjectContainer::iterator it = objects_.find((MemoryObject*)memobj);

    if (it != objects_.end()) {
        MemoryObject* obj = (MemoryObject*)memobj;
        obj->removeRef();

        if (obj->numRefs() == 0) {
            delete obj;
            objects_.erase(it);
        }
        return CL_SUCCESS;
    } else {
        return CL_INVALID_MEM_OBJECT;
    }
}

}

