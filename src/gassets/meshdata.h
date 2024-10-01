#ifndef GPLAY_GASSETS_MESHDATA_H
#define GPLAY_GASSETS_MESHDATA_H
/*
Class MeshData
*/

#include <vector>

#include "gmath/vec3.h"
#include "gmath/vec2.h"

namespace gplay {

namespace gassets {

struct MeshVertex {
public:
    MeshVertex();

    MeshVertex(const gmath::Point3& coord, const gmath::Point2& tex_coord);

    MeshVertex(const gmath::Point3& coord, const gmath::Point2& tex_coord, const gmath::Vec3& normal);

    MeshVertex(const gmath::Point3& coord, const gmath::Point2& tex_coord, const gmath::Vec3& normal, const gmath::Color& color);

    inline const gmath::Point3& GetCoordinate() const {
        return coordinate;
    }

    inline const gmath::Point2& GetTextureCoordinate() const {
        return texture_coordinate;
    }

    inline const gmath::Vec3& GetVertexNormal() const {
        return vertex_normal;
    }

    inline const gmath::Color& GetVertexColor() const {
        return vertex_color;
    }

public:
    gmath::Point3 coordinate;
    gmath::Point2 texture_coordinate;
    gmath::Vec3 vertex_normal;
    gmath::Color vertex_color;
};

struct MeshData {
public:
    MeshData(const std::string& filename);

    bool Load(const std::string& directory, const std::string& filename);

    bool LoadObj(const std::string& directory, const std::string& filename);

    // GetVertexData ...
    inline const MeshVertex* GetVertexData(size_t idx) const {
        return &vertices[idx];
    }

    // GetVertexNum return the number of vertices of mesh data
    inline size_t GetVertexNum() const {
        return vertices.size();
    }

    // Empty ...
    inline bool Empty() const {
        return vertices.empty();
    }

public:
    std::vector<MeshVertex> vertices;
};

} // namespace gassets

} // namespace gplay


#endif // GPLAY_GASSETS_MESHDATA_H
