#include "rabbit/draw.h"
#include "rabbit/bvh.h"
#include "rabbit/object.h"

using namespace gplay::rabbit;

void RenderGroundAndSky() {
    HittableList world;

    // add a big lambertian sphere
    world.AddObject(std::make_shared<Sphere>(Point3(0,-100.5,-1), 100., std::make_shared<Lambertian>(Color(0.5,0.5,0.5))));

    Camera camera(
        Point3(0.,0.,0.),       // lookfrom
        Point3(0.,0.,-1.),      // lookat
        Vec3(0.,1.,0.),         // vup
        90,                     // vfov
        4.0 / 3.0,              // aspect ratio
        512,                    // image width
        128,                    // samples per pixel
        64,                     // bounce max depth
        0,                      // defocus angle
        1.0,                    // focus distance
        Color(0.7, 0.8, 1.0)    // background color
    );
    camera.Initialize();

    RenderWorld(camera, world, "render_ground_and_sky.ppm");
}

void RenderMaterialDemo() {
    HittableList world;

    // add a big lambertian sphere
    world.AddObject(std::make_shared<Sphere>(Point3(0,-100.5,-2), 100., std::make_shared<Lambertian>(Color(0.5,0.5,0.5))));
    // add a small lambertian sphere
    world.AddObject(std::make_shared<Sphere>(Point3(0,0,-2), 0.5, std::make_shared<Lambertian>(Color(0.3,0.3,0.3))));
    // add a metal sphere
    world.AddObject(std::make_shared<Sphere>(Point3(1,0,-2), 0.5, std::make_shared<Metal>(Color(0.8,0.6,0.2), 0.3)));
    // add another metal sphere with different albedo
    world.AddObject(std::make_shared<Sphere>(Point3(-1,0,-2), 0.5, std::make_shared<Metal>(Color(0.8,0.8,0.8), 0.8)));

    Camera camera(
        Point3(0.,0.,0.),       // lookfrom
        Point3(0.,0.,-1.),      // lookat
        Vec3(0.,1.,0.),         // vup
        90,                     // vfov
        4.0 / 3.0,              // aspect ratio
        512,                    // image width
        128,                    // samples per pixel
        64,                     // bounce max depth
        0,                      // defocus angle
        2.0,                    // focus distance
        Color(0.7, 0.8, 1.0)    // background color
    );
    camera.Initialize();

    RenderWorld(camera, world, "render_material_demo.ppm");
}

void RenderMaterialWithPositionableCameraDemo() {
    HittableList world;

    // add a big lambertian sphere
    world.AddObject(std::make_shared<Sphere>(Point3(0,-100.5,-2), 100., std::make_shared<Lambertian>(Color(0.5,0.5,0.5))));
    // add a small lambertian sphere
    world.AddObject(std::make_shared<Sphere>(Point3(0,0,-2), 0.5, std::make_shared<Lambertian>(Color(0.3,0.3,0.3))));
    // add a metal sphere
    world.AddObject(std::make_shared<Sphere>(Point3(1,0,-2), 0.5, std::make_shared<Metal>(Color(0.8,0.6,0.2), 0.3)));
    // add another metal sphere with different albedo
    world.AddObject(std::make_shared<Sphere>(Point3(-1,0,-2), 0.5, std::make_shared<Metal>(Color(0.8,0.8,0.8), 0.8)));

    Camera camera(
        Point3(-2.,2.,1.),      // lookfrom
        Point3(0.,0.,-2.),      // lookat
        Vec3(0.,1.,0.),         // vup
        90,                     // vfov
        4.0 / 3.0,              // aspect ratio
        512,                    // image width
        128,                    // samples per pixel
        64,                     // bounce max depth
        0,                      // defocus angle
        2.0,                    // focus distance
        Color(0.7, 0.8, 1.0)    // background color
    );
    camera.Initialize();

    RenderWorld(camera, world, "render_material_with_positionable_camera_demo.ppm");
}

