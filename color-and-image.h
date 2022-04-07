#ifndef _COLOR_AND_IMAGE_H_
#define _COLOR_AND_IMAGE_H_

#include <stdint.h>
#include <vector>
#include "geometry.h"

struct S_RGB
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct FrameBuffer
{
    unsigned int width;
    unsigned int height;
    std::vector<Vec3f> buffer;
};

#endif
