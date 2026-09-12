#pragma once

#include <cstdint>

extern "C"
{
    void GetRayData(
        float RayX,
        float RayY,

        const float* Angle,

        const float* WallX1,
        const float* WallY1,
        const float* WallX2,
        const float* WallY2,

        std::int32_t RayCount,
        std::int32_t WallCount,

        float* OutputX,
        float* OutputY,
        float* OutputDist
    );
}