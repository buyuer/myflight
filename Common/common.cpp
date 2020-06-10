#include "common.hpp"

#include "arm_math.h"

void mf::PostureCalculate(vec3f& acc, vec3f& gyro, vec3f& out, f32 dt, f32 ki)
{
    f32 kxz = acc.x / acc.z;
    f32 kyz = acc.y / acc.z;
    
    f32 gxi = gyro.x * dt;
    f32 gyi = gyro.y * dt;
    f32 gzi = gyro.z * dt;
    
    out.x = ( (out.x + gyro.x * dt) * ki) + ( atan(kxz) * (1 - ki) );
    out.y = ( (out.y + gyro.y * dt) * ki) + ( atan(kyz) * (1 - ki) );
    out.z = out.z + gyro.z * dt;
}