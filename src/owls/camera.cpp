#include "owls/camera.h"

namespace gplay {

namespace owls {

Camera::Camera(const gmath::Point3& lookfrom, const gmath::Point3& lookat, const gmath::Vec3& vup,
               double film_width, double film_height, int image_width, int image_height,
               FitGateMode fit_gate_mode, double near_clip_distance, double far_clip_distance, double focal_length)
    : film_w(film_width),
      film_h(film_height),
      image_w(image_width),
      image_h(image_height),
      near_clip_dist(near_clip_distance),
      far_clip_dist(far_clip_distance),
      fl(focal_length),
      fitgate(fit_gate_mode),
      _center(lookfrom) {
    _w = UnitVec(lookfrom-lookat);
    _u = UnitVec(Vec3Cross(vup, _w));
    _v = Vec3Cross(_w, _u);

    _camera_to_world_matrix = gmath::SMatrix4(_u, _v, _w, _center);
    _world_to_camera_matrix = gmath::SMatrix4::Inverse(_camera_to_world_matrix);

    ComputeScreenParams();
    ComputePerspectiveProjectionMatrix();
}

Camera::Camera(const gmath::SMatrix4& cam_to_world_mat,
           double film_width, double film_height, int image_width, int image_height,
           FitGateMode fit_gate_mode, double near_clip_distance, double far_clip_distance, double focal_length)
    : film_w(film_width),
      film_h(film_height),
      image_w(image_width),
      image_h(image_height),
      near_clip_dist(near_clip_distance),
      far_clip_dist(far_clip_distance),
      fl(focal_length),
      fitgate(fit_gate_mode),
      _camera_to_world_matrix(cam_to_world_mat) {
    _u      = gmath::Vec3(_camera_to_world_matrix[0][0], _camera_to_world_matrix[0][1], _camera_to_world_matrix[0][2]);
    _v      = gmath::Vec3(_camera_to_world_matrix[1][0], _camera_to_world_matrix[1][1], _camera_to_world_matrix[1][2]);
    _w      = gmath::Vec3(_camera_to_world_matrix[2][0], _camera_to_world_matrix[2][1], _camera_to_world_matrix[2][2]);
    _center = gmath::Vec3(_camera_to_world_matrix[3][0], _camera_to_world_matrix[3][1], _camera_to_world_matrix[3][2]);

    _world_to_camera_matrix = gmath::SMatrix4::Inverse(_camera_to_world_matrix);

    ComputeScreenParams();
    ComputePerspectiveProjectionMatrix();
}

void Camera::ComputeScreenParams() {
    _film_aspect_ratio = film_w / film_h;
    _image_aspect_ratio = static_cast<double>(image_w) / static_cast<double>(image_h);

    _hfov = 2 * RadiansToDegrees(std::atan(InchToMillimeter(film_w)/2/fl));

    auto fitgate_scale_factor = ScaleFactorOfFitGateMode(fitgate, _film_aspect_ratio, _image_aspect_ratio);

    // suppose canvas located at near clipping plane
    _t = InchToMillimeter(film_h)/2/fl * near_clip_dist * fitgate_scale_factor.Y();
    _r = InchToMillimeter(film_w)/2/fl * near_clip_dist * fitgate_scale_factor.X();
    _b = -_t;
    _l = -_r;
}

void Camera::ComputePerspectiveProjectionMatrix() {
    _perspective_projection_matrix[0][0] = (2*near_clip_dist) / (_r - _l);
    _perspective_projection_matrix[0][1] = 0;
    _perspective_projection_matrix[0][2] = 0;
    _perspective_projection_matrix[0][3] = 0;

    _perspective_projection_matrix[1][0] = 0;
    _perspective_projection_matrix[1][1] = (2*near_clip_dist) / (_t - _b);
    _perspective_projection_matrix[1][2] = 0;
    _perspective_projection_matrix[1][3] = 0;

    _perspective_projection_matrix[2][0] = (_r + _l) / (_r - _l);
    _perspective_projection_matrix[2][1] = (_t + _b) / (_t - _b);
    _perspective_projection_matrix[2][2] = -(far_clip_dist+near_clip_dist) / (far_clip_dist-near_clip_dist);
    _perspective_projection_matrix[2][3] = -1;

    _perspective_projection_matrix[3][0] = 0;
    _perspective_projection_matrix[3][1] = 0;
    _perspective_projection_matrix[3][2] = -(2*far_clip_dist*near_clip_dist) / (far_clip_dist-near_clip_dist);
    _perspective_projection_matrix[3][3] = 0;
}

gmath::Vec2 ScaleFactorOfFitGateMode(const FitGateMode& mode, double film_aspect_ratio, double device_aspect_ratio) {
    gmath::Vec2 scale_factor(1,1);
    switch(mode) {
        case FitGateMode::kFill:
            if (film_aspect_ratio > device_aspect_ratio) {
                scale_factor[0] = device_aspect_ratio / film_aspect_ratio;
            } else {
                scale_factor[1] = film_aspect_ratio / device_aspect_ratio;
            }
            break;
        case FitGateMode::kOverscan:
            if (film_aspect_ratio > device_aspect_ratio) {
                scale_factor[1] = film_aspect_ratio / device_aspect_ratio;
            } else {
                scale_factor[0] = device_aspect_ratio / film_aspect_ratio;
            }
            break;
        default:
            break;
    }
    return scale_factor;
}

} // namespace owls

} // namespace gplay
