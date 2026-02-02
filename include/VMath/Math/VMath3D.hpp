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

#ifndef dim3_872349208
#define dim3_872349208
#include<cmath>

#include<iostream>

#include"Constants.h"
#include "NDSFunctions.hpp"

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
        bool operator==(const Vec3& other) const {
            return
            (
                (x == other.x)
                &&
                (y == other.y)
                &&
                (z == other.z)
            );
            //STRICT
        }

    };
    inline Vec3 operator*(float scalar, const Vec3& v) {
        return v * scalar;
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
        float cosTheta = NDSF::clamp(dotProduct(a, b)/(magA*magB), -1.0f, 1.0f);

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
    inline Vec3 crossProduct(const Vec3& a, const Vec3& b){

        return Vec3{
            (a.y*b.z - a.z*b.y),
            (a.z*b.x - a.x*b.z),
            (a.x*b.y - a.y*b.x)
        };

    }

    inline bool epVectorEqual(const Vec3& a,  const Vec3& b) {
        //FUZZY
        return
        (
            (std::abs(a.x-b.x) <= (constants::EPSILON))
            &&
            (std::abs(a.y-b.y) <= (constants::EPSILON))
            &&
            (std::abs(a.z-b.z) <= (constants::EPSILON))
        );
    }
    inline Vec3 lerp(const Vec3& v1, const Vec3& v2, float t){
        float a = NDSF::clamp(t, 0.0f, 1.0f);
        return
        {
            v1.x + a*(v2.x - v1.x),
            v1.y + a*(v2.y - v1.y),
            v1.z + a*(v2.z - v1.z)
        };
    }
    struct Mat3{
        float M[3][3] ={{0}};
        static Mat3 identity(){
            Mat3 res;
            res.M[0][0] = 1; res.M[1][1] = 1;; res.M[2][2] = 1;
            return res;
        }
        Vec3 operator*(const Vec3& v) const{
            return{
                (v.x)*(M[0][0]) + (v.y)*(M[0][1]) + (v.z)*(M[0][2]),
                (v.x)*(M[1][0]) + (v.y)*(M[1][1]) + (v.z)*(M[1][2]),
                (v.x)*(M[2][0]) + (v.y)*(M[2][1]) + (v.z)*(M[2][2])
            };
        }
        static Mat3 genRotatorMatrix(const Vec3& axis_normalized, const float angleRAD){
            Mat3 rotator;
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
        static Mat3 rotationX(float angleRAD){
            float s = std::sin(angleRAD);
            float c = std::cos(angleRAD);
            Mat3 res; // Starts as all zeros

            res.M[0][0] = 1.0f;
            res.M[1][1] = c;
            res.M[1][2] = -s;
            res.M[2][1] = s;
            res.M[2][2] = c;

            return res;
        }
        // Inside struct Mat3 in VMath3D.hpp

        static Mat3 rotationY(float angleRAD) {
            float s = std::sin(angleRAD);
            float c = std::cos(angleRAD);
            Mat3 res; // Assuming default constructor zeros the matrix

            res.M[0][0] = c;   res.M[0][2] = s;
            res.M[1][1] = 1.0f;
            res.M[2][0] = -s;  res.M[2][2] = c;

            return res;
        }

        static Mat3 rotationZ(float angleRAD) {
            float s = std::sin(angleRAD);
            float c = std::cos(angleRAD);
            Mat3 res;

            res.M[0][0] = c;  res.M[0][1] = -s;
            res.M[1][0] = s;  res.M[1][1] = c;
            res.M[2][2] = 1.0f;

            return res;
        }

    };
    inline Mat3 matrixMultiply(const Mat3& M1, const Mat3& M2) {
        Mat3 res;
        // ROW 0
        res.M[0][0] = M1.M[0][0]*M2.M[0][0] + M1.M[0][1]*M2.M[1][0] + M1.M[0][2]*M2.M[2][0];
        res.M[0][1] = M1.M[0][0]*M2.M[0][1] + M1.M[0][1]*M2.M[1][1] + M1.M[0][2]*M2.M[2][1];
        res.M[0][2] = M1.M[0][0]*M2.M[0][2] + M1.M[0][1]*M2.M[1][2] + M1.M[0][2]*M2.M[2][2];

        // ROW 1
        res.M[1][0] = M1.M[1][0]*M2.M[0][0] + M1.M[1][1]*M2.M[1][0] + M1.M[1][2]*M2.M[2][0];
        res.M[1][1] = M1.M[1][0]*M2.M[0][1] + M1.M[1][1]*M2.M[1][1] + M1.M[1][2]*M2.M[2][1];
        res.M[1][2] = M1.M[1][0]*M2.M[0][2] + M1.M[1][1]*M2.M[1][2] + M1.M[1][2]*M2.M[2][2];

        // ROW 2
        res.M[2][0] = M1.M[2][0]*M2.M[0][0] + M1.M[2][1]*M2.M[1][0] + M1.M[2][2]*M2.M[2][0];
        res.M[2][1] = M1.M[2][0]*M2.M[0][1] + M1.M[2][1]*M2.M[1][1] + M1.M[2][2]*M2.M[2][1];
        res.M[2][2] = M1.M[2][0]*M2.M[0][2] + M1.M[2][1]*M2.M[1][2] + M1.M[2][2]*M2.M[2][2];

        return res;
    }
    inline Vec3 rotationCustomAxis(const Vec3& v, const Vec3& axis_normalized, float angleRAD){
        float cosA = std::cos(angleRAD);
        float sinA = std::sin(angleRAD);
        float t = 1.0f - cosA;
        float x = axis_normalized.x;
        float y = axis_normalized.y;
        float z = axis_normalized.z;
        Mat3 rotatorMatrix;
        // ROW 0
        rotatorMatrix.M[0][0] = x * x * t + cosA;
        rotatorMatrix.M[0][1] = x * y * t - z * sinA;
        rotatorMatrix.M[0][2] = x * z * t + y * sinA;

        // ROW 1
        rotatorMatrix.M[1][0] = y * x * t + z * sinA;
        rotatorMatrix.M[1][1] = y * y * t + cosA;
        rotatorMatrix.M[1][2] = y * z * t - x * sinA;

        // ROW 2
        rotatorMatrix.M[2][0] = z * x * t - y * sinA;
        rotatorMatrix.M[2][1] = z * y * t + x * sinA;
        rotatorMatrix.M[2][2] = z * z * t + cosA;


        return rotatorMatrix*v;
    }

    inline Vec3 rotationXAxis(const Vec3& v, float angleRAD){
        float cosA = std::cos(angleRAD);
        float sinA = std::sin(angleRAD);
        // x remains unchanged, y and z rotate
        return {
            v.x,
            v.y * cosA - v.z * sinA,
            v.y * sinA + v.z * cosA
        };

    }
    inline Vec3 rotationYAxis(const Vec3& v, float angleRAD) {
        float s = std::sin(angleRAD);
        float c = std::cos(angleRAD);
        return {
            v.x * c + v.z * s,
            v.y,
            -v.x * s + v.z * c
        };
    }

    // Rotates around Z: X and Y change (Standard 2D rotation logic)
    inline Vec3 rotationZAxis(const Vec3& v, float angleRAD) {
        float s = std::sin(angleRAD);
        float c = std::cos(angleRAD);
        return {
            v.x * c - v.y * s,
            v.x * s + v.y * c,
            v.z
        };
    }


}






#endif





