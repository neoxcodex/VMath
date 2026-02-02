#ifndef visualizer_2890938098035
#define visualizer_2890938098035

/*

TODO:
Visualizer
Registry System
visualizer::pushVecVisual(dim3::Vec3 Vector)
visualizer::pullVecVisual(VectorID) (in registry)
x-y-z Axes
The Visualizer Checks the values of the vectors in the reigstry and updates them according to main.cpp
Real Time
Multi-Threading Preferred
*/
#include "VMath/Math/VMath3D+.hpp"
#include "VMath/Math/VMath3D.hpp"
#include<unordered_map>
#include<string>
#include<iostream>
namespace visualizer{
    inline std::unordered_map<int, dim4::Vec4> registry;
    inline int nextID = 0;
    inline int pushVecVisual(dim4::Vec4 vector){
        //Takes Vec3 as Input Provides Vec3 ID as Output
        int id = nextID++;
        registry[id] = vector;
        return id;
    }
    inline bool pullVecVisual(int vectorID){
        //0 for success & 1 for failure
        if (registry.find(vectorID) != registry.end()){
            registry.erase(vectorID);
            return true;
        }
        return false;
    }
}

#endif
