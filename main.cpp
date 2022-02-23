#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// Específico da aplicação
#include "geometry.h"
#include "color-and-image.h"
#include "sphere.h"

using namespace std;

/**
 * @note Exemplo com variáveis de ambiente
 * @url https://docs.microsoft.com/pt-br/cpp/cpp/main-function-command-line-args?view=msvc-160#example-arguments-to-main
 */
void printEnv(char* envp[])
{
    // Walk through list of strings until a NULL is encountered.
    for (int i = 0; envp[i++];)
    {
        cout << envp[i] << "\n";
    }
}

/**
 * Ideia
 * @note https://stackoverflow.com/questions/19813443/quick-way-to-output-a-picture-in-c#answer-19813498
 * Exemplo de implementação
 * @note https://rosettacode.org/wiki/Bitmap/Write_a_PPM_file#C.2B.2B
 * Sobre o formato
 * @note http://paulbourke.net/dataformats/ppm/
 */
void writePPM()
{
    constexpr auto dimx = 800u, dimy = 800u;

    ofstream ofs("image.ppm", ios_base::out | ios_base::binary);

    ofs << "P6" << endl << dimx << ' ' << dimy << endl << "255" << endl;

    for (auto j = 0u; j < dimy; ++j)
    {
        for (auto i = 0u; i < dimx; ++i)
        {
            ofs << (char) (i % 256) << (char) (j % 256) << (char) ((i * j) % 256);  // red, green, blue 
        }
    }

    ofs.close();
}




void savePPM(const FrameBuffer &frameBuffer)
{
    auto dimx = frameBuffer.width, dimy = frameBuffer.height;

    ofstream ofs("image.ppm", ios_base::out | ios_base::binary);

    ofs << "P6" << endl << dimx << ' ' << dimy << endl << "255" << endl;

    for (const RGB &color : frameBuffer.buffer) {
        ofs << (char) color.r << (char) color.g << (char) color.b;  // red, green, blue 
    }

    ofs.close();
}

void render(const Sphere &sphere)
{
    const unsigned int width = 1024;
    const unsigned int height = 768;
    const int fov = M_PI/2.;


    FrameBuffer frameBuffer = {
        width: width,
        height: height,
        buffer: std::vector<RGB>(width * height),
    };

    // for (RGB &color : frameBuffer.buffer) {
    //     // rgb(50, 178, 203);
    //     color.r = 50; 
    //     color.g = 178;
    //     color.b = 203;
    // }
    for (size_t j = 0; j<height; j++) {
        for (size_t i = 0; i<width; i++) {
            float x =  (2*(i + 0.5)/(float)width  - 1)*tan(fov/2.)*width/(float)height;
            float y = -(2*(j + 0.5)/(float)height - 1)*tan(fov/2.);
            vec3 dir = vec3 {x, y, -1};
            // std::cout << "antes  x: " << dir.x << "\n";
            dir = normalize(dir);
            // std::cout << "depois x: " << dir.x << "\n";
            frameBuffer.buffer[i+j*width] = cast_ray(vec3 { 0, 0, 0 }, dir, sphere);
        }
    }

    savePPM(frameBuffer);
}

int main(int argc, char *argv[], char *envp[])
{
    // printEnv(envp);

    vec3 center = {-3,    0,   -16};
    Sphere sphere(center, 2.0f);
    render(sphere);

    return 0;
}
