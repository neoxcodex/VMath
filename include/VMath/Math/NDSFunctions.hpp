#ifndef NDSFunction_30980238
#define NDSFunction_30980238
/*
Non-Dimension Specific Functions (NDSF)
*/
#include<cmath>
#include"Constants.hpp"
namespace NDSF{
    inline float clamp(float a, float lowerL, float upperL){
        return std::max(lowerL, std::min(a, upperL));
    }
    inline bool epEqual(float a, float b, float epsilon = constants::EPSILON){
        //FUZZY
        return(std::abs(a-b) <= epsilon);
    }
    inline float lerp(float a, float b, float t){
        //Jus Point Slope With :: y0 = initial, y1 = end, x0 = 0, x1 = 1, x = t and m = (v2-v1)
        float clT = clamp(t, 0.0f, 1.0f);
        return a + (b-a)*clT;
    }
}



#endif
