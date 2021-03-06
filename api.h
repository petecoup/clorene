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

#ifndef API_H_
#define API_H_

#include <CL/cl.h>
#include "memory/MemoryObject.h"
#include "command_queue/CommandQueue.h"
#include "program/Program.h"
#include "program/Kernel.h"
#include "Context.h"
#include "Platform.h"
#include "Device.h"

struct _cl_context : public clorene::Context
{
};

struct _cl_mem : public clorene::MemoryObject
{
};

struct _cl_command_queue : public clorene::CommandQueue
{
};

struct _cl_program : public clorene::Program
{
};

struct _cl_platform : public clorene::Platform
{
};

struct _cl_device : public clorene::Device
{
};

struct _cl_kernel : public clorene::Kernel
{
};

#endif

