#define GLM_ENABLE_EXPERIMENTAL  // Add this first
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <iostream>


#include "VMath/Math/NDSFunctions.hpp"
#include "VMath/Math/VMath2D.hpp"
#include "VMath/Math/VMath3D.hpp"
#include "VMath/Math/VMath3D+.hpp"
#include "VMath/Math/VMathN.hpp"
#include "VMath/Profiler/profiler.hpp"
// Use the same profiler macro you used for VMath
#define PROFILE_GLM(id, name, call) \
    profiler::profileFunction("G" #id ": " name, [&]() { return call; })
#define PROFILE_VMATH(id, name, call) \
    profiler::profileFunction("F" #id ": " name, [&]() { return call; })

int main() {
    // --- Data Setup ---
    float f1 = 1.0f, f2 = 2.0f, f3 = 0.5f;
    glm::vec2 a2{1, 2}, b2{3, 4};
    glm::vec3 a3{1, 2, 3}, b3{4, 5, 6}, axis{0, 1, 0};
    glm::mat3 m3(1.0f); 
    glm::vec4 a4{1, 2, 3, 1}, b4{4, 5, 6, 1};
    glm::mat4 m4(1.0f);

    //THIS IS VIBCODED
    // --- GLM Equiv to dim2 ---
    PROFILE_GLM(4,  "glm::vec2::op+", a2 + b2);
    PROFILE_GLM(7,  "glm::dot(vec2)", glm::dot(a2, b2));
    PROFILE_GLM(9,  "glm::normalize(vec2)", glm::normalize(a2));
    PROFILE_GLM(11, "glm::angle(vec2)", glm::angle(glm::normalize(a2), glm::normalize(b2)));

    // --- GLM Equiv to dim3 ---
    PROFILE_GLM(14, "glm::vec3::op+", a3 + b3);
    PROFILE_GLM(18, "glm::mat3(1.0f)", glm::mat3(1.0f));
    PROFILE_GLM(23, "glm::mat3::op*", m3 * a3);
    PROFILE_GLM(24, "glm::dot(vec3)", glm::dot(a3, b3));
    PROFILE_GLM(26, "glm::normalize(vec3)", glm::normalize(a3));
    PROFILE_GLM(32, "glm::cross", glm::cross(a3, b3));
    PROFILE_GLM(35, "glm::mat3*mat3", m3 * m3);
    
    // GLM Rotation (Equiv to your genRotationX)
    PROFILE_GLM(37, "glm::rotate(X)", glm::rotate(glm::mat4(1.0f), f1, glm::vec3(1,0,0)));

    // --- GLM Equiv to dim4 ---
    PROFILE_GLM(44, "glm::mat4(1.0f)", glm::mat4(1.0f));
    PROFILE_GLM(49, "glm::translate", glm::translate(m4, a3));
    PROFILE_GLM(50, "glm::scale", glm::scale(m4, a3));
    PROFILE_GLM(55, "glm::mat4::op*", m4 * a4);
    PROFILE_GLM(70, "glm::mat4*mat4", m4 * m4);

    // --- GLM Equiv to your worldToScreen (Projection) ---
    // Note: GLM uses a combined lookAt and project call
    glm::mat4 view = glm::lookAt(a3, b3, axis);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 16.0f/9.0f, 0.1f, 100.0f);
    PROFILE_GLM(69, "glm::project", glm::project(a3, view, proj, glm::vec4(0,0,1920,1080)));


    std::cout << "GLM TESTING COMPLETE, VMATH TESTING INITIATED:" << std::endl;
    //THIS IS HANDWRITTEN

    // --- Data Setup ---
    float vf1 = 1.0f, vf2 = 2.0f, vf3 = 0.5f;
    dim2::Vec2 va2{1, 2}, vb2{3, 4};
    dim3::Vec3 va3{1, 2, 3}, vb3{4, 5, 6}, vaxis{0, 1, 0};
    dim3::Mat3 vm3 = dim3::Mat3::identity();
    dim4::Vec4 va4{1, 2, 3, 1}, vb4{4, 5, 6, 1};
    dim4::Mat4 vm4 = dim4::Mat4::identity();
    std::vector<double> vn1(10, 1.0), vn2(10, 2.0);

  // --- NDSF (Namespace) ---
    PROFILE_VMATH(1, "NDSF::clamp", NDSF::clamp(vf1, 0.0f, 5.0f));
    PROFILE_VMATH(2, "NDSF::epEqual", NDSF::epEqual(vf1, vf2));
    PROFILE_VMATH(3, "NDSF::lerp", NDSF::lerp(vf1, vf2, vf3));

    // --- dim2::Vec2 (Struct Members) ---
    PROFILE_VMATH(4, "dim2::Vec2::op+", va2 + vb2);
    PROFILE_VMATH(5, "dim2::Vec2::op-", va2 - vb2);
    PROFILE_VMATH(6, "dim2::Vec2::op*", va2 * vf1);

    // --- dim2 (Namespace Functions) ---
    PROFILE_VMATH(7,  "dim2::dotProduct", dim2::dotProduct(va2, vb2));
    PROFILE_VMATH(8,  "dim2::magSquared", dim2::magSquared(va2));
    PROFILE_VMATH(9,  "dim2::normalize", dim2::normalize(va2));
    PROFILE_VMATH(10, "dim2::distanceSquared", dim2::distanceSquared(va2, vb2));
    PROFILE_VMATH(11, "dim2::angleRAD", dim2::angleRAD(va2, vb2));
    PROFILE_VMATH(12, "dim2::angleDEG", dim2::angleDEG(va2, vb2));
    PROFILE_VMATH(13, "dim2::lerp", dim2::lerp(va2, vb2, vf3));

    // --- dim3::Vec3 (Struct Members) ---
    PROFILE_VMATH(14, "dim3::Vec3::op+", va3 + vb3);
    PROFILE_VMATH(15, "dim3::Vec3::op-", va3 - vb3);
    PROFILE_VMATH(16, "dim3::Vec3::op*", va3 * vf1);
    PROFILE_VMATH(17, "dim3::Vec3::op==", va3 == vb3);

    // --- dim3::Mat3 (Struct Members) ---
    PROFILE_VMATH(18, "dim3::Mat3::identity", dim3::Mat3::identity());
    PROFILE_VMATH(19, "dim3::Mat3::genRotator", dim3::Mat3::genRotator(vaxis, vf1));
    PROFILE_VMATH(20, "dim3::Mat3::genRotationX", dim3::Mat3::genRotationX(vf1));
    PROFILE_VMATH(21, "dim3::Mat3::genRotationY", dim3::Mat3::genRotationY(vf1));
    PROFILE_VMATH(22, "dim3::Mat3::genRotationZ", dim3::Mat3::genRotationZ(vf1));
    PROFILE_VMATH(23, "dim3::Mat3::op*", vm3 * va3);

    // --- dim3 (Namespace Functions) ---
    PROFILE_VMATH(24, "dim3::dotProduct", dim3::dotProduct(va3, vb3));
    PROFILE_VMATH(25, "dim3::magSquared", dim3::magSquared(va3));
    PROFILE_VMATH(26, "dim3::normalize", dim3::normalize(va3));
    PROFILE_VMATH(27, "dim3::distanceSquared", dim3::distanceSquared(va3, vb3));
    PROFILE_VMATH(28, "dim3::angleRAD", dim3::angleRAD(va3, vb3));
    PROFILE_VMATH(29, "dim3::angleDEG", dim3::angleDEG(va3, vb3));
    PROFILE_VMATH(30, "dim3::scalarProject", dim3::scalarProject(va3, vb3));
    PROFILE_VMATH(31, "dim3::vectorProject", dim3::vectorProject(va3, vb3));
    PROFILE_VMATH(32, "dim3::crossProduct", dim3::crossProduct(va3, vb3));
    PROFILE_VMATH(33, "dim3::epVectorEqual", dim3::epVectorEqual(va3, vb3));
    PROFILE_VMATH(34, "dim3::lerp", dim3::lerp(va3, vb3, vf3));
    PROFILE_VMATH(35, "dim3::matrixMultiply", dim3::matrixMultiply(vm3, vm3));
    PROFILE_VMATH(36, "dim3::rotationCustomAxis", dim3::rotationCustomAxis(va3, vaxis, vf1));
    PROFILE_VMATH(37, "dim3::rotationXAxis", dim3::rotationXAxis(va3, vf1));
    PROFILE_VMATH(38, "dim3::rotationYAxis", dim3::rotationYAxis(va3, vf1));
    PROFILE_VMATH(39, "dim3::rotationZAxis", dim3::rotationZAxis(va3, vf1));

    // --- dim4::Vec4 (Struct Members) ---
    PROFILE_VMATH(40, "dim4::Vec4::op==", va4 == vb4);
    PROFILE_VMATH(41, "dim4::Vec4::op+", va4 + vb4);
    PROFILE_VMATH(42, "dim4::Vec4::op-", va4 - vb4);
    PROFILE_VMATH(43, "dim4::Vec4::op*", va4 * vf1);

    // --- dim4::Mat4 (Struct Members) ---
    PROFILE_VMATH(44, "dim4::Mat4::identity", dim4::Mat4::identity());
    PROFILE_VMATH(45, "dim4::Mat4::genRotator", dim4::Mat4::genRotator(va3, vf1));
    PROFILE_VMATH(46, "dim4::Mat4::genRotationX", dim4::Mat4::genRotationX(vf1));
    PROFILE_VMATH(47, "dim4::Mat4::genRotationY", dim4::Mat4::genRotationY(vf1));
    PROFILE_VMATH(48, "dim4::Mat4::genRotationZ", dim4::Mat4::genRotationZ(vf1));
    PROFILE_VMATH(49, "dim4::Mat4::genTranslation", dim4::Mat4::genTranslation(vf1, vf2, vf3));
    PROFILE_VMATH(50, "dim4::Mat4::genScaling", dim4::Mat4::genScaling(vf1, vf2, vf3));
    PROFILE_VMATH(51, "dim4::Mat4::homoToVec3", dim4::Mat4::homoToVec3(va4));
    PROFILE_VMATH(52, "dim4::Mat4::Vec3toHomo", dim4::Mat4::Vec3toHomo(va3));
    PROFILE_VMATH(53, "dim4::Mat4::genIntrinsic", dim4::Mat4::genIntrinsic(va2, vf1, vf2));
    PROFILE_VMATH(54, "dim4::Mat4::genExtrinsic", dim4::Mat4::genExtrinsic(va3, vb3));
    PROFILE_VMATH(55, "dim4::Mat4::op*", vm4 * va4);

    // --- dim4 (Namespace Functions) ---
    PROFILE_VMATH(56, "dim4::dotProduct", dim4::dotProduct(va4, vb4));
    PROFILE_VMATH(57, "dim4::magSquared", dim4::magSquared(va4));
    PROFILE_VMATH(58, "dim4::magnitude", dim4::magnitude(va4));
    PROFILE_VMATH(59, "dim4::epVectorEqual", dim4::epVectorEqual(va4, vb4));
    PROFILE_VMATH(60, "dim4::normalize", dim4::normalize(va4));
    PROFILE_VMATH(61, "dim4::lerp", dim4::lerp(va4, vb4, vf3));
    PROFILE_VMATH(62, "dim4::angleRAD", dim4::angleRAD(va4, vb4));
    PROFILE_VMATH(63, "dim4::angleDEG", dim4::angleDEG(va4, vb4));
    PROFILE_VMATH(64, "dim4::toVec4", dim4::toVec4(va3, true));
    PROFILE_VMATH(65, "dim4::calcFocalLength", dim4::calcFocalLength(va2, 1920, 1080));
    PROFILE_VMATH(66, "dim4::calcOffsets", dim4::calcOffsets(1920.0f, 1080.0f));
    PROFILE_VMATH(67, "dim4::cameraSpaceVecToImgSpace", dim4::cameraSpaceVecToImgSpace(va4, va2));
    PROFILE_VMATH(68, "dim4::worldSpaceToCameraSpace", dim4::worldSpaceToCameraSpace(va3, va3, vb3));
    PROFILE_VMATH(69, "dim4::worldToScreen", dim4::worldToScreen(va3, va3, vb3, va2));
    PROFILE_VMATH(70, "dim4::matrixMultiply", dim4::matrixMultiply(vm4, vm4));

    // --- dimN (Namespace Functions) ---
    PROFILE_VMATH(71, "dimN::magnitude", dimN::magnitude(vn1));
    PROFILE_VMATH(72, "dimN::normalize", dimN::normalize(vn1));
    PROFILE_VMATH(73, "dimN::scalarMult", dimN::scalarMult(vn1, 2.0));
    PROFILE_VMATH(74, "dimN::addVectors", dimN::addVectors(vn1, vn2));
    PROFILE_VMATH(75, "dimN::subtractVectors", dimN::subtractVectors(vn1, vn2));
    PROFILE_VMATH(76, "dimN::distance", dimN::distance(vn1, vn2));
    PROFILE_VMATH(77, "dimN::dotProduct", dimN::dotProduct(vn1, vn2));
    PROFILE_VMATH(78, "dimN::angleRAD", dimN::angleRAD(vn1, vn2));
    PROFILE_VMATH(79, "dimN::angleDEG", dimN::angleDEG(vn1, vn2));
    std::cout << "VMATH TESTING COMPLETE, PROGRAM TERMINATED. " << std::endl;
    return 0;
}