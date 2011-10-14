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

#include "Poco/ThreadPool.h"

#include "Engine.h"
#include "Worker.h"
#include "FunctionRunner.h"

namespace clorene
{

Engine::Engine(int numWorkers) :
    pool_(new Poco::ThreadPool(numWorkers, 2*numWorkers))
{
}

Engine::~Engine()
{
    waitForIdle();
    delete pool_;
}

void
Engine::addWorkGroup(Kernel* kernel, size_t numWorkItems)
{
    FunctionRunner* runner = new FunctionRunner(kernel);
    for(size_t i = 0; i < numWorkItems; i++) {
        addWorker(runner, i);
    }
}

void
Engine::addWorker(FunctionRunner* runner, int id)
{
    Worker* worker = new Worker(runner, id);
    pool_->start(*worker);
}

void
Engine::waitForIdle()
{
    pool_->joinAll();
}

}