void RenderMaterialWithSmallerFovDemo() {
    HittableList world;

    // add a big lambertian sphere
    world.AddObject(std::make_shared<Sphere>(Point3(0,-100.5,-2), 100., std::make_shared<Lambertian>(Color(0.5,0.5,0.5))));
    // add a small lambertian sphere
    world.AddObject(std::make_shared<Sphere>(Point3(0,0,-2), 0.5, std::make_shared<Lambertian>(Color(0.3,0.3,0.3))));
    // add a metal sphere
    world.AddObject(std::make_shared<Sphere>(Point3(1,0,-2), 0.5, std::make_shared<Metal>(Color(0.8,0.6,0.2), 0.3)));
    // add another metal sphere with different albedo
    world.AddObject(std::make_shared<Sphere>(Point3(-1,0,-2), 0.5, std::make_shared<Metal>(Color(0.8,0.8,0.8), 0.8)));

    Camera camera(
        Point3(-2.,2.,1.),      // lookfrom
        Point3(0.,0.,-2.),      // lookat
        Vec3(0.,1.,0.),         // vup
        20,                     // vfov
        4.0 / 3.0,              // aspect ratio
        512,                    // image width
        128,                    // samples per pixel
        64,                     // bounce max depth
        0,                      // defocus angle
        2.0,                    // focus distance
        Color(0.7, 0.8, 1.0)    // background color
    );
    camera.Initialize();

    RenderWorld(camera, world, "render_material_with_smaller_fov_demo.ppm");
}

void RenderMaterialWithDefocusBlurDemo() {
    HittableList world;

    // add a big lambertian sphere
    world.AddObject(std::make_shared<Sphere>(Point3(0,-100.5,-2), 100., std::make_shared<Lambertian>(Color(0.5,0.5,0.5))));
    // add a small lambertian sphere
    world.AddObject(std::make_shared<Sphere>(Point3(0,0,-2), 0.5, std::make_shared<Lambertian>(Color(0.3,0.3,0.3))));
    // add a metal sphere
    world.AddObject(std::make_shared<Sphere>(Point3(1,0,-2), 0.5, std::make_shared<Metal>(Color(0.8,0.6,0.2), 0.3)));
    // add another metal sphere with different albedo
    world.AddObject(std::make_shared<Sphere>(Point3(-1,0,-2), 0.5, std::make_shared<Metal>(Color(0.8,0.8,0.8), 0.8)));

    auto lookfrom = Point3(-2.,2.,1.);
    auto lookat = Point3(0.,0.,-2.);
    Camera camera(
        lookfrom,                      // lookfrom
        lookat,                        // lookat
        Vec3(0.,1.,0.),                // vup
        20,                            // vfov
        4.0 / 3.0,                     // aspect ratio
        512,                           // image width
        128,                           // samples per pixel
        64,                            // bounce max depth
        10,                            // defocus angle
        (lookat-lookfrom).Length(),    // focus distance
        Color(0.7, 0.8, 1.0)           // background color
    );
    camera.Initialize();

    RenderWorld(camera, world, "render_material_with_defocus_blur_demo.ppm");
}

void RenderHollowGlassSphere() {
    HittableList world;

    // add a big lambertian sphere
    world.AddObject(std::make_shared<Sphere>(Point3(0,-100.5,-2), 100., std::make_shared<Lambertian>(Color(0.5,0.5,0.5))));
    // add a hollow glass sphere
    world.AddObject(std::make_shared<Sphere>(Point3(0.6,0.0,-2), 0.5, std::make_shared<Dielectric>(1.5)));
    world.AddObject(std::make_shared<Sphere>(Point3(0.6,0.0,-2), 0.45, std::make_shared<Dielectric>(1.0/1.5)));
    // add a glass sphere
    world.AddObject(std::make_shared<Sphere>(Point3(-0.6,0,-2), 0.5, std::make_shared<Dielectric>(1.5)));

    Camera camera(
        Point3(0.,0.,0.),       // lookfrom
        Point3(0.,0.,-1.),      // lookat
        Vec3(0.,1.,0.),         // vup
        90,                     // vfov
        4.0 / 3.0,              // aspect ratio
        512,                    // image width
        128,                    // samples per pixel
        64,                     // bounce max depth
        0,                      // defocus angle
        2.0,                    // focus distance
        Color(0.7, 0.8, 1.0)    // background color
    );
    camera.Initialize();

    RenderWorld(camera, world, "render_hollow_glass_sphere.ppm");
}

