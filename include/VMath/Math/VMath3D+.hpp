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
