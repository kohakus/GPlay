#ifndef GPLAY_OWLS_DRAW_H
#define GPLAY_OWLS_DRAW_H

#include <vector>

#include "owls/camera.h"
#include "owls/triangle.h"

namespace gplay {

namespace owls {

class TrianglePainter {
public:
    TrianglePainter(const Camera& camera);

    // RenderCheckerPattern render a triangle defined by three points, using checker pattern
    void RenderCheckerPattern(double checker_scale, const gmath::Point3& p0, const gmath::Point3& p1, const gmath::Point3& p2,
                              const VertexUVAttribute& attr0_uv, const VertexUVAttribute& attr1_uv, const VertexUVAttribute& attr2_uv);

    // WriteImage write buffer data to an output image file
    void WriteImage(const std::string& outfile);

    // GetPainterImageWidth ...
    int GetPainterImageWidth() const;

    // GetPainterImageHeight ...
    int GetPainterImageHeight() const;

    // GetPainterImageGridSize ...
    int GetPainterImageGridSize() const;

private:
    Camera _camera;

    std::vector<gmath::Color> _frame_buffer_;
    std::vector<double> _depth_buffer;
};

} // namespace owls

} // namespace gplay

#endif // GPLAY_OWLS_DRAW_H
