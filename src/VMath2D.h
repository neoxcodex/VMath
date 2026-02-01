//GRAPHICS 2D
#include<iostream>

#include<cmath>

namespace dim2{
    #include"Constants.h"
    struct Vec2{
        float x,y;
    };
    inline float dotProduct(Vec2 a, Vec2 b){
        return (a.x*b.x) + (a.y*b.y);
    }
    inline float magSquared(Vec2 a){
        return dotProduct(a,a);
    }
    inline void vectorCout(Vec2 a){
        std::cout << "3D Vector : (" << a.x << ", " << a.y  <<")" << std::endl;
    }
    inline Vec2 normalize(Vec2 a){
        float mag  = std::sqrt(magSquared(a));
        if (mag == 0){ return Vec2{0,0};}
        float invMag = 1.0f/mag;
        return Vec2{(a.x)*invMag, (a.y)*invMag};

    }
    inline Vec2 scalarMult(Vec2 a, float scalar){
        return Vec2{(a.x*scalar), (a.y*scalar)};
    }
    inline Vec2 add(Vec2 a, Vec2 b){

        return Vec2{(a.x+b.x),(a.y+b.y)};
    }
    inline Vec2 subtract(Vec2 a, Vec2 b){
        return Vec2{(a.x-b.x), (a.y-b.y)};
    }
    inline float distanceSquared(Vec2 a, Vec2 b){
        return magSquared(subtract(a,b));
    }
    inline float angleRAD(Vec2 a, Vec2 b){
        float magA = std::sqrt(magSquared(a));
        float magB = std::sqrt(magSquared(b));
        if (magA == 0 || magB ==0 ){return 0;}
        float cosTheta = (dotProduct(a, b))/(magA*magB);

        if(cosTheta > 1.0){cosTheta = 1.0;}
        if(cosTheta < -1.0){cosTheta = -1.0;}

        return std::acos(cosTheta);
    }
    inline float angleDEG(Vec2 a, Vec2 b){
        return angleRAD(a,b) * constants::INV_PI_180;
    }



    /*TODO AGAIN*/
}
