#include "owls/transforms.h"

namespace gplay {

namespace owls {

gmath::Point3 CvtCoordinateWorldToCamera(const gmath::Point3& p, const Camera& camera) {
    gmath::Point3 p_cam;
    camera.GetWorldToCameraMatrix().MultPoint(p, p_cam);
    return p_cam;
}

gmath::Point3 CvtCoordinateCameraToNDC(const gmath::Point3& p, const Camera& camera) {
    gmath::Point3 p_ndc;
    camera.GetPerspectiveProjectionMatrix().MultPoint(p, p_ndc);
    return p_ndc;
}

gmath::Point3 CvtCoordinateWorldToNDC(const gmath::Point3& p, const Camera& camera) {
    // world -> camera
    gmath::Point3 p_cam = CvtCoordinateWorldToCamera(p, camera);
    // camera -> screen -> NDC, range [-1, 1], a canonical volume
    return CvtCoordinateCameraToNDC(p_cam, camera);
}

gmath::Point3 CvtCoordinateNDCToRaster(const gmath::Point3& p, const Camera& camera) {
    double raster_x = (p.X() + 1)/2 * static_cast<double>(camera.GetImageWidth());
    // in raster space, y is downward so invert direction
    double raster_y = (-p.Y() + 1)/2 * static_cast<double>(camera.GetImageHeight());
    double raster_z = p.Z();

    // continuous point under raster coordinate
    return gmath::Point3(raster_x, raster_y, raster_z);
}

gmath::Point3 CvtCoordinateCameraToRaster(const gmath::Point3& p, const Camera& camera) {
    gmath::Point3 p_ndc = CvtCoordinateCameraToNDC(p, camera);
    return CvtCoordinateNDCToRaster(p_ndc, camera);
}

gmath::Point3 CvtCoordinateWorldToRaster(const gmath::Point3& p, const Camera& camera) {
    gmath::Point3 p_ndc = CvtCoordinateWorldToNDC(p, camera);
    return CvtCoordinateNDCToRaster(p_ndc, camera);
}

gmath::Point3 CvtCoordinateZDivide(const gmath::Point3& p_cam) {
    auto z = p_cam.Z();
    return gmath::Point3(p_cam.X()/-z, p_cam.Y()/-z, 1);
}

} // namespace owls

} // namespace gplay
