#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>

const int WIDTH = 800;
const int HEIGHT = 600;

struct Vec3 {
    float x, y, z;
    
    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    
    Vec3 operator+(const Vec3& v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }
    
    Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }
    
    Vec3 operator*(float s) const {
        return Vec3(x * s, y * s, z * s);
    }
    
    float dot(const Vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }
    
    Vec3 normalize() const {
        float len = std::sqrt(x * x + y * y + z * z);
        return Vec3(x / len, y / len, z / len);
    }
};

struct Ray {
    Vec3 origin;
    Vec3 direction;
    
    Ray(const Vec3& o, const Vec3& d) : origin(o), direction(d) {}
};

bool intersect_sphere(const Ray& ray, const Vec3& sphere_center, float sphere_radius, float& t) {
    Vec3 oc = ray.origin - sphere_center;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * oc.dot(ray.direction);
    float c = oc.dot(oc) - sphere_radius * sphere_radius;
    float discriminant = b * b - 4 * a * c;
    
    if (discriminant > 0) {
        t = (-b - std::sqrt(discriminant)) / (2.0f * a);
        return t > 0;
    }
    return false;
}

void render_image() {
    std::vector<Vec3> image(WIDTH * HEIGHT);
    Vec3 sphere_center(0, 0, -5);
    float sphere_radius = 1.0f;

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            float u = (x / float(WIDTH)) * 2 - 1;
            float v = (y / float(HEIGHT)) * 2 - 1;
            Vec3 ray_origin(0, 0, 0);
            Vec3 ray_direction(u, v, -1);
            ray_direction = ray_direction.normalize();
            
            Ray ray(ray_origin, ray_direction);
            float t;
            if (intersect_sphere(ray, sphere_center, sphere_radius, t)) {
                Vec3 hit_point = ray.origin + ray.direction * t;
                Vec3 normal = (hit_point - sphere_center).normalize();
                float brightness = std::max(0.0f, normal.dot(Vec3(0, 0, -1)));
                image[y * WIDTH + x] = Vec3(brightness, brightness, brightness);
            } else {
                image[y * WIDTH + x] = Vec3(0, 0, 0);
            }
        }
    }

    // Output the image (e.g., to PPM file)
    std::ofstream file("output.ppm");
    file << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";
    for (const Vec3& color : image) {
        file << int(color.x * 255) << " " << int(color.y * 255) << " " << int(color.z * 255) << "\n";
    }
    file.close();
}

int main() {
    render_image();
    return 0;
}
