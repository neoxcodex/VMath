#ifndef dim2_239785980
#define dim2_239785980

//GRAPHICS 2D
#include<iostream>
#include"Constants.h"
#include<cmath>
#include"NDSFunctions.hpp"
namespace dim2{

    struct Vec2{
        float x,y;
        Vec2 operator+(const Vec2& other) const{
            return {x + other.x, y + other.y};
        }
        Vec2 operator-(const Vec2& other)const {
            return {x - other.x, y-other.y};
        }
        Vec2 operator*(float scalar) const{
            return {x*scalar, y*scalar};
        }
    };
    inline float dotProduct(const Vec2& a, const Vec2& b){
        return (a.x*b.x) + (a.y*b.y);
    }
    inline float magSquared(const Vec2& a){
        return dotProduct(a,a);
    }
    inline void vectorCout(const Vec2& a){
        std::cout << "2D Vector : (" << a.x << ", " << a.y  <<")" << std::endl;
    }
    inline Vec2 normalize(const Vec2& a){
        float mag  = std::sqrt(magSquared(a));
        if (mag == 0){ return Vec2{0,0};}
        float invMag = 1.0f/mag;
        return Vec2{(a.x)*invMag, (a.y)*invMag};

    }

    inline float distanceSquared(const Vec2& a, const Vec2& b){
        return magSquared(a-b);
    }
    inline float angleRAD(const Vec2& a, const Vec2& b){
        float magA = std::sqrt(magSquared(a));
        float magB = std::sqrt(magSquared(b));
        if (magA == 0 || magB ==0 ){return 0;}
        float cosTheta = (dotProduct(a, b))/(magA*magB);

        if(cosTheta > 1.0){cosTheta = 1.0;}
        if(cosTheta < -1.0){cosTheta = -1.0;}

        return std::acos(cosTheta);
    }
    inline float angleDEG(const Vec2& a, const Vec2& b){
        return angleRAD(a,b) * constants::INV_PI_180;
    }
    inline Vec2 lerp(const Vec2& v1, const Vec2& v2, float t){
        float a = NDSF::clamp(t, 0.0f, 1.0f);
        return
        {
            v1.x + a*(v2.x - v1.x),
            v1.y + a*(v2.y - v1.y)
        };
    }

    /*TODO AGAIN*/
}
#endif
