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



}



#endif
