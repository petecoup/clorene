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

// clamp ---------------------------------------------------------------------

float CLANG_OVERLOADABLE clamp(float x, float minval, float maxval)
{
    return min(fmax(x, minval), maxval);
}

float2 CLANG_OVERLOADABLE clamp(float2 x, float2 minval, float2 maxval)
{
    float2 result;
    int i = 0;
    for (i = 0; i < 2; i++) {
        result[i] = clamp(x[i], minval[i], maxval[i]);
    }
    return result;
}

float3 CLANG_OVERLOADABLE clamp(float3 x, float3 minval, float3 maxval)
{
    float3 result;
    int i = 0;
    for (i = 0; i < 3; i++) {
        result[i] = clamp(x[i], minval[i], maxval[i]);
    }
    return result;
}

float4 CLANG_OVERLOADABLE clamp(float4 x, float4 minval, float4 maxval)
{
    float4 result;
    int i = 0;
    for (i = 0; i < 4; i++) {
        result[i] = clamp(x[i], minval[i], maxval[i]);
    }
    return result;
}

float8 CLANG_OVERLOADABLE clamp(float8 x, float8 minval, float8 maxval)
{
    float8 result;
    int i = 0;
    for (i = 0; i < 8; i++) {
        result[i] = clamp(x[i], minval[i], maxval[i]);
    }
    return result;
}

float16 CLANG_OVERLOADABLE clamp(float16 x, float16 minval, float16 maxval)
{
    float16 result;
    int i = 0;
    for (i = 0; i < 16; i++) {
        result[i] = clamp(x[i], minval[i], maxval[i]);
    }
    return result;
}

// degrees -------------------------------------------------------------------

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
    for (i = 0; i < 2; i++) {
        result[i] = max(x[i], y[i]);
    }
    return result;
}

float3 CLANG_OVERLOADABLE max(float3 x, float3 y)
{
    float3 result;
    int i = 0;
    for (i = 0; i < 3; i++) {
        result[i] = max(x[i], y[i]);
    }
    return result;
}

float4 CLANG_OVERLOADABLE max(float4 x, float4 y)
{
    float4 result;
    int i = 0;
    for (i = 0; i < 4; i++) {
        result[i] = max(x[i], y[i]);
    }
    return result;
}

float8 CLANG_OVERLOADABLE max(float8 x, float8 y)
{
    float8 result;
    int i = 0;
    for (i = 0; i < 8; i++) {
        result[i] = max(x[i], y[i]);
    }
    return result;
}

