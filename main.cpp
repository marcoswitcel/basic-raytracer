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

void render(const vector<Sphere> &spheres, const std::vector<Light> &lights)
{
    constexpr unsigned int width = 1024;
    constexpr unsigned int height = 768;
    const int fov = M_PI / 2.;

    FrameBuffer frameBuffer = {
        width : width,
        height : height,
        buffer : vector<RGB>(width * height),
    };

    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            float x = (2 * (i + 0.5) / (float)width - 1) * tan(fov / 2.) * width / (float)height;
            float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);

            Vec3f dir = Vec3f{x, y, -1}.normalize();
            frameBuffer.buffer[i + j * width] = cast_ray(Vec3f{0, 0, 0}, dir, spheres, lights);
        }
    }

    for (RGB &rgb : frameBuffer.buffer)
    {
        float max = std::max(rgb.r, std::max(rgb.g, rgb.b));

        // @TODO quanto das cores chegam aqui elas já estão dentro do range 0 - 255
        // if (max > 255.f) {
        //     rgb = RGB{
        //         (uint8_t)(255 * ((float) rgb.r) * (255/max)),
        //         (uint8_t)(255 * ((float) rgb.g) * (255/max)),
        //         (uint8_t)(255 * ((float) rgb.b) * (255/max)),
        //     };
        // }

        rgb.r = std::max(0, std::min(255, (int)rgb.r));
        rgb.g = std::max(0, std::min(255, (int)rgb.g));
        rgb.b = std::max(0, std::min(255, (int)rgb.b));
    }

    // for (size_t i = 0; i < height*width; ++i) {
    //     Vec3f &c = frameBuffer.buffer[i];
    //     float max = std::max(c[0], std::max(c[1], c[2]));

    //     if (max>1) c = c*(1./max);
    //     for (size_t j = 0; j<3; j++) {
    //         ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
    //     }
    // }

    saveFrameBuffertoPPMFile(frameBuffer, "image.ppm");
}

int main(int argc, char *argv[], char *envp[])
{
    // printEnv(envp);

    Material ivory(Vec2f(0.6, 0.3), Vec3f(0.4, 0.4, 0.3), 50.);
    Material red_rubber(Vec2f(0.9, 0.1), Vec3f(0.3, 0.1, 0.1), 10.);

    vector<Sphere> spheres;

    spheres.push_back(Sphere(Vec3f(-3, 0, -16), 2, ivory));
    spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2, red_rubber));
    spheres.push_back(Sphere(Vec3f(1.5, -0.5, -18), 3, red_rubber));
    spheres.push_back(Sphere(Vec3f(7, 5, -18), 4, ivory));

    vector<Light> lights;
    lights.push_back(Light(Vec3f(-20, 20, 20), 1.5));
    lights.push_back(Light(Vec3f( 30, 50, -25), 1.8));
    lights.push_back(Light(Vec3f( 30, 20,  30), 1.7));

    render(spheres, lights);

    return 0;
}
