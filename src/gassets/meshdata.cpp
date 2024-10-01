#include <cstdlib>
#include <iostream>

#include "gassets/meshdata.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

namespace gplay {

namespace gassets {

MeshVertex::MeshVertex() {}

MeshVertex::MeshVertex(const gmath::Point3& coord, const gmath::Point2& tex_coord)
    : coordinate(coord),
      texture_coordinate(tex_coord) {}

MeshVertex::MeshVertex(const gmath::Point3& coord, const gmath::Point2& tex_coord, const gmath::Vec3& normal)
    : coordinate(coord),
      texture_coordinate(tex_coord),
      vertex_normal(normal) {}

MeshVertex::MeshVertex(const gmath::Point3& coord, const gmath::Point2& tex_coord, const gmath::Vec3& normal, const gmath::Color& color)
    : coordinate(coord),
      texture_coordinate(tex_coord),
      vertex_normal(normal),
      vertex_color(color) {}

MeshData::MeshData(const std::string& filename) {
    // get directory
    auto data_dir = getenv("GPLAY_MESHDATA_DIR");

    // Hunt for the mesh data file in some likely locations.
    if (data_dir && Load(std::string(data_dir), filename)) { return; }
    if (Load("./", filename)) { return; }

    std::cerr << "ERROR: Could not load file '" << filename << "'.\n";
}

bool MeshData::Load(const std::string& directory, const std::string& filename) {
    // TODO: add more mesh data file format support
    return LoadObj(directory, filename);
}

bool MeshData::LoadObj(const std::string& directory, const std::string& filename) {
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string errors;

    std::string filepath = directory + filename;
    bool succ = tinyobj::LoadObj(&attributes, &shapes, &materials, &errors, filepath.c_str(), directory.c_str());
    if (!errors.empty()) {
        std::cerr << errors << std::endl;
        return false;
    }
    if (!succ) {
        return false;
    }

    for (int i = 0; i < shapes.size(); i ++) {
        const tinyobj::shape_t& shape = shapes[i];
        const tinyobj::mesh_t& mesh = shape.mesh;

        for (int fv = 0; fv < mesh.indices.size(); fv++) {
            tinyobj::index_t idx = mesh.indices[fv];
            MeshVertex vert;

            // Check if `vertex_index` is zero or positive. negative = no vertex data
            if (idx.vertex_index >= 0) {
                vert.coordinate = gmath::Point3(
                    attributes.vertices[idx.vertex_index * 3],
                    attributes.vertices[idx.vertex_index * 3 + 1],
                    attributes.vertices[idx.vertex_index * 3 + 2]
                );
            }

            // Check if `normal_index` is zero or positive. negative = no normal data
            if (idx.normal_index >= 0) {
                vert.vertex_normal = gmath::Vec3(
                    attributes.normals[idx.normal_index * 3],
                    attributes.normals[idx.normal_index * 3 + 1],
                    attributes.normals[idx.normal_index * 3 + 2]
                );
            }

            // Check if `texcoord_index` is zero or positive. negative = no texcoord data
            if (idx.texcoord_index >= 0) {
                vert.texture_coordinate = gmath::Point2(
                    attributes.texcoords[idx.texcoord_index * 2],
                    attributes.texcoords[idx.texcoord_index * 2 + 1]
                );
            }
            vertices.emplace_back(std::move(vert));
        }
    }

    return true;
}

} // namespace gassets

} // namespace gplay
