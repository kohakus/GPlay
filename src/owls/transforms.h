#ifndef GPLAY_OWLS_TRANSFORMS_H
#define GPLAY_OWLS_TRANSFORMS_H
/*
Coordinate transformations and Projection transformations.
*/

#include "owls/camera.h"

namespace gplay {

namespace owls {

// CvtCoordinateWorldToCamera ...
gmath::Point3 CvtCoordinateWorldToCamera(const gmath::Point3& p, const Camera& camera);

// CvtCoordinateCameraToNDC ...
gmath::Point3 CvtCoordinateCameraToNDC(const gmath::Point3& p, const Camera& camera);

// CvtCoordinateWorldToNDC ...
gmath::Point3 CvtCoordinateWorldToNDC(const gmath::Point3& p, const Camera& camera);

// CvtCoordinateNDCToRaster ...
gmath::Point3 CvtCoordinateNDCToRaster(const gmath::Point3& p, const Camera& camera);

// CvtCoordinateCameraToRaster ...
gmath::Point3 CvtCoordinateCameraToRaster(const gmath::Point3& p, const Camera& camera);

// CvtCoordinateWorldToRaster ...
gmath::Point3 CvtCoordinateWorldToRaster(const gmath::Point3& p, const Camera& camera);

// CvtCoordinateZDivide ...
gmath::Point3 CvtCoordinateZDivide(const gmath::Point3& p_cam);

} // namespace owls

} // namespace gplay

#endif // GPLAY_OWLS_TRANSFORMS_H
