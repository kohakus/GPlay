#include "rabbit/draw.h"

namespace gplay {

namespace rabbit {

void WriteColor(std::ostream& out, const Color& pixel_color) {
    // Apply a linear to gamma transform for gamma 2
    auto r = LinearToGamma(pixel_color.R());
    auto g = LinearToGamma(pixel_color.G());
    auto b = LinearToGamma(pixel_color.B());

    // Translate the [0,1] component values to the byte range [0,255].
    static const Interval intensity(0.000, 0.999);
    int rbyte = static_cast<int>(256 * intensity.Clamp(r));
    int gbyte = static_cast<int>(256 * intensity.Clamp(g));
    int bbyte = static_cast<int>(256 * intensity.Clamp(b));

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

Color RayColor(const Ray& r, int depth_limit, const Camera& camera, const Hittable& world) {
    // If we have exceeded the ray bounce limit, no more light is gathered.
    if (depth_limit <= 0) {
        return Color(0,0,0);
    }

    HitRecord record;

    // If the ray hits nothing, return the background color.
    if (!world.Hit(r, Interval(0.001, kInfinity), record)) {
        return camera.BackgroundColor();
    }

    Ray scattered;
    Color attenuation;

    Color color_from_emission = record.material->Emitted(record.u, record.v, record.hitpoint);

    if (!record.material->Scatter(r, record, attenuation, scattered)) {
        return color_from_emission;
    }
    Color color_from_scatter = attenuation * RayColor(scattered, depth_limit-1, camera, world);

    return color_from_emission + color_from_scatter;
}

void RenderWorld(const Camera& camera, const Hittable& world, const std::string& outfile) {
    // Note that here we use C++ IO Redirection
    // Actually, if we don't do this, another choice is using bash pipe to write to an image file
    // Like this: ./main >> "xxx.ppm"

    std::fstream file;
    file.open(outfile, std::ios::out);
    std::streambuf* stream_buffer_cout = std::cout.rdbuf();
    std::streambuf* stream_buffer_file = file.rdbuf();
    std::cout.rdbuf(stream_buffer_file);

    std::cout << "P3\n" << camera.ImageWidth() << ' ' << camera.ImageHeight() << "\n255\n";
    for (int j = 0; j < camera.ImageHeight(); j++) {
        std::clog << "\rScanlines remaining: " << (camera.ImageHeight() - j) << ' ' << std::flush;
        for (int i = 0; i < camera.ImageWidth(); i++) {
            Color pixel_color(0,0,0);
            for (int sample = 0; sample < camera.SamplesPerPixel(); sample++) {
                Ray r = camera.GetRay(i, j);
                pixel_color += RayColor(r, camera.MaxBounce(), camera, world);
            }
            WriteColor(std::cout, camera.PixelSamplesScaleFactor() * pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";

    // restore cout buffer
    std::cout.rdbuf(stream_buffer_cout);
}

} // namespace rabbit

} // namespace gplay
