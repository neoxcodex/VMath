#ifndef dim4_2309809238
#define dim4_2309809238
#include "Constants.h"
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
    inline Vec4 toVec4(dim3::Vec3& v, bool isPoint= true){
        return {v.x, v.y, v.z, isPoint ? 1.0f : 0.0f};
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
     
        static Mat4 genTranslation(float Tx, float Ty, float Tz){
            Mat4 res = Mat4::identity();
            res.M[0][3] = Tx;
            res.M[1][3] = Ty;
            res.M[2][3] = Tz;
            return res;
        }

        //To Scale
        static Mat4 genScaling(float Sx, float Sy, float Sz){
            Mat4 res = Mat4::identity();
            res.M[0][0] = Sx;
            res.M[1][1] = Sy;
            res.M[2][2] = Sz;
            return res;
        }
        static dim3::Vec3 homoToVec3(Vec4 v){
            float factor = 1/(v.w);
            return {
                v.x*factor, v.y*factor, v.z*factor
            };

        }
        static Vec4 Vec3toHomo(dim3::Vec3 v){
            return{
                v.x, v.y, v.z, 1
            };
        }
        //CAMERA-MATRIX UTILS (Math IO in Homogenous Coords ONLY)
        static Mat4 genIntrinsic(dim2::Vec2 focalLength, float imgPlaneXoffset, float imgPlaneYoffset){
            Mat4 res = Mat4::identity();
            //Homogenous Space && Coords
            //<x,y,z> => <xS, yS, zS, S> (for any arbitraty S)
            //So all homogenous coords are NOT unique
            //<3,2,1> = <6,4,2> = <9,6,3> (Homogenous Coords in 2D space)
            //Homogenous coords back to 3D Cartesian Coords : (1/w)*homoVector
            //As S tends to 0, the dist bw point and origin tends to infinity
            res.M[0][0] = focalLength.x;
            res.M[0][2] = imgPlaneXoffset;
            res.M[1][2] = imgPlaneYoffset;
            res.M[1][1] = focalLength.y;
            res.M[2][2] = 1;
            res.M[3][3] =1;
            return res;
        }//Camera sys (3D homo)--> ImgCoordSys (2D uv homo)
        
        //World Coord Sys (3D homo) ---> CameraCoordSYs (3D homo)
        static Mat4 genExtrinsic(dim3::Vec3 cameraPos, dim3::Vec3 targetPos){
            dim3::Vec3 forward = dim3::normalize(targetPos - cameraPos);
            
            dim3::Vec3 right = dim3::normalize(dim3::crossProduct({0.0f, 1.0f, 0.0f}, forward));
            dim3::Vec3 up = dim3::crossProduct(forward, right);
            Mat4 res = Mat4::identity();

            res.M[0][0] = right.x;
            res.M[0][1] = right.y;
            res.M[0][2] = right.z;
            res.M[1][0] = up.x;
            res.M[1][1] = up.y;
            res.M[1][2] = up.z;

            res.M[2][0] = forward.x;
            res.M[2][1] = forward.y;
            res.M[2][2] = forward.z;

            res.M[0][3] = -(dim3::dotProduct(right, cameraPos));
            res.M[1][3] = -(dim3::dotProduct(up, cameraPos));
            res.M[2][3] = -(dim3::dotProduct(forward, cameraPos));
            return res;
        } 
        //Camera Matrix (Convention for this API)
        // 
    };
    inline dim2::Vec2 calcFocalLength(dim2::Vec2 FOVRadxy, int Wpx, int Hpx){
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
    // inline dim2::Vec2 calcOffsets
    inline dim3::Vec3 cameraSpaceVecToImgSpace(Vec4 cameraSVector, dim2::Vec2 fVector, float imgPlaneXoffset=0.0f, float imgPlaneYoffset=0.0f){
        Mat4 matrix = Mat4::genIntrinsic(fVector, imgPlaneXoffset, imgPlaneYoffset);
        Vec4 intermediaryVector = matrix*cameraSVector;
        dim3::Vec3 homoImgSpaceVector = {intermediaryVector.x / intermediaryVector.z, intermediaryVector.y / intermediaryVector.z, 1}; 
        return homoImgSpaceVector;
    }
    inline Vec4 worldSpaceToCameraSpace(dim3::Vec3 worldPos, dim3::Vec3 cameraPos, dim3::Vec3 targetPos) {

        Mat4 viewMatrix = Mat4::genExtrinsic(cameraPos, targetPos);

        Vec4 worldHomo = Mat4::Vec3toHomo(worldPos);
        return viewMatrix * worldHomo;
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
    inline dim2::Vec2 worldToScreen(dim3::Vec3 worldPos, dim3::Vec3 cameraPos, dim3::Vec3 targetPos, dim2::Vec2 focalLength, float ox = 0.0f, float oy = 0.0f) {
        // 1. World Space -> Camera Space
        Vec4 cameraSpacePos = worldSpaceToCameraSpace(worldPos, cameraPos, targetPos);

        // 2. Camera Space -> Image Space (Projection)
        dim3::Vec3 projected = cameraSpaceVecToImgSpace(cameraSpacePos, focalLength, ox, oy);

        // 3. Return as 2D coordinates (u, v)
        return { projected.x, projected.y };
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
