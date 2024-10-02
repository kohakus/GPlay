#include <fstream>

#include "owls/draw.h"
#include "owls/shading.h"
#include "owls/transforms.h"

namespace gplay {

namespace owls {

TrianglePainter::TrianglePainter(const Camera& camera) : _camera(camera) {
    int size = GetPainterImageGridSize();
    _frame_buffer_.resize(size, gmath::Color(255,255,255));
    _depth_buffer.resize(size, _camera.GetFarClippingDistance());
}

void TrianglePainter::RenderCheckerPattern(double checker_scale, const gmath::Point3& p0, const gmath::Point3& p1, const gmath::Point3& p2,
                                           const VertexUVAttribute& attr0_uv, const VertexUVAttribute& attr1_uv, const VertexUVAttribute& attr2_uv) {
    gmath::Point3 p0_cam = CvtCoordinateWorldToCamera(p0, _camera);
    gmath::Point3 p1_cam = CvtCoordinateWorldToCamera(p1, _camera);
    gmath::Point3 p2_cam = CvtCoordinateWorldToCamera(p2, _camera);

    gmath::Point3 p0_raster = CvtCoordinateCameraToRaster(p0_cam, _camera);
    gmath::Point3 p1_raster = CvtCoordinateCameraToRaster(p1_cam, _camera);
    gmath::Point3 p2_raster = CvtCoordinateCameraToRaster(p2_cam, _camera);

    int image_w = GetPainterImageWidth();
    int image_h = GetPainterImageHeight();

    Triangle triangle(p0_raster, p1_raster, p2_raster);
    if (triangle.IsOutOfScreen(image_w, image_h)) {
        return;
    }

    // get sampling region of the triangle
    // be careful xmin/xmax/ymin/ymax can be negative
    auto bbox_min = triangle.GetBoundingBoxMin();
    auto bbox_max = triangle.GetBoundingBoxMax();
    int xmin = std::max(0, static_cast<int>(std::floor(bbox_min.X())));
    int ymin = std::max(0, static_cast<int>(std::floor(bbox_min.Y())));
    int xmax = std::min(image_w-1, static_cast<int>(std::floor(bbox_max.X())));
    int ymax = std::min(image_h-1, static_cast<int>(std::floor(bbox_max.Y())));

    // render triangle in clipped bbox
    for (int y = ymin; y <= ymax; y++) {
        for (int x = xmin; x <= xmax; x++) {
            gmath::Point3 p(x+0.5, y+0.5, 0);
            gmath::Point3 w;
            double pdepth;

            // coverage test
            if (!triangle.GetBarycentricCoordinate(p, w, pdepth)) {
                continue;
            }

            // depth test
            if (!(pdepth < _depth_buffer[y*image_w + x])) {
                continue;
            }
            _depth_buffer[y*image_w + x] = pdepth;

            VertexVec3Attribute attr_uv_interp = PerspectiveCorrectInterpVec3(triangle, w, pdepth,
                attr0_uv.DeriveVec3Attribute(), attr1_uv.DeriveVec3Attribute(), attr2_uv.DeriveVec3Attribute());
            VertexUVAttribute attrp_uv = attr_uv_interp.DeriveVec2Attribute();
            double checker_val = CheckerPatternValue(attrp_uv, checker_scale);
            double facing_ratio = TriangleFacingRatio(w, pdepth, gmath::SMatrix4(p0_cam, p1_cam, p2_cam, gmath::Point3()));
            _frame_buffer_[y*image_w + x] *= checker_val * facing_ratio;
        }
    }
}

void TrianglePainter::WriteImage(const std::string& outfile) {
    std::ofstream ofs;
    ofs.open(outfile);

    int image_w = GetPainterImageWidth();
    int image_h = GetPainterImageHeight();

    ofs << "P3\n" << image_w << " " << image_h << "\n255\n";
    // save as ppm file
    for (int j = 0; j < image_h; j++) {
        for (int i = 0; i < image_w; i++) {
            ofs << static_cast<int>(_frame_buffer_[j*image_w + i][0]) << " "
                << static_cast<int>(_frame_buffer_[j*image_w + i][1]) << " "
                << static_cast<int>(_frame_buffer_[j*image_w + i][2]) << "\n";
        }
    }
    ofs.close();
}

int TrianglePainter::GetPainterImageWidth() const {
    return _camera.GetImageWidth();
}

int TrianglePainter::GetPainterImageHeight() const {
    return _camera.GetImageHeight();
}

int TrianglePainter::GetPainterImageGridSize() const {
    return GetPainterImageWidth() * GetPainterImageHeight();
}

} // namespace owls

} // namespace gplay
