/*
TODO:
1) Get Accurate PI
2) Get Better Precision With preferrably a custom Data type
3) Allow for a dim3, dim2 namespace under which hardcoded 3D, 2D vector functions rest
4) Remove the pass by value goddamnit
5) Do something about those for loops (repetitive tbh)
6) Add More Vector Operations
7) Optimize the shit outta dim3, dim2
8) Error Handling
9) Clamping

*/

#ifndef dim3
#define dim3
#include<cmath>

#include<iostream>

#include"Constants.h"


//AI STUFF


//GRAPHICS 3D
namespace dim3 {

    struct Vec3{
        float x,y,z;
        Vec3 operator+(const Vec3& other) const{
            return {x + other.x, y + other.y, z + other.z};
        }
        Vec3 operator-(const Vec3& other)const {
            return {x - other.x, y-other.y, z-other.z};
        }
        Vec3 operator*(float scalar) const{
            return {x*scalar, y*scalar, z*scalar};
        }

    };
    inline Vec3 operator*(float scalar, const Vec3& v) {
        return v * scalar; // Reuse the member operator you already wrote!
    }
    inline float dotProduct(const Vec3& a, const Vec3& b){
        return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
    }
    inline float magSquared(const Vec3& a){
        return dotProduct(a,a);
    }
    inline void vectorCout(const Vec3& a){
        std::cout << "3D Vector : (" << a.x << ", " << a.y << ", " << a.z <<")" << std::endl;
    }
    inline Vec3 normalize(const Vec3& a){
        float mag  = std::sqrt(magSquared(a));
        if (mag == 0){ return Vec3{0,0,0};}
        float invMag = 1.0f/mag;
        return Vec3{(a.x)*invMag, (a.y)*invMag, (a.z)*invMag};

    }
    inline float distanceSquared(const Vec3& a, const Vec3& b){
        return magSquared(a-b);
    }
    inline float angleRAD(const Vec3& a, const Vec3& b, bool returnCosValue = false){
        float magA = std::sqrt(magSquared(a));
        float magB = std::sqrt(magSquared(b));
        if (magA == 0 || magB ==0 ){return 0;}
        float cosTheta = (dotProduct(a, b))/(magA*magB);

        if(cosTheta > 1.0){cosTheta = 1.0;}
        if(cosTheta < -1.0){cosTheta = -1.0;}

        if(!returnCosValue){return std::acos(cosTheta);}
        else{return cosTheta;}
    }
    inline float angleDEG(const Vec3& a, const Vec3& b){
        return angleRAD(a,b) * constants::INV_PI_180;
    }
    inline float scalarProject(const Vec3& vecToProj, const Vec3& vecToProjAlong){
        float magAlong = std::sqrt(magSquared(vecToProjAlong));
        return (dotProduct(vecToProjAlong, vecToProj) / magAlong);

    }
    inline Vec3 vectorProject(const Vec3& vecToProj, const Vec3& vecToProjAlong){
        // return scalarMult(normalize(vecToProjAlong),scalarProject(vecToProj, vecToProjAlong)); (This is BAD; Multiple function calls, temp objects.. slow)
        //Fast Version
        float dotProd = dotProduct(vecToProjAlong, vecToProj);
        float magSq = magSquared(vecToProjAlong);
        return (vecToProjAlong*(dotProd/magSq));
    }

}






#endif