float16 CLANG_OVERLOADABLE max(float16 x, float16 y)
{
    float16 result;
    int i = 0;
    for (i = 0; i < 16; i++) {
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
    for (i = 0; i < 2; i++) {
        result[i] = min(x[i], y[i]);
    }
    return result;
}

float3 CLANG_OVERLOADABLE min(float3 x, float3 y)
{
    float3 result;
    int i = 0;
    for (i = 0; i < 3; i++) {
        result[i] = min(x[i], y[i]);
    }
    return result;
}

float4 CLANG_OVERLOADABLE min(float4 x, float4 y)
{
    float4 result;
    int i = 0;
    for (i = 0; i < 4; i++) {
        result[i] = min(x[i], y[i]);
    }
    return result;
}

float8 CLANG_OVERLOADABLE min(float8 x, float8 y)
{
    float8 result;
    int i = 0;
    for (i = 0; i < 8; i++) {
        result[i] = min(x[i], y[i]);
    }
    return result;
}

float16 CLANG_OVERLOADABLE min(float16 x, float16 y)
{
    float16 result;
    int i = 0;
    for (i = 0; i < 16; i++) {
        result[i] = min(x[i], y[i]);
    }
    return result;
}

// mix -----------------------------------------------------------------------

float CLANG_OVERLOADABLE mix(float x, float y, float a)
{
    return x + (y - x)*a;
}

float2 CLANG_OVERLOADABLE mix(float2 x, float2 y, float2 a)
{
    float2 result;
    int i = 0;
    for (i = 0; i < 2; i++) {
        result[i] = mix(x[i], y[i], a[i]);
    }
    return result;
}

float3 CLANG_OVERLOADABLE mix(float3 x, float3 y, float3 a)
{
    float3 result;
    int i = 0;
    for (i = 0; i < 3; i++) {
        result[i] = mix(x[i], y[i], a[i]);
    }
    return result;
}

float4 CLANG_OVERLOADABLE mix(float4 x, float4 y, float4 a)
{
    float4 result;
    int i = 0;
    for (i = 0; i < 4; i++) {
        result[i] = mix(x[i], y[i], a[i]);
    }
    return result;
}

float8 CLANG_OVERLOADABLE mix(float8 x, float8 y, float8 a)
{
    float8 result;
    int i = 0;
    for (i = 0; i < 8; i++) {
        result[i] = mix(x[i], y[i], a[i]);
    }
    return result;
}

float16 CLANG_OVERLOADABLE mix(float16 x, float16 y, float16 a)
{
    float16 result;
    int i = 0;
    for (i = 0; i < 16; i++) {
        result[i] = mix(x[i], y[i], a[i]);
    }
    return result;
}

// radians -------------------------------------------------------------------

float CLANG_OVERLOADABLE radians(float degrees)
{
    return (M_PI_F * degrees) / 180.0f;
}

float2 CLANG_OVERLOADABLE radians(float2 degrees)
{
    float2 result;
    int i = 0;
    for (i = 0; i < 2; i++) {
        result[i] = radians(degrees[i]);
    }
    return result;
}

float3 CLANG_OVERLOADABLE radians(float3 degrees)
{
    float3 result;
    int i = 0;
    for (i = 0; i < 3; i++) {
        result[i] = radians(degrees[i]);
    }
    return result;
}

float4 CLANG_OVERLOADABLE radians(float4 degrees)
{
    float4 result;
    int i = 0;
    for (i = 0; i < 4; i++) {
        result[i] = radians(degrees[i]);
    }
    return result;
}

float8 CLANG_OVERLOADABLE radians(float8 degrees)
{
    float8 result;
    int i = 0;
    for (i = 0; i < 8; i++) {
        result[i] = radians(degrees[i]);
    }
    return result;
}

float16 CLANG_OVERLOADABLE radians(float16 degrees)
{
    float16 result;
    int i = 0;
    for (i = 0; i < 16; i++) {
        result[i] = radians(degrees[i]);
    }
    return result;
}

// sign ----------------------------------------------------------------------

// TODO: nan support
float CLANG_OVERLOADABLE sign(float x)
{
    if (x == 0.0f) {
        return 0.0f;
    }
    return (x > 0.0f ? 1.0f : -1.0f);
}

float2 CLANG_OVERLOADABLE sign(float2 x)
{
    float2 result;
    int i = 0;
    for (i = 0; i < 2; i++) {
        result[i] = sign(x[i]);
    }
    return result;
}

float3 CLANG_OVERLOADABLE sign(float3 x)
{
    float3 result;
    int i = 0;
    for (i = 0; i < 3; i++) {
        result[i] = sign(x[i]);
    }
    return result;
}

float4 CLANG_OVERLOADABLE sign(float4 x)
{
    float4 result;
    int i = 0;
    for (i = 0; i < 4; i++) {
        result[i] = sign(x[i]);
    }
    return result;
}

float8 CLANG_OVERLOADABLE sign(float8 x)
{
    float8 result;
    int i = 0;
    for (i = 0; i < 8; i++) {
        result[i] = sign(x[i]);
    }
    return result;
}

float16 CLANG_OVERLOADABLE sign(float16 x)
{
    float16 result;
    int i = 0;
    for (i = 0; i < 16; i++) {
        result[i] = sign(x[i]);
    }
    return result;
}

// smoothstep ----------------------------------------------------------------

float CLANG_OVERLOADABLE smoothstep(float edge0, float edge1, float x)
{
    float t = clamp((x - edge0)/(edge1 - edge0), 0, 1);
    return t*t*(3 - 2*t);
}

float2 CLANG_OVERLOADABLE smoothstep(float2 edge0, float2 edge1, float2 x)
{
    float2 result;
    int i = 0;
    for (i = 0; i < 2; i++) {
        result[i] = smoothstep(edge0[i], edge1[i], x[i]);
    }
    return result;
}

float3 CLANG_OVERLOADABLE smoothstep(float3 edge0, float3 edge1, float2 x)
{
    float3 result;
    int i = 0;
    for (i = 0; i < 3; i++) {
        result[i] = smoothstep(edge0[i], edge1[i], x[i]);
    }
    return result;
}

float4 CLANG_OVERLOADABLE smoothstep(float4 edge0, float4 edge1, float4 x)
{
    float4 result;
    int i = 0;
    for (i = 0; i < 4; i++) {
        result[i] = smoothstep(edge0[i], edge1[i], x[i]);
    }
    return result;
}

float8 CLANG_OVERLOADABLE smoothstep(float8 edge0, float8 edge1, float8 x)
{
    float8 result;
    int i = 0;
    for (i = 0; i < 8; i++) {
        result[i] = smoothstep(edge0[i], edge1[i], x[i]);
    }
    return result;
}

float16 CLANG_OVERLOADABLE smoothstep(float16 edge0, float16 edge1, float16 x)
{
    float16 result;
    int i = 0;
    for (i = 0; i < 16; i++) {
        result[i] = smoothstep(edge0[i], edge1[i], x[i]);
    }
    return result;
}

// step ----------------------------------------------------------------------

float CLANG_OVERLOADABLE step(float edge, float x)
{
    return (x < edge ? 0.0f : 1.0f);
}

float2 CLANG_OVERLOADABLE step(float2 edge, float2 x)
{
    float2 result;
    int i = 0;
    for (i = 0; i < 2; i++) {
        result[i] = step(edge[i], x[i]);
    }
    return result;
}

float3 CLANG_OVERLOADABLE step(float3 edge, float3 x)
{
    float3 result;
    int i = 0;
    for (i = 0; i < 3; i++) {
        result[i] = step(edge[i], x[i]);
    }
    return result;
}

float4 CLANG_OVERLOADABLE step(float4 edge, float4 x)
{
    float4 result;
    int i = 0;
    for (i = 0; i < 4; i++) {
        result[i] = step(edge[i], x[i]);
    }
    return result;
}

float8 CLANG_OVERLOADABLE step(float8 edge, float8 x)
{
    float8 result;
    int i = 0;
    for (i = 0; i < 8; i++) {
        result[i] = step(edge[i], x[i]);
    }
    return result;
}

float16 CLANG_OVERLOADABLE step(float16 edge, float16 x)
{
    float16 result;
    int i = 0;
    for (i = 0; i < 16; i++) {
        result[i] = step(edge[i], x[i]);
    }
    return result;
}

// ***************************************************************************
// Math Functions
// ***************************************************************************

// TODO: nan support (note, this looks a lot like max).

float CLANG_OVERLOADABLE fmax(float x, float y)
{
    return max(x, y);
}

float2 CLANG_OVERLOADABLE fmax(float2 x, float2 y)
{
    float2 result;
    int i = 0;
    for (i = 0; i < 2; i++) {
        result[i] = fmax(x[i], y[i]);
    }
    return result;
}

float3 CLANG_OVERLOADABLE fmax(float3 x, float3 y)
{
    float3 result;
    int i = 0;
    for (i = 0; i < 3; i++) {
        result[i] = fmax(x[i], y[i]);
    }
    return result;
}

float4 CLANG_OVERLOADABLE fmax(float4 x, float4 y)
{
    float4 result;
    int i = 0;
    for (i = 0; i < 4; i++) {
        result[i] = fmax(x[i], y[i]);
    }
    return result;
}

float8 CLANG_OVERLOADABLE fmax(float8 x, float8 y)
{
    float8 result;
    int i = 0;
    for (i = 0; i < 8; i++) {
        result[i] = fmax(x[i], y[i]);
    }
    return result;
}

float16 CLANG_OVERLOADABLE fmax(float16 x, float16 y)
{
    float16 result;
    int i = 0;
    for (i = 0; i < 16; i++) {
        result[i] = fmax(x[i], y[i]);
    }
    return result;
}

