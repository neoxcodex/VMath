#ifndef VMathM1_H
#define VMathM1_H

#include <vector>

namespace constants {
    constexpr double ACCU_PI = 3.14159265358979323846;
    constexpr float PI = 3.14159265f;
    constexpr float INV_PI_180 = 57.2957795f;
}

namespace dimN {
    double magnitude(const std::vector<double>& v);
    std::vector<double> normalize(const std::vector<double>& v);
    void vecout(const std::vector<double>& a);
    std::vector<double> scalarMult(const std::vector<double>& vector_, double multiplier);
    std::vector<double> addVectors(const std::vector<double>& vec1, const std::vector<double>& vec2);
    std::vector<double> subtractVectors(const std::vector<double>& vec1, const std::vector<double>& vec2);
    double distance(const std::vector<double>& vec1, const std::vector<double>& vec2);
    double dotProduct(const std::vector<double>& vec1, const std::vector<double>& vec2);
    double angleRAD(const std::vector<double>& vec1, const std::vector<double>& vec2);
    double angleDEG(const std::vector<double>& vec1, const std::vector<double>& vec2);
}

namespace dim3 {
    struct Vec3 {
        float x, y, z;
    };

    float dotProduct(Vec3 a, Vec3 b);
    float magSquared(Vec3 a);
    void vectorCout(Vec3 a);
    Vec3 normalize(Vec3 a);
    Vec3 scalarMult(Vec3 a, float scalar);
    Vec3 add(Vec3 a, Vec3 b);
    Vec3 subtract(Vec3 a, Vec3 b);
    float distanceSquared(Vec3 a, Vec3 b);
    float angleRAD(Vec3 a, Vec3 b);
    float angleDEG(Vec3 a, Vec3 b);
}

namespace dim2 {
    struct Vec2 {
        float x, y;
    };

    float dotProduct(Vec2 a, Vec2 b);
    float magSquared(Vec2 a);
    void vectorCout(Vec2 a);
    Vec2 normalize(Vec2 a);
    Vec2 scalarMult(Vec2 a, float scalar);
    Vec2 add(Vec2 a, Vec2 b);
    Vec2 subtract(Vec2 a, Vec2 b);
    float distanceSquared(Vec2 a, Vec2 b);
    float angleRAD(Vec2 a, Vec2 b);
    float angleDEG(Vec2 a, Vec2 b);
}

#endif // VMathM1_H