void RenderMotionBlurDemo() {
    HittableList world;

    // add a very big sphere as ground
    world.AddObject(std::make_shared<Sphere>(Point3(0,-1000,0), 1000, std::make_shared<Lambertian>(Color(0.5,0.5,0.5))));

    // add small spheres randomly
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_prob = RandomDouble();
            Point3 center(a + 0.9*RandomDouble(), 0.2, b + 0.9*RandomDouble());

            if (((center - Point3(-4, 0.2, 0)).Length() > 0.9) &&
                ((center - Point3(0, 0.2, 0)).Length() > 0.9) &&
                ((center - Point3(4, 0.2, 0)).Length() > 0.9)) {
                if (choose_prob < 0.8) {
                    // diffuse
                    auto center_mv = center + Vec3(0, RandomDouble(0,0.2), 0);
                    world.AddObject(std::make_shared<Sphere>(center, center_mv, 0.2,
                        std::make_shared<Lambertian>(RandomVec3()*RandomVec3())));
                } else if (choose_prob < 0.95) {
                    // metal
                    auto fuzz =  RandomDouble(0, 0.5);
                    world.AddObject(std::make_shared<Sphere>(center, 0.2,
                        std::make_shared<Metal>(RandomVec3(0.5,1.0), fuzz)));
                } else {
                    // glass
                    world.AddObject(std::make_shared<Sphere>(center, 0.2,
                        std::make_shared<Dielectric>(1.5)));
                }
            }
        }
    }

    // add a big dielectric sphere
    world.AddObject(std::make_shared<Sphere>(Point3(0,1,0), 1, std::make_shared<Dielectric>(1.5)));
    // add a big lambertian sphere
    world.AddObject(std::make_shared<Sphere>(Point3(4,1,0), 1, std::make_shared<Lambertian>(Color(0.3,0.5,0.2))));
    // add a big metal sphere
    world.AddObject(std::make_shared<Sphere>(Point3(-4,1,0), 1, std::make_shared<Metal>(Color(0.7,0.6,0.5), 0.3)));

    // construct bvh to speed up rendering
    world = HittableList(std::make_shared<BVHNode>(world));

    Camera camera(
        Point3(-13.,2.,3.),     // lookfrom
        Point3(0.,0.,0.),       // lookat
        Vec3(0.,1.,0.),         // vup
        20,                     // vfov
        16.0 / 9.0,             // aspect ratio
        1024,                   // image width
        128,                    // samples per pixel
        64,                     // bounce max depth
        0.6,                    // defocus angle
        10.0,                   // focus distance
        Color(0.7, 0.8, 1.0)    // background color
    );
    camera.Initialize();

    RenderWorld(camera, world, "render_motion_blur.ppm");
}

void RenderCheckeredSpheres() {
    HittableList world;

    auto checker_texture = std::make_shared<CheckerTexture>(0.32, Color(.2, .3, .1), Color(.9, .9, .9));
    world.AddObject(std::make_shared<Sphere>(Point3(0,-10, 0), 10, std::make_shared<Lambertian>(checker_texture)));
    world.AddObject(std::make_shared<Sphere>(Point3(0, 10, 0), 10, std::make_shared<Lambertian>(checker_texture)));

    Camera camera(
        Point3(13.,2.,3.),      // lookfrom
        Point3(0.,0.,0.),       // lookat
        Vec3(0.,1.,0.),         // vup
        20,                     // vfov
        16.0 / 9.0,             // aspect ratio
        512,                    // image width
        128,                    // samples per pixel
        64,                     // bounce max depth
        0,                      // defocus angle
        10.0,                   // focus distance
        Color(0.7, 0.8, 1.0)    // background color
    );
    camera.Initialize();

    RenderWorld(camera, world, "render_checkered_spheres.ppm");
}

