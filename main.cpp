#include <iostream>
#include <string>
#include <fstream>
#include <vector>
// Específico da aplicação
#include "geometry.h"
#include "color-and-image.h"
#include "sphere.h"
#include "utils.cpp"


using namespace std;


void render(const Sphere &sphere)
{
    constexpr unsigned int width = 1024;
    constexpr unsigned int height = 768;
    const int fov = M_PI/2.;

    FrameBuffer frameBuffer = {
        width: width,
        height: height,
        buffer: std::vector<RGB>(width * height),
    };

    for (size_t j = 0; j<height; j++) {
        for (size_t i = 0; i<width; i++) {
            float x =  (2*(i + 0.5)/(float)width  - 1)*tan(fov/2.)*width/(float)height;
            float y = -(2*(j + 0.5)/(float)height - 1)*tan(fov/2.);
            // std::cout << "antes  x: " << dir.x << "\n";
            Vec3f dir = Vec3f {x, y, -1}.normalize();
            // std::cout << "depois x: " << dir.x << "\n";
            frameBuffer.buffer[i+j*width] = cast_ray(Vec3f { 0, 0, 0 }, dir, sphere);
        }
    }

    saveFrameBuffertoPPMFile(frameBuffer, "image.ppm");
}

int main(int argc, char *argv[], char *envp[])
{
    // printEnv(envp);
    Vec3f center = {-3,    0,   -16};
    Sphere sphere(center, 2.0f);
    render(sphere);

    return 0;
}
