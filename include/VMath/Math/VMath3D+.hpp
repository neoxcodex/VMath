#ifndef dim4_2309809238
#define dim4_2309809238
#include "Constants.hpp"
#include "NDSFunctions.hpp"
#include "VMath3D.hpp"
#include"VMath2D.hpp"
#include<iostream>
#include<cmath>
#include <xmmintrin.h>

namespace dim4{
    struct Vec4{
        float x,y,z,w;
        //STRICT
        bool operator==(const Vec4& other) const{
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
    inline Vec4 toVec4(const dim3::Vec3& v, const bool isPoint= true){
        return {v.x, v.y, v.z, isPoint ? 1.0f : 0.0f};
    }

    //MATRICES
    // MATRICES rewritten for OpenGL NDC compatibility
    struct Mat4 {
        // Hardcoded Identity state by default
        float M[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };

        static Mat4 identity() {
            return Mat4(); // Returns the hardcoded identity state
        }

        Vec4 operator*(const Vec4& v) const {
            return {
                (v.x * M[0][0]) + (v.y * M[0][1]) + (v.z * M[0][2]) + (v.w * M[0][3]),
                (v.x * M[1][0]) + (v.y * M[1][1]) + (v.z * M[1][2]) + (v.w * M[1][3]),
                (v.x * M[2][0]) + (v.y * M[2][1]) + (v.z * M[2][2]) + (v.w * M[2][3]),
                (v.x * M[3][0]) + (v.y * M[3][1]) + (v.z * M[3][2]) + (v.w * M[3][3])
            };
        }

        // Fixed Intrinsic: Maps Camera Space -> NDC [-1, 1]
        static Mat4 genIntrinsic(const dim2::Vec2& focalLength, const dim2::Vec2& offsets, float Wpx, float Hpx) {
            Mat4 res; 
            res.M[0][0] = focalLength.x / (Wpx / 2.0f);
            res.M[1][1] = focalLength.y / (Hpx / 2.0f);

   
            res.M[0][2] = (offsets.x - (Wpx / 2.0f)) / (Wpx / 2.0f);
            res.M[1][2] = (offsets.y - (Hpx / 2.0f)) / (Hpx / 2.0f);

            res.M[2][2] = 1.0f; 
            res.M[3][2] = 1.0f; 
            res.M[3][3] = 0.0f; 
            return res;
        }

        static Mat4 genExtrinsic(const dim3::Vec3& cameraPos, const dim3::Vec3& targetPos) {
            dim3::Vec3 zAxis = dim3::normalize(cameraPos - targetPos); // Forward points away from target
            dim3::Vec3 xAxis = dim3::normalize(dim3::crossProduct({0.0f, 1.0f, 0.0f}, zAxis));
            dim3::Vec3 yAxis = dim3::crossProduct(zAxis, xAxis);

            Mat4 res;
            res.M[0][0] = xAxis.x; res.M[0][1] = xAxis.y; res.M[0][2] = xAxis.z;
            res.M[1][0] = yAxis.x; res.M[1][1] = yAxis.y; res.M[1][2] = yAxis.z;
            res.M[2][0] = zAxis.x; res.M[2][1] = zAxis.y; res.M[2][2] = zAxis.z;

            res.M[0][3] = -(dim3::dotProduct(xAxis, cameraPos));
            res.M[1][3] = -(dim3::dotProduct(yAxis, cameraPos));
            res.M[2][3] = -(dim3::dotProduct(zAxis, cameraPos));
            return res;
        }

        static Mat4 genRotationX(float angle) {
            Mat4 res; float s = sinf(angle), c = cosf(angle);
            res.M[1][1] = c; res.M[1][2] = -s; res.M[2][1] = s; res.M[2][2] = c;
            return res;
        }

        static Mat4 genRotationY(float angle) {
            Mat4 res; float s = sinf(angle), c = cosf(angle);
            res.M[0][0] = c; res.M[0][2] = s; res.M[2][0] = -s; res.M[2][2] = c;
            return res;
        }

        static Mat4 genRotationZ(float angle) {
            Mat4 res; float s = sinf(angle), c = cosf(angle);
            res.M[0][0] = c; res.M[0][1] = -s; res.M[1][0] = s; res.M[1][1] = c;
            return res;
        }

        static Mat4 genTranslation(float x, float y, float z) {
            Mat4 res; res.M[0][3] = x; res.M[1][3] = y; res.M[2][3] = z;
            return res;
        }

        static Vec4 Vec3toHomo(const dim3::Vec3& v) { return {v.x, v.y, v.z, 1.0f}; }
    };

    
    inline dim2::Vec2 calcFocalLength(const dim2::Vec2& FOVRadxy, const int Wpx, const int Hpx){
        dim2::Vec2 focalVector;
        focalVector.x = Wpx/(2*std::tan(FOVRadxy.x/2));
        focalVector.y = Hpx/(2*std::tan(FOVRadxy.y/2));
        return focalVector;
    }
    inline dim2::Vec2 calcOffsets(float Wpx, float Hpx){
        dim2::Vec2 offsetVector;
        offsetVector.x = Wpx/2.0f;
        offsetVector.y = Hpx/2.0f;
        return offsetVector;
    }
    inline dim3::Vec3 cameraSpaceVecToImgSpace(const Vec4& cameraSVector, const dim2::Vec2& fVector, float W, float H, const dim2::Vec2& offsets) {
        Mat4 matrix = Mat4::genIntrinsic(fVector, offsets, W, H);
        Vec4 projected = matrix * cameraSVector;
        float wInv = (projected.w != 0) ? 1.0f / projected.w : 1.0f;
        return {projected.x * wInv, projected.y * wInv, 1.0f}; 
    }

    inline dim2::Vec2 worldToNDC(const dim3::Vec3& worldPos, const dim3::Vec3& cameraPos, const dim3::Vec3& targetPos, const dim2::Vec2& FOV, float W, float H) {
        dim2::Vec2 focal = calcFocalLength(FOV, (int)W, (int)H);
        dim2::Vec2 offsets = calcOffsets(W, H);
        
        Vec4 camSpace = Mat4::genExtrinsic(cameraPos, targetPos) * Mat4::Vec3toHomo(worldPos);
        Vec4 projected = Mat4::genIntrinsic(focal, offsets, W, H) * camSpace;
        
        float wInv = (projected.w != 0) ? 1.0f / projected.w : 1.0f;
        return { projected.x * wInv, -(projected.y * wInv) }; // Y-flip for OpenGL
    }

    inline void matrixCout(const Mat4& matrix){
        std::cout << "Formatting : M <i,j>" << std::endl;
        for(int i =0; i <=3; i++){
            for(int j = 0; j <= 3; j++){
                std::cout <<"<" << i << ", " << j << "> : " << matrix.M[i][j] << "  ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

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
