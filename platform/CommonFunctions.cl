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

#include "PlatformStdlib.h"

float2 CLANG_OVERLOADABLE max(float2 x, float2 y)
{
    float2 result;
    result[0] = x[0] > y[0] ? x[0] : y[0];
    result[1] = x[1] > y[1] ? x[1] : y[1];
    return result;
}

float3 CLANG_OVERLOADABLE max(float3 x, float3 y)
{
    float3 result;
    result[0] = x[0] > y[0] ? x[0] : y[0];
    result[1] = x[1] > y[1] ? x[1] : y[1];
    result[2] = x[2] > y[2] ? x[2] : y[2];
    return result;
}

float4 CLANG_OVERLOADABLE max(float4 x, float4 y)
{
    float4 result;
    result[0] = x[0] > y[0] ? x[0] : y[0];
    result[1] = x[1] > y[1] ? x[1] : y[1];
    result[2] = x[2] > y[2] ? x[2] : y[2];
    result[3] = x[3] > y[3] ? x[3] : y[3];
    return result;
}

