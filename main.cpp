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


void render(const vector<Sphere> &spheres)
{
    constexpr unsigned int width = 1024;
    constexpr unsigned int height = 768;
    const int fov = M_PI/2.;

    FrameBuffer frameBuffer = {
        width: width,
        height: height,
        buffer: vector<RGB>(width * height),
    };

    for (size_t j = 0; j<height; j++) {
        for (size_t i = 0; i<width; i++) {
            float x =  (2*(i + 0.5)/(float)width  - 1)*tan(fov/2.)*width/(float)height;
            float y = -(2*(j + 0.5)/(float)height - 1)*tan(fov/2.);
            // cout << "antes  x: " << dir.x << "\n";
            Vec3f dir = Vec3f {x, y, -1}.normalize();
            // cout << "depois x: " << dir.x << "\n";
            frameBuffer.buffer[i+j*width] = cast_ray(Vec3f { 0, 0, 0 }, dir, spheres);
        }
    }

    saveFrameBuffertoPPMFile(frameBuffer, "image.ppm");
}

int main(int argc, char *argv[], char *envp[]) 
{
    // printEnv(envp);
    Material ivory(Vec3f(0.4, 0.4, 0.3));
    Material red_rubber(Vec3f(0.3, 0.1, 0.1));
    vector<Sphere> spheres;

    spheres.push_back(Sphere(Vec3f(-3,    0,   -16), 2,      ivory));
    spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2, red_rubber));
    spheres.push_back(Sphere(Vec3f( 1.5, -0.5, -18), 3, red_rubber));
    spheres.push_back(Sphere(Vec3f( 7,    5,   -18), 4,      ivory));

    render(spheres);

    return 0;
}
