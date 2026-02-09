#ifndef dimN_30298409238
#define dimN_30298409238
#include<cmath>

#include<iostream>

#include"Constants.hpp"
#include<iostream>
#include<vector>

namespace dimN {

    inline double magnitude(const std::vector<double>& v) {
        double returnmag{0};
        for (int i = 0; i < v.size(); i++) {
            returnmag += (v[i]) * (v[i]);
        }
        return std::sqrt(returnmag);
    }

    inline std::vector<double> normalize(const std::vector<double>& v) {
        std::vector<double> returnvec;
        double vecmag = magnitude(v);

        for (int i = 0; i < v.size(); i++) {
            double normval = v[i] / vecmag;
            returnvec.push_back(normval);
        }
        return returnvec;
    }

    inline void vecout(const std::vector<double>& a) {
        std::cout << std::endl << "Vector " << a.size() << "D" << std::endl << "( ";
        for (int i = 0; i < a.size(); i++) {
            if (i == (a.size()-1) ) { std::cout << a[i]; }
            else { std::cout << a[i] << ","; }
        }
        std::cout << " )" << std::endl;
    }

    inline std::vector<double> scalarMult(const std::vector<double>& vector_, double multiplier) {
        std::vector<double> returnVec;
        for (int i = 0; i < vector_.size(); i++) {
            returnVec.push_back(multiplier * vector_[i]);
        }
        return returnVec;
    }

    inline std::vector<double> addVectors(const std::vector<double>& vec1, const std::vector<double>& vec2) {
        std::vector<double> returnVec;
        for (int i = 0; i < vec1.size(); i++) {
            returnVec.push_back(vec1[i] + vec2[i]);
        }
        return returnVec;
    }

    inline std::vector<double> subtractVectors(const std::vector<double>& vec1, const std::vector<double>& vec2) {

        return addVectors(vec1, scalarMult(vec2, -1));
    }

    inline double distance(const std::vector<double>& vec1, const std::vector<double>& vec2) {
        return magnitude((subtractVectors(vec1, vec2)));
    }

    inline double dotProduct(const std::vector<double>& vec1, const std::vector<double>& vec2) {
        double returnval{0};
        for (int i = 0; i < vec1.size(); i++) {
            returnval += (vec1[i] * vec2[i]);
        }
        return returnval;
    }

    inline double angleRAD(const std::vector<double>& vec1, const std::vector<double>& vec2) {
        double angle{0};
        angle = (dotProduct(vec1, vec2)) / (magnitude(vec1) * magnitude(vec2));
        return acos(angle);
    }

    inline double angleDEG(const std::vector<double>& vec1, const std::vector<double>& vec2) {
        double angle{0};
        angle = angleRAD(vec1, vec2);
        return (angle * (180 / constants::PI));
    }
    //Cross Product for N-dimensional vectors is a huge TODO
    }
#endif
