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
        /*
        THEORY:
        A Homogenous Coordinate System is Needed:
        Why : A 3x3 Matrix (Mat3) can only warp, shear, rotator the basis vectors of a vector in 3D space, it cannot physically move the vector from the origin
        Thus it can't perform translation
        The BIG Idea:
        Using an Affine Transformation:
        (1) Do a Linear Transformation (as we did with Mat3 and Vec3)
        (2) Translate the Vector
        //So for a matrix which has to do both we need a Mat4 Matrix
        R00 R01 R02 Tx
        R10 R11 R12 Ty
        R20 R21 R22 Tz
         0   0   0   1
        The T bucket is for translating vectors
        R(ij) submatrix is for Mat3 level operations
        (0,0,0,1) is something related to perspective which I do not understand rt now
        */
        //To Move ONLY
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

        //FIXME
        //CAMERA MATRIX UTILS

        //CHANGE OF BASIS (VIEW MATRIX)

        /*
        THEORY:
        CAMERA is Supposed to be STUCK to the origin <0,0,0>
        We then apply transformations and shit to the world and NOT the camera


        "So my idea of what the view matrix does is that it takes the camera vector (yes this is a Vec3 3D world space vector, this vector is normal to the lens of the camera) but then we can just use our normal rotator, function to move this vector right?"

        THIS IS WRONG!


        "THE CAMERA STAYS AT <0,0,0>"
        //SO THE WORLD IS MOVED TO PROVIDE AN ILLUSION THAT THE CAMERA IS MOVING

        So we have: View Matrices
        Basic Direction Sense for the Camera :: (Right, Up, Forward) Basis Vectors
        Let Camera Position is P
        Basis Vectors for the Camera Space are Written in World Space Coordinate System, hence the Rx, Ry, Rz components
        //This Matrix Essentially Takes The World and Moves it According to the Camera
        View Matrix ::
        Rx Ry Rz    -RdotP
        Ux Uy Uz    -UdotP
        Fx Fy Fz    -FdotP
        0  0  0        1
        */
        // static Mat4 genView(const dim3::Vec3& R, const dim3::Vec3& U, const dim3::Vec3& F, const dim3::Vec3& P){
        //     Mat4 res = Mat4::identity();
        //     res.M[0][0] = R.x; res.M[0][1] = R.y; res.M[0][2] = R.z;
        //     res.M[1][0] = U.x; res.M[1][1] = U.y; res.M[1][2] = U.z;
        //     res.M[2][0] = F.x; res.M[2][1] = F.y; res.M[2][2] = F.z;

        //     //Translator

        //     res.M[0][3] = -dim3::dotProduct(R, P);
        //     res.M[1][3] = -dim3::dotProduct(U, P);
        //     res.M[2][3] = -dim3::dotProduct(F, P);

        //     return res;
        // }

        // //Prespective Matrix :: Morphs 3D into 2D space

        // static Mat4 genPerspective(float FOVRad, float aspectRatio, float nearP, float farP){
        //     Mat4 res;

        //     float f = 1.0f / std::tan(FOVRad / 2.0f);

        //     res.M[0][0] = f/aspectRatio;

        //     res.M[1][1] = f;

        //     res.M[2][2] = (farP + nearP) / (nearP - farP);

        //     res.M[2][3] = (2.0f * farP * nearP) / (nearP - farP);

        //     res.M[3][2] = -1.0f;

        //     res.M[3][3] = 0.0f;

        //     return res;

        //     //NDC OUT
        //     //Far Plane +1.0f, and Near Plane -1.0f
        // }



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
