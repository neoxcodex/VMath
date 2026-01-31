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


#include<cmath>
#include<vector>
#include<iostream>
namespace constants{
    constexpr double ACCU_PI = 3.14159265358979323846;
    constexpr float PI = 3.14159265f;
    constexpr float INV_PI_180 = 57.2957795f;
}



//AI STUFF
namespace dimN {

    double magnitude(const std::vector<double>& v) {
        double returnmag{0};
        for (int i = 0; i < v.size(); i++) {
            returnmag += (v[i]) * (v[i]);
        }
        return std::sqrt(returnmag);
    }

    std::vector<double> normalize(const std::vector<double>& v) {
        std::vector<double> returnvec;
        double vecmag = magnitude(v);

        for (int i = 0; i < v.size(); i++) {
            double normval = v[i] / vecmag;
            returnvec.push_back(normval);
        }
        return returnvec;
    }

    void vecout(const std::vector<double>& a) {
        std::cout << std::endl << "Vector " << a.size() << "D" << std::endl << "( ";
        for (int i = 0; i < a.size(); i++) {
            if (i == (a.size()-1) ) { std::cout << a[i]; }
            else { std::cout << a[i] << ","; }
        }
        std::cout << " )" << std::endl;
    }

    std::vector<double> scalarMult(const std::vector<double>& vector_, double multiplier) {
        std::vector<double> returnVec;
        for (int i = 0; i < vector_.size(); i++) {
            returnVec.push_back(multiplier * vector_[i]);
        }
        return returnVec;
    }

    std::vector<double> addVectors(const std::vector<double>& vec1, const std::vector<double>& vec2) {
        std::vector<double> returnVec;
        for (int i = 0; i < vec1.size(); i++) {
            returnVec.push_back(vec1[i] + vec2[i]);
        }
        return returnVec;
    }

    std::vector<double> subtractVectors(const std::vector<double>& vec1, const std::vector<double>& vec2) {

        return addVectors(vec1, scalarMult(vec2, -1));
    }

    double distance(const std::vector<double>& vec1, const std::vector<double>& vec2) {
        return magnitude((subtractVectors(vec1, vec2)));
    }

    double dotProduct(const std::vector<double>& vec1, const std::vector<double>& vec2) {
        double returnval{0};
        for (int i = 0; i < vec1.size(); i++) {
            returnval += (vec1[i] * vec2[i]);
        }
        return returnval;
    }

    double angleRAD(const std::vector<double>& vec1, const std::vector<double>& vec2) {
        double angle{0};
        angle = (dotProduct(vec1, vec2)) / (magnitude(vec1) * magnitude(vec2));
        return acos(angle);
    }

    double angleDEG(const std::vector<double>& vec1, const std::vector<double>& vec2) {
        double angle{0};
        angle = angleRAD(vec1, vec2);
        return (angle * (180 / constants::PI));
    }
    //Cross Product for N-dimensional vectors is a huge TODO
}

//GRAPHICS 3D
namespace dim3 {
    struct Vec3{
        float x,y,z;
    };

    float dotProduct(Vec3 a, Vec3 b){
        return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
    }
    float magSquared(Vec3 a){
        return dotProduct(a,a);
    }
    void vectorCout(Vec3 a){
        std::cout << "3D Vector : (" << a.x << ", " << a.y << ", " << a.z <<")" << std::endl;
    }
    Vec3 normalize(Vec3 a){
        float mag  = std::sqrt(magSquared(a));
        if (mag == 0){ return Vec3{0,0,0};}
        float invMag = 1.0f/mag;
        return Vec3{(a.x)*invMag, (a.y)*invMag, (a.z)*invMag};

    }
    Vec3 scalarMult(Vec3 a, float scalar){
        return Vec3{(a.x*scalar), (a.y*scalar), (a.z*scalar)};
    }
    Vec3 add(Vec3 a, Vec3 b){

        return Vec3{(a.x+b.x),(a.y+b.y), (a.z+b.z)};
    }
    Vec3 subtract(Vec3 a, Vec3 b){
        return Vec3{(a.x-b.x), (a.y-b.y), (a.z-b.z)};
    }
    float distanceSquared(Vec3 a, Vec3 b){
        return magSquared(subtract(a,b));
    }
    float angleRAD(Vec3 a, Vec3 b){
        float magA = std::sqrt(magSquared(a));
        float magB = std::sqrt(magSquared(b));
        if (magA == 0 || magB ==0 ){return 0;}
        float cosTheta = (dotProduct(a, b))/(magA*magB);

        if(cosTheta > 1.0){cosTheta = 1.0;}
        if(cosTheta < -1.0){cosTheta = -1.0;}

        return std::acos(cosTheta);
    }
    float angleDEG(Vec3 a, Vec3 b){
        return angleRAD(a,b) * constants::INV_PI_180;
    }

}




//GRAPHICS 2D
namespace dim2{

    struct Vec2{
        float x,y;
    };
        float dotProduct(Vec2 a, Vec2 b){
        return (a.x*b.x) + (a.y*b.y);
    }
    float magSquared(Vec2 a){
        return dotProduct(a,a);
    }
    void vectorCout(Vec2 a){
        std::cout << "3D Vector : (" << a.x << ", " << a.y  <<")" << std::endl;
    }
    Vec2 normalize(Vec2 a){
        float mag  = std::sqrt(magSquared(a));
        if (mag == 0){ return Vec2{0,0};}
        float invMag = 1.0f/mag;
        return Vec2{(a.x)*invMag, (a.y)*invMag};

    }
    Vec2 scalarMult(Vec2 a, float scalar){
        return Vec2{(a.x*scalar), (a.y*scalar)};
    }
    Vec2 add(Vec2 a, Vec2 b){

        return Vec2{(a.x+b.x),(a.y+b.y)};
    }
    Vec2 subtract(Vec2 a, Vec2 b){
        return Vec2{(a.x-b.x), (a.y-b.y)};
    }
    float distanceSquared(Vec2 a, Vec2 b){
        return magSquared(subtract(a,b));
    }
    float angleRAD(Vec2 a, Vec2 b){
        float magA = std::sqrt(magSquared(a));
        float magB = std::sqrt(magSquared(b));
        if (magA == 0 || magB ==0 ){return 0;}
        float cosTheta = (dotProduct(a, b))/(magA*magB);

        if(cosTheta > 1.0){cosTheta = 1.0;}
        if(cosTheta < -1.0){cosTheta = -1.0;}

        return std::acos(cosTheta);
    }
    float angleDEG(Vec2 a, Vec2 b){
        return angleRAD(a,b) * constants::INV_PI_180;
    }



    /*TODO AGAIN*/
}
