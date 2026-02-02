#ifndef dim4_2309809238
#define dim4_2309809238
#include "Constants.h"
#include "NDSFunctions.hpp"
#include "VMath3D.hpp"
#include<iostream>
#include<cmath>
namespace dim4{
    struct Vec4{
        float x,y,z,w;
        //STRICT
        bool operator==(const Vec4 other) const{
            return
            (
                (x == other.x)
                &&
                (y == other.y)
                &&
                (z == other.z)
                &&
                (w == other.w)
            );
        }
        Vec4 operator+(const Vec4 other) const{
            return {(x + other.x), (y+other.y), (z + other.z), (w + other.w)};
        }
        Vec4 operator-(const Vec4 other) const{

            return {(x - other.x), (y-other.y), (z - other.z), (w - other.w)};
        }
        Vec4 operator*(const float n) const{
            return {n*x, n*y , n*z, n*w};
        }


    };
    inline void vectorCout(const Vec4 v){
        std::cout << "3D+ Vector (" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" << std::endl;
    }
    inline Vec4 operator*(float scalar, const Vec4 v){
        return v*scalar;
    }
    inline float dotProduct(const Vec4 v1, const Vec4 v2){
        return
        (
            (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w)
        );
    }
    inline float magSquared(const Vec4 v){
        return
        (
            (v.x)*(v.x)+
            (v.y)*(v.y)+
            (v.z)*(v.z)+
            (v.w)*(v.w)
        );
    }
    inline float magnitude(const Vec4 v){
        return std::sqrt(magSquared(v));
    }
    inline bool epVectorEqual(const Vec4 v1, const Vec4 v2, float epsilon = constants::EPSILON){
        return (
            (std::abs(v1.x - v2.x) <= epsilon)
            &&
            (std::abs(v1.y - v2.y) <= epsilon)
            &&
            (std::abs(v1.z - v2.z) <= epsilon)
            &&
            (std::abs(v1.w - v2.w) <= epsilon)
        );
    }
    inline Vec4 normalize(const Vec4 v){
        float invMagV = 1.0f / std::sqrt((magSquared(v)));
        return {(v.x)*invMagV, (v.y)*invMagV, (v.z)*invMagV, (v.w)*invMagV};
    }
    inline Vec4 lerp(const Vec4& v1, const Vec4& v2, float t){
        float a = NDSF::clamp(t, 0.0f, 1.0f);
        return
        {

            v1.x + a*(v2.x - v1.x),
            v1.y + a*(v2.y - v1.y),
            v1.z + a*(v2.z - v1.z),
            v1.w + a*(v2.w - v1.w)
        };
    }
    inline float angleRAD(const Vec4& v1, const Vec4& v2, const bool returnCosAngle = false){
        float v1Mag = magnitude(v1);
        float v2Mag = magnitude(v2);

        float cosAngle = NDSF::clamp(dotProduct(v1, v2) / (v1Mag*v2Mag), -1.0f, 1.0f);

        if (returnCosAngle){return cosAngle;}

        return std::acos(cosAngle);
    }
    inline float angleDEG(const Vec4& v1, const Vec4& v2, const bool returnCosAngle = false){
        return angleRAD(v1, v2, returnCosAngle) * constants::INV_PI_180;
    }

