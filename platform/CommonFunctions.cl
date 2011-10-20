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

float CLANG_OVERLOADABLE degrees(float radians)
{
    return (radians * 180.0f) / M_PI_F;
}

float2 CLANG_OVERLOADABLE degrees(float2 radians)
{
    float2 result;
    int i = 0;
    for (i = 0; i < 2; i++) {
        result[i] = degrees(radians[i]);
    }
    return result;
}

float3 CLANG_OVERLOADABLE degrees(float3 radians)
{
    float3 result;
    int i = 0;
    for (i = 0; i < 3; i++) {
        result[i] = degrees(radians[i]);
    }
    return result;
}

float4 CLANG_OVERLOADABLE degrees(float4 radians)
{
    float4 result;
    int i = 0;
    for (i = 0; i < 4; i++) {
        result[i] = degrees(radians[i]);
    }
    return result;
}

float8 CLANG_OVERLOADABLE degrees(float8 radians)
{
    float8 result;
    int i = 0;
    for (i = 0; i < 8; i++) {
        result[i] = degrees(radians[i]);
    }
    return result;
}

float16 CLANG_OVERLOADABLE degrees(float16 radians)
{
    float16 result;
    int i = 0;
    for (i = 0; i < 16; i++) {
        result[i] = degrees(radians[i]);
    }
    return result;
}

// max -----------------------------------------------------------------------

float CLANG_OVERLOADABLE max(float x, float y)
{
    return (x > y ? x : y);
}

float2 CLANG_OVERLOADABLE max(float2 x, float2 y)
{
    float2 result;
    int i = 0;
    for(i = 0;i < 2;i++) {
        result[i] = max(x[i], y[i]);
    }
    return result;
}

float3 CLANG_OVERLOADABLE max(float3 x, float3 y)
{
    float3 result;
    int i = 0;
    for(i = 0;i < 3;i++) {
        result[i] = max(x[i], y[i]);
    }
    return result;
}

float4 CLANG_OVERLOADABLE max(float4 x, float4 y)
{
    float4 result;
    int i = 0;
    for(i = 0;i < 4;i++) {
        result[i] = max(x[i], y[i]);
    }
    return result;
}

float8 CLANG_OVERLOADABLE max(float8 x, float8 y)
{
    float8 result;
    int i = 0;
    for(i = 0;i < 8;i++) {
        result[i] = max(x[i], y[i]);
    }
    return result;
}

float16 CLANG_OVERLOADABLE max(float16 x, float16 y)
{
    float16 result;
    int i = 0;
    for(i = 0;i < 16;i++) {
        result[i] = max(x[i], y[i]);
    }
    return result;
}

// min -----------------------------------------------------------------------

float CLANG_OVERLOADABLE min(float x, float y)
{
    return (x < y ? x : y);
}

float2 CLANG_OVERLOADABLE min(float2 x, float2 y)
{
    float2 result;
    int i = 0;
    for(i = 0;i < 2;i++) {
        result[i] = min(x[i], y[i]);
    }
    return result;
}

float3 CLANG_OVERLOADABLE min(float3 x, float3 y)
{
    float3 result;
    int i = 0;
    for(i = 0;i < 3;i++) {
        result[i] = min(x[i], y[i]);
    }
    return result;
}

float4 CLANG_OVERLOADABLE min(float4 x, float4 y)
{
    float4 result;
    int i = 0;
    for(i = 0;i < 4;i++) {
        result[i] = min(x[i], y[i]);
    }
    return result;
}

float8 CLANG_OVERLOADABLE min(float8 x, float8 y)
{
    float8 result;
    int i = 0;
    for(i = 0;i < 8;i++) {
        result[i] = min(x[i], y[i]);
    }
    return result;
}

float16 CLANG_OVERLOADABLE min(float16 x, float16 y)
{
    float16 result;
    int i = 0;
    for(i = 0;i < 16;i++) {
        result[i] = min(x[i], y[i]);
    }
    return result;
}

