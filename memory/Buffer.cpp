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

#include <assert.h>
#include "Buffer.h"

namespace clorene
{

Buffer::Buffer(size_t size)
{
    data_ = new char[size];
    allocated_ = true;
}

Buffer::Buffer(void *ptr)
{
    assert(ptr != 0);
    data_ = (char *)ptr;
    allocated_ = false;
}

Buffer::~Buffer()
{
    if (allocated_) {
        delete [] data_;
    }
}

Buffer*
Buffer::createSubBuffer(cl_mem_flags flags,
                        cl_buffer_create_type buffer_create_type,
                        const void* buffer_create_info,
                        cl_int* errcode_ret)
{
    // Not implemented.
    return 0;
}

}