    //MATRICES
    struct Mat4{
        float M[4][4] = {{0}};
        static Mat4 identity(){
            Mat4 res;
            res.M[0][0] = 1; res.M[1][1] = 1; res.M[2][2] = 1; res.M[3][3] = 1;
            return res;
        }
        Vec4 operator*(const Vec4& v) const{
            return{
                (v.x)*(M[0][0]) + (v.y)*(M[0][1]) + (v.z)*(M[0][2]) + (v.w)*(M[0][3]),
                (v.x)*(M[1][0]) + (v.y)*(M[1][1]) + (v.z)*(M[1][2]) + (v.w)*(M[1][3]),
                (v.x)*(M[2][0]) + (v.y)*(M[2][1]) + (v.z)*(M[2][2]) + (v.w)*(M[2][3]),
                (v.x)*(M[3][0]) + (v.y)*(M[3][1]) + (v.z)*(M[3][2]) + (v.w)*(M[3][3])
            };
        }
        static Mat4 genRotator(const dim3::Vec3& axis_normalized, const float angleRAD){
            Mat4 rotator = Mat4::identity();
            float cosA = std::cos(angleRAD);
            float sinA = std::sin(angleRAD);
            float t = 1.0f-cosA;
            float x = axis_normalized.x;
            float y = axis_normalized.y;
            float z = axis_normalized.z;

            // ROW 0
            rotator.M[0][0] = x * x * t + cosA;
            rotator.M[0][1] = x * y * t - z * sinA;
            rotator.M[0][2] = x * z * t + y * sinA;

            // ROW 1
            rotator.M[1][0] = y * x * t + z * sinA;
            rotator.M[1][1] = y * y * t + cosA;
            rotator.M[1][2] = y * z * t - x * sinA;

            // ROW 2
            rotator.M[2][0] = z * x * t - y * sinA;
            rotator.M[2][1] = z * y * t + x * sinA;
            rotator.M[2][2] = z * z * t + cosA;
            return rotator;

        }
        static Mat4 genRotationX(float angleRAD){
            float s = std::sin(angleRAD);
            float c = std::cos(angleRAD);
            Mat4 res = Mat4::identity();
            res.M[1][1] = c;
            res.M[1][2] = -s;
            res.M[2][1] = s;
            res.M[2][2] = c;
            return res;
        }
        static Mat4 genRotationY(float angleRAD){
            float s = std::sin(angleRAD);
            float c = std::cos(angleRAD);
            Mat4 res = Mat4::identity();
            res.M[0][0] = c;
            res.M[0][2] = s;
            res.M[2][0] = -s;
            res.M[2][2] = c;
            return res;
        }
        static Mat4 genRotationZ(float angleRAD){
            float s = std::sin(angleRAD);
            float c = std::cos(angleRAD);
            Mat4 res = Mat4::identity();
            res.M[0][0] = c;
            res.M[0][1] = -s;
            res.M[1][0] = s;
            res.M[1][1] = c;
            return res;
        }
    };
    inline Mat4 matrixMultiply(const Mat4& M1, const Mat4& M2) {
    Mat4 res;

        // Row 0
        res.M[0][0] = M1.M[0][0]*M2.M[0][0] + M1.M[0][1]*M2.M[1][0] + M1.M[0][2]*M2.M[2][0] + M1.M[0][3]*M2.M[3][0];
        res.M[0][1] = M1.M[0][0]*M2.M[0][1] + M1.M[0][1]*M2.M[1][1] + M1.M[0][2]*M2.M[2][1] + M1.M[0][3]*M2.M[3][1];
        res.M[0][2] = M1.M[0][0]*M2.M[0][2] + M1.M[0][1]*M2.M[1][2] + M1.M[0][2]*M2.M[2][2] + M1.M[0][3]*M2.M[3][2];
        res.M[0][3] = M1.M[0][0]*M2.M[0][3] + M1.M[0][1]*M2.M[1][3] + M1.M[0][2]*M2.M[2][3] + M1.M[0][3]*M2.M[3][3];

        // Row 1
        res.M[1][0] = M1.M[1][0]*M2.M[0][0] + M1.M[1][1]*M2.M[1][0] + M1.M[1][2]*M2.M[2][0] + M1.M[1][3]*M2.M[3][0];
        res.M[1][1] = M1.M[1][0]*M2.M[0][1] + M1.M[1][1]*M2.M[1][1] + M1.M[1][2]*M2.M[2][1] + M1.M[1][3]*M2.M[3][1];
        res.M[1][2] = M1.M[1][0]*M2.M[0][2] + M1.M[1][1]*M2.M[1][2] + M1.M[1][2]*M2.M[2][2] + M1.M[1][3]*M2.M[3][2];
        res.M[1][3] = M1.M[1][0]*M2.M[0][3] + M1.M[1][1]*M2.M[1][3] + M1.M[1][2]*M2.M[2][3] + M1.M[1][3]*M2.M[3][3];

        // Row 2
        res.M[2][0] = M1.M[2][0]*M2.M[0][0] + M1.M[2][1]*M2.M[1][0] + M1.M[2][2]*M2.M[2][0] + M1.M[2][3]*M2.M[3][0];
        res.M[2][1] = M1.M[2][0]*M2.M[0][1] + M1.M[2][1]*M2.M[1][1] + M1.M[2][2]*M2.M[2][1] + M1.M[2][3]*M2.M[3][1];
        res.M[2][2] = M1.M[2][0]*M2.M[0][2] + M1.M[2][1]*M2.M[1][2] + M1.M[2][2]*M2.M[2][2] + M1.M[2][3]*M2.M[3][2];
        res.M[2][3] = M1.M[2][0]*M2.M[0][3] + M1.M[2][1]*M2.M[1][3] + M1.M[2][2]*M2.M[2][3] + M1.M[2][3]*M2.M[3][3];

        // Row 3
        res.M[3][0] = M1.M[3][0]*M2.M[0][0] + M1.M[3][1]*M2.M[1][0] + M1.M[3][2]*M2.M[2][0] + M1.M[3][3]*M2.M[3][0];
        res.M[3][1] = M1.M[3][0]*M2.M[0][1] + M1.M[3][1]*M2.M[1][1] + M1.M[3][2]*M2.M[2][1] + M1.M[3][3]*M2.M[3][1];
        res.M[3][2] = M1.M[3][0]*M2.M[0][2] + M1.M[3][1]*M2.M[1][2] + M1.M[3][2]*M2.M[2][2] + M1.M[3][3]*M2.M[3][2];
        res.M[3][3] = M1.M[3][0]*M2.M[0][3] + M1.M[3][1]*M2.M[1][3] + M1.M[3][2]*M2.M[2][3] + M1.M[3][3]*M2.M[3][3];

        return res;
    }

}



#endif
