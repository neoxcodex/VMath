#include<iostream>
#include<vector>
#include <vector>

// Forward Declarations
double magnitudeN(std::vector<double> v);
std::vector<double> normalizeN(std::vector<double> v);
void vecoutN(std::vector<double> a);
std::vector<double> scalarMultN(std::vector<double> vector_, double multiplier);
std::vector<double> addVectorsN(std::vector<double> vec1, std::vector<double> vec2);
std::vector<double> subtractVectorsN(std::vector<double> vec1, std::vector<double> vec2);
double distanceN(std::vector<double> vec1, std::vector<double> vec2);
double dotProductN(std::vector<double> vec1, std::vector<double> vec2);
double angleRAD(std::vector<double> vec1, std::vector<double> vec2);
double angleDEGN(std::vector<double> vec1, std::vector<double> vec2);


int main(){
    std::vector<double> vector1 = {3.0, 4.0, 65.0, 1.0};
    std::vector<double> vector2 = {90.0, 3.0, 4.0, 10.0};
    vecoutN(vector1);
    vecoutN(vector2);
    std::cout << "Angle Between these vectors is (in degree) : "<<angleDEGN(vector1, vector2) << std::endl;
    std::vector<double> addedVectors{};
    addedVectors = addVectorsN(vector1, vector2);
    vecoutN(addedVectors);
    double dotProductvec = dotProductN(vector1, vector2);
    std::cout << "Dot Product is : " << dotProductvec << std::endl;

}
