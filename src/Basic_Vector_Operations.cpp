/*
TODO:
1) Get Accurate PI
2) Get Better Precision With preferrably a custom Data type
3) Allow for a dim3, dim2 namespace under which hardcoded 3D, 2D vector functions rest
4) Remove the pass by value goddamnit
5) Do something about those for loops (repetitive tbh)
6) Add More Vector Operations
7) Optimize the shit outta this
8) Error Handling
9) Clamping

*/


#include<cmath>
#include<vector>
#include<iostream>
namespace constants{

    constexpr double PI = 3.1415926535897932384626433832795;
}



//AI STUFF
namespace dimN {
    double magnitudeN(std::vector<double> v){
        double returnmag{0};
        for (int i = 0; static_cast<double>(i) <= (v.size()-1); i++){
            returnmag += (v[i])*(v[i]);

        }
        return std::sqrt(returnmag);
    }
    std::vector<double> normalizeN(std::vector<double> v){
        std::vector<double> returnvec;
        double vecmag = magnitudeN(v);

        for(int i = 0; i <= (static_cast<double>(v.size() - 1)); i++){
            double normval = v[i] / vecmag;
            returnvec.push_back(normval);
        }
        return returnvec;

    }
    void vecoutN(std::vector<double> a){
        std::cout << std::endl << "Vector " << a.size() << "D" << std::endl << "( ";
        for(int i = 0; i <= (static_cast<double>(a.size() - 1)); i++){
            if (i == (static_cast<double>(a.size() - 1))){std::cout << a[i];}
            else{   std::cout << a[i] << ",";}
        }
        std::cout << " )" << std::endl;

    }
    std::vector<double> scalarMultN(std::vector<double> vector_, double multiplier){
        std::vector<double> returnVec;
        for(int i = 0; i <= (static_cast<double>(vector_.size() - 1)); i++){
            returnVec.push_back(multiplier*vector_[i]);
        }
        return returnVec;
    }
    std::vector<double> addVectorsN(std::vector<double> vec1, std::vector<double> vec2){

        std::vector<double> returnVec;
        for(int i = 0; i <= (static_cast<double>(vec1.size() - 1)); i++){
            returnVec.push_back(vec1[i] + vec2[i]);
        }
        return returnVec;

    }
    std::vector<double> subtractVectorsN(std::vector<double> vec1, std::vector<double> vec2){
        return addVectorsN(vec1, scalarMultN(vec2, -1));
    }

    double distanceN(std::vector<double> vec1, std::vector<double> vec2){
        return magnitudeN((subtractVectorsN(vec1, vec2)));
    }
    double dotProductN(std::vector<double> vec1, std::vector<double> vec2){

        double returnval{0};
        for(int i = 0; i <= (static_cast<double>(vec1.size() - 1)); i++){
            returnval +=(vec1[i] * vec2[i]);
        }
        return returnval;

    }
    double angleRAD(std::vector<double> vec1, std::vector<double>vec2){

        double angle{0};
        angle = (dotProductN(vec1, vec2))/(magnitudeN(vec1)*magnitudeN(vec2));
        return acos(angle);
    }
    double angleDEGN(std::vector<double> vec1, std::vector<double>vec2){

        double angle{0};
        angle = angleRAD(vec1, vec2);
        return (angle*(180/constants::PI));

    }
}


//GRAPHICS
namespace dim3 {
    struct Vec3{
        double x,y,z;
    };


    /*TODO*/


}
namespace dim2{

    struct Vec2{
        double x,y;
    };



    /*TODO AGAIN*/
}
