#pragma once

#define MYPI        3.141592653f

using u8  = unsigned char;
using s8  = char;
using u16 = unsigned short;
using s16 = short;
using u32 = unsigned int;
using s32 = int;
using f32 = float;
using f64 = double;


template<class T>
struct vec3{
    f32 x, y, z;
};

using vec3f = vec3<f32>;
using vec3s = vec3<s16>;
using vec3i = vec3<s32>;