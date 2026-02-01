
#include"VMath3D.hpp"
#include"VMath2D.hpp"

#include"VMathN.hpp"
#include<iostream>
int main(){
   dim3::Vec3 v1{1.0f, 2.0f, 3.0f};
   dim3::Vec3 v2{5.0f, 2.0f, 33.0f};
   dim3::Vec3 newVec = (v1+v2*2.0f);
   dim3::vectorCout(newVec);
}
