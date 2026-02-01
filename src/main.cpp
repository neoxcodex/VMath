
#include "Constants.h"
#include"VMath3D.hpp"
#include"VMath2D.hpp"
#include"NDSFunctions.hpp"
#include"VMathN.hpp"
#include<iostream>
int main(){
   dim3::Vec3 v1{1.0f, 0.0f, 0.0f};
   dim3::Vec3 v2{0.0f, 1.0f, 0.0f};
   dim3::Vec3 newVec = dim3::crossProduct(v1, v2);
   dim3::vectorCout(newVec);
   if(NDSF::epEqual(dim3::angleRAD(newVec, v1), (constants::PI / 2.0f))){
      std::cout << "Yeah its okay!" << std::endl;
   }
}
