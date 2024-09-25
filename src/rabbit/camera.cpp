#include "rabbit/camera.h"

namespace gplay {

namespace rabbit {

Camera::Camera() {}

Camera::Camera(Point3 lookfrom_point, Point3 lookat_point, Vec3 vup_direction, double vfov_angle,
               double image_aspect_ratio, int out_image_width, int num_samples_per_pixel,
               int max_depth, double variation_angle, double focus_distance, Color background_color)
    : lookfrom(lookfrom_point),
      lookat(lookat_point),
      vup(vup_direction),
      vfov(vfov_angle),
      aspect_ratio(image_aspect_ratio),
      image_width(out_image_width),
      samples_per_pixel(num_samples_per_pixel),
      max_bounce(max_depth),
      defocus_angle(variation_angle),
      focus_dist(focus_distance),
      bgcolor(background_color) {}

void Camera::Initialize() {
    _image_height = static_cast<int>(image_width/aspect_ratio);
    _image_height = _image_height < 1 ? 1 : _image_height;

    _pixel_samples_scale_factor = 1.0 / samples_per_pixel;

    _center = lookfrom;
    double viewport_height = 2 * focus_dist * std::tan(DegreesToRadians(vfov)/2);
    // use actual ratio between image_width and image_height instead of ideal aspect_ratio
    double viewport_width = static_cast<double>(image_width) / static_cast<double>(_image_height) * viewport_height;

    _w = UnitVec(lookfrom-lookat);
    _u = UnitVec(Vec3Cross(vup, _w));
    _v = Vec3Cross(_w, _u);

    Vec3 viewport_u = viewport_width * _u;
    Vec3 viewport_v = viewport_height * (-_v);
    _pixel_delta_u = viewport_u / image_width;
    _pixel_delta_v = viewport_v / _image_height;
    _viewport_upper_left = _center - viewport_u/2 - viewport_v/2 - (focus_dist * _w);
    _location_origin_pixel_grid = _viewport_upper_left + 0.5*_pixel_delta_u + 0.5*_pixel_delta_v;

    double defocus_disk_radius = focus_dist * std::tan(DegreesToRadians(defocus_angle) / 2);
    _defocus_disk_u = defocus_disk_radius * _u;
    _defocus_disk_v = defocus_disk_radius * _v;
}

Ray Camera::GetRay(int i, int j) const {
    Point3 offset_in_pixel = RandomPointInUnitSquare();
    Point3 target = _location_origin_pixel_grid +
                    _pixel_delta_u * (static_cast<double>(i)+offset_in_pixel.X()) +
                    _pixel_delta_v * (static_cast<double>(j)+offset_in_pixel.Y());
    Point3 origin = _center;
    if (defocus_angle > 0) {
        Point3 point_in_disk = RandomPointInUnitDisk();
        origin += point_in_disk.X()*_defocus_disk_u + point_in_disk.Y()*_defocus_disk_v;
    }
    return Ray(origin, target-origin, RandomDouble());
}

void Camera::SetBackgroundColor(Color color) {
    bgcolor = color;
}

int Camera::ImageWidth() const {
    return image_width;
}

int Camera::ImageHeight() const {
    return _image_height;
}

int Camera::SamplesPerPixel() const {
    return samples_per_pixel;
}

double Camera::PixelSamplesScaleFactor() const {
    return _pixel_samples_scale_factor;
}

int Camera::MaxBounce() const {
    return max_bounce;
}

const Color& Camera::BackgroundColor() const {
    return bgcolor;
}

} // namespace rabbit

} // namespace gplay
