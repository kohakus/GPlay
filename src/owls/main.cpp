#include "owls/draw.h"
#include "gassets/meshdata.h"

using namespace gplay;
using namespace gplay::owls;

void RenderPreloadCowDemo() {
    auto mesh_data = gassets::MeshData("cow.obj");

    auto cam_to_world_mat = gmath::SMatrix4(
        0.707107,  0.,        -0.707107, 0.,
        -0.331295, 0.883452,  -0.331295, 0.,
        0.624695,  0.468521,  0.624695,  0.,
        24.492470, 24.006365, 22.174985, 1.
    );

    Camera camera(
        cam_to_world_mat,      // camera to world matrix
        0.980,                 // film width (inch)
        0.735,                 // film height (inch)
        1280,                  // image width
        960,                   // image height
        FitGateMode::kFill,    // fit gate mode
        1,                     // near clipping plane distance
        1000,                  // far clipping plane distance
        20                     // focal length
    );
    auto painter = TrianglePainter(camera);

    for (int i = 0; i < mesh_data.GetVertexNum(); i++) {
        const gassets::MeshVertex* vertex0 = mesh_data.GetVertexData(i * 3);
        const gassets::MeshVertex* vertex1 = mesh_data.GetVertexData(i * 3 + 1);
        const gassets::MeshVertex* vertex2 = mesh_data.GetVertexData(i * 3 + 2);

        auto uv0 = VertexUVAttribute(vertex0->GetTextureCoordinate());
        auto uv1 = VertexUVAttribute(vertex1->GetTextureCoordinate());
        auto uv2 = VertexUVAttribute(vertex2->GetTextureCoordinate());

        painter.RenderCheckerPattern(10,
                                     vertex0->GetCoordinate(), vertex1->GetCoordinate(), vertex2->GetCoordinate(),
                                     uv0, uv1, uv2);
    }
    painter.WriteImage("render_preload_cow_demo.ppm");
}

void RenderPreloadCubeDemo() {
    auto mesh_data = gassets::MeshData("cube.obj");

    Camera camera(
        gmath::Point3(5, 2.5, 3),    // lookfrom
        gmath::Point3(0, 0, 0),      // lookat
        gmath::Vec3(0, 1, 0),        // vup
        0.980,                       // film width (inch)
        0.735,                       // film height (inch)
        1280,                        // image width
        960,                         // image height
        FitGateMode::kFill,          // fit gate mode
        1,                           // near clipping plane distance
        1000,                        // far clipping plane distance
        20                           // focal length
    );
    auto painter = TrianglePainter(camera);

    for (int i = 0; i < mesh_data.GetVertexNum(); i++) {
        const gassets::MeshVertex* vertex0 = mesh_data.GetVertexData(i * 3);
        const gassets::MeshVertex* vertex1 = mesh_data.GetVertexData(i * 3 + 1);
        const gassets::MeshVertex* vertex2 = mesh_data.GetVertexData(i * 3 + 2);

        auto uv0 = VertexUVAttribute(vertex0->GetTextureCoordinate());
        auto uv1 = VertexUVAttribute(vertex1->GetTextureCoordinate());
        auto uv2 = VertexUVAttribute(vertex2->GetTextureCoordinate());

        painter.RenderCheckerPattern(10,
                                     vertex0->GetCoordinate(), vertex1->GetCoordinate(), vertex2->GetCoordinate(),
                                     uv0, uv1, uv2);
    }
    painter.WriteImage("render_preload_cube_demo.ppm");
}

int main() {
    RenderPreloadCowDemo();
    RenderPreloadCubeDemo();
}
