#include <fstream>
#include <iostream>
#include <glm/vec3.hpp>

int main() {
    // Note that here we use C++ IO Redirection
    // Actually, if we don't do this, another choice is using bash pipe to write to an image file
    // Like this: ./ppm >> "ppm_demo.ppm"
    std::fstream file;
    file.open("ppm_demo.ppm", std::ios::out);
    std::streambuf *stream_buffer_cout = std::cout.rdbuf();
    std::streambuf *stream_buffer_file = file.rdbuf();
    std::cout.rdbuf(stream_buffer_file);

    int nx = 320;
    int ny = 180;
    std::cout << "P3\n" << nx << " " << ny << " " << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            glm::vec3 colorx(static_cast<float>(i) / static_cast<float>(nx),
                             static_cast<float>(j) / static_cast<float>(ny),
                             0.2);
            int ir = static_cast<int>(255.99 * colorx.r);
            int ig = static_cast<int>(255.99 * colorx.g);
            int ib = static_cast<int>(255.99 * colorx.b);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    std::cout.rdbuf(stream_buffer_cout);
    return 0;
}
