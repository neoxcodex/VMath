#ifndef NDSFunction_30980238
#define NDSFunction_30980238
/*
Non-Dimensions Specific Functions (NDSF)
*/
#include<iostream>
#include"Constants.h"
namespace NDSF{
    inline float clamp(float a, float lowerL, float upperL){
        return std::max(lowerL, std::min(a, upperL));
    }
    inline bool epEqual(float a, float b, float epsilon = constants::EPSILON){
        //FUZZY
        return(std::abs(a-b) <= epsilon);
    }
}



#endif