void RenderTextureMappingDemo() {
    HittableList world;

    auto checker_texture = std::make_shared<CheckerTexture>(0.32, Color(.2, .3, .1), Color(.9, .9, .9));
    auto earth_image_texture = std::make_shared<ImageTexture>("earthmap.jpg");

    // add a very big sphere as ground
    world.AddObject(std::make_shared<Sphere>(Point3(0,-1000,0), 1000, std::make_shared<Lambertian>(checker_texture)));
    // add a sphere with earth image texture
    world.AddObject(std::make_shared<Sphere>(Point3(-2,2,0), 2, std::make_shared<Lambertian>(earth_image_texture)));

    Camera camera(
        Point3(18, 5, 10),      // lookfrom
        Point3(-2, 2, 0),       // lookat
        Vec3(0.,1.,0.),         // vup
        30,                     // vfov
        16.0 / 9.0,             // aspect ratio
        512,                    // image width
        128,                    // samples per pixel
        64,                     // bounce max depth
        0,                      // defocus angle
        10.0,                   // focus distance
        Color(0.7, 0.8, 1.0)    // background color
    );
    camera.Initialize();

    RenderWorld(camera, world, "render_texture_mapping_demo.ppm");
}

void RenderPerlinSpheres() {
    HittableList world;

    auto perlin_noise_texture = std::make_shared<NoiseTexture>(4, std::make_shared<PerlinNoise>());
    world.AddObject(std::make_shared<Sphere>(Point3(0,-1000,0), 1000, std::make_shared<Lambertian>(perlin_noise_texture)));
    world.AddObject(std::make_shared<Sphere>(Point3(0,2,0), 2, std::make_shared<Lambertian>(perlin_noise_texture)));

    Camera camera(
        Point3(18, 5, 10),      // lookfrom
        Point3(0, 2, 0),        // lookat
        Vec3(0.,1.,0.),         // vup
        30,                     // vfov
        16.0 / 9.0,             // aspect ratio
        512,                    // image width
        128,                    // samples per pixel
        64,                     // bounce max depth
        0,                      // defocus angle
        10.0,                   // focus distance
        Color(0.7, 0.8, 1.0)    // background color
    );
    camera.Initialize();

    RenderWorld(camera, world, "render_perlin_spheres.ppm");
}

void RenderSimpleLightDemo() {
    HittableList world;

    auto perlin_noise_texture = std::make_shared<NoiseTexture>(4, std::make_shared<PerlinNoise>());
    world.AddObject(std::make_shared<Sphere>(Point3(0,-1000,0), 1000, std::make_shared<Lambertian>(perlin_noise_texture)));
    world.AddObject(std::make_shared<Sphere>(Point3(0,2,0), 2, std::make_shared<Lambertian>(perlin_noise_texture)));
    // add a small lighting sphere
    world.AddObject(std::make_shared<Sphere>(Point3(3,1,0), 1, std::make_shared<DiffuseLight>(Color(4,4,4))));
    // add a lighting rectangle
    world.AddObject(std::make_shared<Quadrilateral>(Point3(-1,5,-1), Vec3(2,0,0), Vec3(0,0,2), std::make_shared<DiffuseLight>(Color(1,0,0))));

    Camera camera(
        Point3(18, 10, 10),     // lookfrom
        Point3(0, 1, 0),        // lookat
        Vec3(0.,1.,0.),         // vup
        25,                     // vfov
        16.0 / 9.0,             // aspect ratio
        512,                    // image width
        128,                    // samples per pixel
        64,                     // bounce max depth
        0,                      // defocus angle
        10.0,                   // focus distance
        Color(0.0, 0.0, 0.0)    // background color
    );
    camera.Initialize();

    RenderWorld(camera, world, "render_simple_light_demo.ppm");
}

