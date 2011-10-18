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

#ifndef PLATFORM_STDLIB_H_
#define PLATFORM_STDLIB_H_

// See http://clang.llvm.org/docs/LanguageExtensions.html for different
//  available extensions that we use here.

// define the variety of vector formats available (float2, float3, float4).
typedef float float2 __attribute__((ext_vector_type(2)));
typedef float float3 __attribute__((ext_vector_type(3)));
typedef float float4 __attribute__((ext_vector_type(4)));

typedef int int2 __attribute__((ext_vector_type(2)));
typedef int int3 __attribute__((ext_vector_type(3)));
typedef int int4 __attribute__((ext_vector_type(4)));

// Now, define builtin functions.

#define CLANG_OVERLOADABLE __attribute__((overloadable))
// Common functions
// clamp
float2 CLANG_OVERLOADABLE clamp(float2 x, float2 minval, float2 maxval);
float3 CLANG_OVERLOADABLE clamp(float3 x, float3 minval, float3 maxval);
float4 CLANG_OVERLOADABLE clamp(float4 x, float4 minval, float4 maxval);

float2 CLANG_OVERLOADABLE clamp(float2 x, float minval, float maxval);
float3 CLANG_OVERLOADABLE clamp(float3 x, float minval, float maxval);
float4 CLANG_OVERLOADABLE clamp(float4 x, float minval, float maxval);


//degrees
float2 CLANG_OVERLOADABLE degrees(float2 radians);
float3 CLANG_OVERLOADABLE degrees(float3 radians);
float4 CLANG_OVERLOADABLE degrees(float4 radians);

//max
float2 CLANG_OVERLOADABLE max(float2 x, float2 y);
float3 CLANG_OVERLOADABLE max(float3 x, float3 y);
float4 CLANG_OVERLOADABLE max(float4 x, float4 y);

float2 CLANG_OVERLOADABLE max(float2 x, float y);
float3 CLANG_OVERLOADABLE max(float3 x, float y);
float4 CLANG_OVERLOADABLE max(float4 x, float y);

//min
float2 CLANG_OVERLOADABLE min(float2 x, float2 y);
float3 CLANG_OVERLOADABLE min(float3 x, float3 y);
float4 CLANG_OVERLOADABLE min(float4 x, float4 y);

float2 CLANG_OVERLOADABLE min(float2 x, float y);
float3 CLANG_OVERLOADABLE min(float3 x, float y);
float4 CLANG_OVERLOADABLE min(float4 x, float y);

//mix: returns x + (y - x)*a
float2 CLANG_OVERLOADABLE mix(float2 x, float2 y, float2 a);
float3 CLANG_OVERLOADABLE mix(float3 x, float3 y, float3 a);
float4 CLANG_OVERLOADABLE mix(float4 x, float4 y, float4 a);

float2 CLANG_OVERLOADABLE mix(float2 x, float2 y, float a);
float3 CLANG_OVERLOADABLE mix(float3 x, float3 y, float a);
float4 CLANG_OVERLOADABLE mix(float4 x, float4 y, float a);

//degrees
float2 CLANG_OVERLOADABLE radians(float2 degrees);
float3 CLANG_OVERLOADABLE radians(float3 degrees);
float4 CLANG_OVERLOADABLE radians(float4 degrees);

//sign
float2 CLANG_OVERLOADABLE sign(float2 x);
float3 CLANG_OVERLOADABLE sign(float3 x);
float4 CLANG_OVERLOADABLE sign(float4 x);

//smoothstep: t = clamp((x - edge0)/(edge1 - edge0),0,1); return t*t*(3-2*t);
float2 CLANG_OVERLOADABLE smoothstep(float2 edge0, float2 edge1, float2 x);
float3 CLANG_OVERLOADABLE smoothstep(float3 edge0, float3 edge1, float3 x);
float4 CLANG_OVERLOADABLE smoothstep(float4 edge0, float4 edge1, float4 x);

float2 CLANG_OVERLOADABLE smoothstep(float edge0, float edge1, float2 x);
float3 CLANG_OVERLOADABLE smoothstep(float edge0, float edge1, float3 x);
float4 CLANG_OVERLOADABLE smoothstep(float edge0, float edge1, float4 x);

//step: 0 if x < edge, 1 if x >= edge
float2 CLANG_OVERLOADABLE step(float2 edge, float2 x);
float3 CLANG_OVERLOADABLE step(float3 edge, float3 x);
float4 CLANG_OVERLOADABLE step(float4 edge, float4 x);

float2 CLANG_OVERLOADABLE step(float edge, float2 x);
float3 CLANG_OVERLOADABLE step(float edge, float3 x);
float4 CLANG_OVERLOADABLE step(float edge, float4 x);

//Work-Item Functions
int get_global_id(int work_dim);

#endif

