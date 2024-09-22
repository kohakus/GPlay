#ifndef GPLAY_RABBIT_CAMERA_H
#define GPLAY_RABBIT_CAMERA_H
/*
Class Camera
- Positionable
- Antialiasing
- Field of View
- Pinhole or Thin Lens Approximation (Defocus Blur/Depth of Field)
- Motion Blur
*/

#include "rabbit/mathtools.h"
#include "rabbit/ray.h"

namespace gplay {

namespace rabbit {

class Camera {
public:
    Camera();
    Camera(Point3 lookfrom_point, Point3 lookat_point, Vec3 vup_direction, double vfov_angle,
           double image_aspect_ratio, int out_image_width, int num_samples_per_pixel,
           int max_depth, double variation_angle, double focus_distance, Color background_color);

    // Initialize ...
    void Initialize();

    // SetBackgroundColor ...
    void SetBackgroundColor(Color color);

    // GetRay construct a camera ray originating from the defocus disk and directed at a randomly
    // sampled point around the pixel location i, j
    Ray GetRay(int i, int j);

public:
    // Point camera is looking from
    Point3 lookfrom = Point3(0,0,0);
    // Point camera is looking at
    Point3 lookat = Point3(0,0,-1);
    // Camera relative up direction
    Vec3 vup = Vec3(0,1,0);
    // Vertical view angle (vertical fov)
    double vfov = 90;

    // Ratio of image w/h
    double aspect_ratio = 1.0;
    // Rendered image width
    int image_width = 100;

    int samples_per_pixel = 10;
    int max_bounce = 10;

    // Variation angle of rays through each pixel
    double defocus_angle = 0;
    // Distance from camera lookfrom point (camera center) to plane of perfect focus (focus plane)
    // Be aware that the focus distance is not usually the same as the focal length
    double focus_dist = 10;

    // The focal length is the distance between the camera center and the image plane
    // For this model, we put the pixel grid right on the focus plane, i.e. let the value of focal_length equal that of focus_dist
    // double focal_length;

    // Scene background color
    Color bgcolor;

private:
    // Camera center
    Point3 _center;
    // The viewport upper left corner
    Point3 _viewport_upper_left;
    // Location of pixel 0,0
    Point3 _location_origin_pixel_grid;
    // Offset to pixel to the right
    Vec3 _pixel_delta_u;
    // Offset to pixel below
    Vec3 _pixel_delta_v;
    // Camera frame basis vector u
    Vec3 _u;
    // Camera frame basis vector v
    Vec3 _v;
    // Camera frame basis vector w
    Vec3 _w;
    // Defocus disk horizontal radius
    Vec3 _defocus_disk_u;
    // Defocus disk vertical radius
    Vec3 _defocus_disk_v;
    // Rendered image height
    int _image_height;
    // Color scale factor for a sum of pixel samples
    double _pixel_samples_scale_factor;
};

} // namespace rabbit

} // namespace gplay


#endif // GPLAY_RABBIT_CAMERA_H