void RenderCornellBoxDemo() {
    HittableList world;

    auto red   = std::make_shared<Lambertian>(Color(.65, .05, .05));
    auto white = std::make_shared<Lambertian>(Color(.73, .73, .73));
    auto green = std::make_shared<Lambertian>(Color(.12, .45, .15));
    auto light = std::make_shared<DiffuseLight>(Color(7, 7, 7));

    world.AddObject(std::make_shared<Quadrilateral>(Point3(555,0,0), Vec3(0,555,0), Vec3(0,0,555), green));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(0,0,0), Vec3(0,555,0), Vec3(0,0,555), red));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(0,0,0), Vec3(555,0,0), Vec3(0,0,555), white));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(555,555,555), Vec3(-555,0,0), Vec3(0,0,-555), white));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(0,0,555), Vec3(555,0,0), Vec3(0,555,0), white));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(113,554,127), Vec3(330,0,0), Vec3(0,0,305), light));

    std::shared_ptr<Hittable> box1 = std::make_shared<Box>(Point3(0,0,0), Point3(165,330,165), white);
    box1 = std::make_shared<ObjectYRotated>(box1, 15);
    box1 = std::make_shared<ObjectTranslated>(box1, Vec3(265,0,295));
    world.AddObject(box1);

    std::shared_ptr<Hittable> box2 = std::make_shared<Box>(Point3(0,0,0), Point3(165,165,165), white);
    box2 = std::make_shared<ObjectYRotated>(box2, -18);
    box2 = std::make_shared<ObjectTranslated>(box2, Vec3(130,0,65));
    world.AddObject(box2);

    Camera camera(
        Point3(278, 278, -800),    // lookfrom
        Point3(278, 278, 0),       // lookat
        Vec3(0.,1.,0.),            // vup
        40,                        // vfov
        1.0,                       // aspect ratio
        512,                       // image width
        512,                       // samples per pixel
        64,                        // bounce max depth
        0,                         // defocus angle
        10.0,                      // focus distance
        Color(0.0, 0.0, 0.0)       // background color
    );
    camera.Initialize();

    RenderWorld(camera, world, "render_cornell_box_demo.ppm");
}

void RenderCornellBoxWithVolumesDemo() {
    HittableList world;

    auto red   = std::make_shared<Lambertian>(Color(.65, .05, .05));
    auto white = std::make_shared<Lambertian>(Color(.73, .73, .73));
    auto green = std::make_shared<Lambertian>(Color(.12, .45, .15));
    auto light = std::make_shared<DiffuseLight>(Color(7, 7, 7));

    world.AddObject(std::make_shared<Quadrilateral>(Point3(555,0,0), Vec3(0,555,0), Vec3(0,0,555), green));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(0,0,0), Vec3(0,555,0), Vec3(0,0,555), red));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(0,0,0), Vec3(555,0,0), Vec3(0,0,555), white));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(555,555,555), Vec3(-555,0,0), Vec3(0,0,-555), white));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(0,0,555), Vec3(555,0,0), Vec3(0,555,0), white));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(113,554,127), Vec3(330,0,0), Vec3(0,0,305), light));

    std::shared_ptr<Hittable> box1 = std::make_shared<Box>(Point3(0,0,0), Point3(165,330,165), white);
    box1 = std::make_shared<ObjectYRotated>(box1, 15);
    box1 = std::make_shared<ObjectTranslated>(box1, Vec3(265,0,295));
    world.AddObject(std::make_shared<ObjectWithConstDensityMedium>(box1, 0.01, Color(0,0,0)));

    std::shared_ptr<Hittable> box2 = std::make_shared<Box>(Point3(0,0,0), Point3(165,165,165), white);
    box2 = std::make_shared<ObjectYRotated>(box2, -18);
    box2 = std::make_shared<ObjectTranslated>(box2, Vec3(130,0,65));
    world.AddObject(std::make_shared<ObjectWithConstDensityMedium>(box2, 0.01, Color(1,1,1)));

    Camera camera(
        Point3(278, 278, -800),    // lookfrom
        Point3(278, 278, 0),       // lookat
        Vec3(0.,1.,0.),            // vup
        40,                        // vfov
        1.0,                       // aspect ratio
        512,                       // image width
        512,                       // samples per pixel
        64,                        // bounce max depth
        0,                         // defocus angle
        10.0,                      // focus distance
        Color(0.0, 0.0, 0.0)       // background color
    );
    camera.Initialize();

    RenderWorld(camera, world, "render_cornell_box_with_volumes_demo.ppm");
}

