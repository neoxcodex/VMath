#include "VMath/Math/Constants.h"
#include "VMath/Math/VMath3D.hpp"
#include "VMath/Math/VMath2D.hpp"
#include "VMath/Math/NDSFunctions.hpp"
#include "VMath/Math/VMathN.hpp"
// #include "VMath/Vis/visualizer.hpp" // Future home of the visualizer

#include <iostream>

// Create an alias if it's not defined in the header


int main() {
    // Using dim3 namespace from your VMath3D.hpp
    dim3::Vec3 v1{1.0f, 0.0f, 0.0f};
    dim3::Vec3 v2{0.0f, 1.0f, 0.0f};

    // Math check: Cross product of X and Y should be Z (0, 0, 1)
    dim3::Vec3 crossed = dim3::crossProduct(v1, v2);

    // Check angle between Z and X (should be 90 degrees / PI/2)
    float angle = dim3::angleRAD(crossed, v1);

    if (NDSF::epEqual(angle, constants::PI / 2.0f)) {
        std::cout << "YAY IT IS 90 DEG" << std::endl;
        dim3::vectorCout(crossed);
    } else {
        std::cout << "Math check failed. Angle: " << angle << std::endl;
    }

    return 0;
}
