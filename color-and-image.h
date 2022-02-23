#ifndef _COLOR_AND_IMAGE_
#define _COLOR_AND_IMAGE_

#include <stdint.h>
#include <vector>

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct FrameBuffer {
    unsigned int width;
    unsigned int height;
    std::vector<RGB> buffer;
};

#endif