void RenderCornellBoxWithSubsurfaceScatteringDemo() {
    HittableList world;

    auto red   = std::make_shared<Lambertian>(Color(.65, .05, .05));
    auto white = std::make_shared<Lambertian>(Color(.73, .73, .73));
    auto green = std::make_shared<Lambertian>(Color(.12, .45, .15));
    auto light = std::make_shared<DiffuseLight>(Color(7, 7, 7));

    world.AddObject(std::make_shared<Quadrilateral>(Point3(555,0,0), Vec3(0,555,0), Vec3(0,0,555), green));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(0,0,0), Vec3(0,555,0), Vec3(0,0,555), red));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(0,0,0), Vec3(555,0,0), Vec3(0,0,555), white));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(555,555,555), Vec3(-555,0,0), Vec3(0,0,-555), white));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(0,0,555), Vec3(555,0,0), Vec3(0,555,0), white));
    world.AddObject(std::make_shared<Quadrilateral>(Point3(113,554,127), Vec3(330,0,0), Vec3(0,0,305), light));

    auto sphere1 = std::make_shared<Sphere>(Point3(360, 120, 270), 120, std::make_shared<Dielectric>(1.6));
    world.AddObject(sphere1);
    world.AddObject(std::make_shared<ObjectWithConstDensityMedium>(sphere1, 0.1, Color(0.2, 0.4, 0.9)));

    auto sphere2 = std::make_shared<Sphere>(Point3(180, 65, 140), 65, std::make_shared<Dielectric>(1.6));
    world.AddObject(sphere2);
    world.AddObject(std::make_shared<ObjectWithConstDensityMedium>(sphere2, 0.1, Color(0.2, 0.8, 0.4)));

    Camera camera(
        Point3(278, 278, -800),    // lookfrom
        Point3(278, 278, 0),       // lookat
        Vec3(0.,1.,0.),            // vup
        40,                        // vfov
        1.0,                       // aspect ratio
        512,                       // image width
        512,                       // samples per pixel
        64,                        // bounce max depth
        0,                         // defocus angle
        10.0,                      // focus distance
        Color(0.0, 0.0, 0.0)       // background color
    );
    camera.Initialize();

    RenderWorld(camera, world, "render_cornell_box_with_subsurface_scattering_demo.ppm");
}

int main() {
    RenderGroundAndSky();
    RenderMaterialDemo();
    RenderMaterialWithPositionableCameraDemo();
    RenderMaterialWithSmallerFovDemo();
    RenderMaterialWithDefocusBlurDemo();
    RenderHollowGlassSphere();
    RenderMotionBlurDemo();
    RenderCheckeredSpheres();
    RenderTextureMappingDemo();
    RenderPerlinSpheres();
    RenderSimpleLightDemo();
    RenderCornellBoxDemo();
    RenderCornellBoxWithVolumesDemo();
    RenderCornellBoxWithSubsurfaceScatteringDemo();
}
