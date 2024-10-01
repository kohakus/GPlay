#ifndef GPLAY_OWLS_CAMERA_H
#define GPLAY_OWLS_CAMERA_H
/*
Class Camera
*/

#include "owls/mathtools.h"

namespace gplay {

namespace owls {

// FitGateMode decide the appearance of renders by considering resolution and film gates.
// When the resolution and film gates differ, two options are available:
//   1. fit the resolution gate within the film gate
//   2. fit the film gate within the resolution gate
enum class FitGateMode {
    // The Fill mode forces the resolution gate within the film gate
    kFill = 0,
    // The Overscan mode forces the film gate within the resolution gate
    kOverscan
};

class Camera {
public:
    Camera(const gmath::Point3& lookfrom, const gmath::Point3& lookat, const gmath::Vec3& vup,
           double film_width, double film_height, int image_width, int image_height,
           FitGateMode fit_gate_mode, double near_clip_distance, double far_clip_distance, double focal_length);

    Camera(const gmath::SMatrix4& cam_to_world_mat,
           double film_width, double film_height, int image_width, int image_height,
           FitGateMode fit_gate_mode, double near_clip_distance, double far_clip_distance, double focal_length);

    inline int GetImageWidth() const {
        return image_w;
    }

    inline int GetImageHeight() const {
        return image_h;
    }

    inline double GetNearClippingDistance() const {
        return near_clip_dist;
    }

    inline double GetFarClippingDistance() const {
        return far_clip_dist;
    }

    inline const gmath::SMatrix4& GetWorldToCameraMatrix() const {
        return _world_to_camera_matrix;
    }

    inline const gmath::SMatrix4& GetCameraToWorldMatrix() const {
        return _camera_to_world_matrix;
    }

    inline const gmath::SMatrix4& GetPerspectiveProjectionMatrix() const {
        return _perspective_projection_matrix;
    }

private:
    // ComputeScreenParams ...
    void ComputeScreenParams();

    // ComputePerspectiveProjectionMatrix provide an opengl-form perspective projection matrix (see glFrustum)
    void ComputePerspectiveProjectionMatrix();

public:
    // Film width
    double film_w;
    // Film height
    double film_h;
    // Image width
    int image_w;
    // Image height
    int image_h;
    // Near clipping plane distance
    double near_clip_dist;
    // Far clipping plane distance
    double far_clip_dist;
    // Focal length
    double fl;
    // The option to render when the resolution and film gates differ
    FitGateMode fitgate;

private:
    // Camera center
    gmath::Point3 _center;
    // Camera frame basis vector u
    gmath::Vec3 _u;
    // Camera frame basis vector v
    gmath::Vec3 _v;
    // Camera frame basis vector w
    gmath::Vec3 _w;

    // Ratio of film w/h
    double _film_aspect_ratio;
    // Ratio of image w/h
    double _image_aspect_ratio;

    // Horizontal view angle (horizontal fov)
    double _hfov;

    // Screen parameter t (top)
    double _t;
    // Screen parameter b (bottom)
    double _b;
    // Screen parameter l (left)
    double _l;
    // Screen parameter r (right)
    double _r;

    // Coordinate transformation matrix (camera to world)
    gmath::SMatrix4 _camera_to_world_matrix;
    // Coordinate transformation matrix (world to camera)
    gmath::SMatrix4 _world_to_camera_matrix;

    // Perspective Projection Matrix
    gmath::SMatrix4 _perspective_projection_matrix;
};

// InchToMillimeter ...
inline double InchToMillimeter(double inch) {
    return inch * kInchToMm;
}

// ScaleFactorOfFitGateMode ...
static gmath::Vec2 ScaleFactorOfFitGateMode(const FitGateMode& mode, double film_aspect_ratio, double device_aspect_ratio);

} // namespace owls

} // namespace gplay

#endif // GPLAY_OWLS_CAMERA_H
