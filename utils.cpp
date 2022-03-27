#ifndef _UTILS_C_
#define _UTILS_C_

#include <iostream>
#include <fstream>
// Específico da aplicação
#include "color-and-image.h"


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
 * @note https://en.wikipedia.org/wiki/Netpbm#PPM_example
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

void saveFrameBuffertoPPMFile(const FrameBuffer &frameBuffer, const char* filename)
{
    auto dimx = frameBuffer.width, dimy = frameBuffer.height;
    ofstream ofs(filename, ios_base::out | ios_base::binary);

    ofs << "P6" << endl << dimx << ' ' << dimy << endl << "255" << endl;
    for (const RGB &color : frameBuffer.buffer)
    {
        ofs << (char) color.r << (char) color.g << (char) color.b;
    }

    ofs.close();
}

#endif
