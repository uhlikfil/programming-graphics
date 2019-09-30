#pragma once

#include "loaded_model.h"


class happy_cube : public loaded_model {
public:
	happy_cube(const shader_struct& shader_s, const glm::vec3& position, const glm::vec3& direction, const float& size);
	virtual void create() override;

protected:
	virtual void set_material_uniforms(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, GLuint texture) override;

};

const int cubeNAttribsPerVertex = 8;
const int cubeNVertices = 96;
const int cubeNTriangles = 48;
static const float vertices[] = {
  5.96046e-08f,1.19209e-07f,-1.0f,-0.113259f,0.116122f,-0.986757f,0.5f,0.5f,
  0.0f,-1.26346f,-1.26346f,-0.113259f,0.116122f,-0.986757f,1.0f,0.5f,
  -1.0014f,-1.00311f,-1.00311f,-0.113259f,0.116122f,-0.986757f,1.0f,1.0f,
  -1.0f,2.98023e-07f,-1.0f,-0.113259f,0.116122f,-0.986757f,0.5f,1.0f,
  -1.49012e-07f,-1.78814e-07f,1.0f,-0.113259f,0.116122f,0.986756f,0.5f,0.5f,
  -1.0f,1.78814e-07f,1.0f,-0.113259f,0.116122f,0.986756f,1.0f,0.5f,
  -1.0014f,-1.00311f,1.00311f,-0.113259f,0.116122f,0.986756f,1.0f,1.0f,
  -5.66244e-07f,-1.26346f,1.26346f,-0.113259f,0.116122f,0.986756f,0.5f,1.0f,
  1.43425f,-2.98023e-07f,0.0f,0.956466f,-0.206366f,0.206365f,0.5f,0.5f,
  1.0f,-5.36442e-07f,1.0f,0.956466f,-0.206366f,0.206365f,1.0f,0.5f,
  1.0014f,-1.00311f,1.00311f,0.956466f,-0.206366f,0.206365f,1.0f,1.0f,
  1.0f,-1.0f,0.0f,0.956466f,-0.206366f,0.206365f,0.5f,1.0f,
  -2.98023e-07f,-1.0f,0.0f,-0.113259f,-0.986756f,-0.116122f,0.5f,0.5f,
  -5.66244e-07f,-1.26346f,1.26346f,-0.113259f,-0.986756f,-0.116122f,1.0f,0.5f,
  -1.0014f,-1.00311f,1.00311f,-0.113259f,-0.986756f,-0.116122f,1.0f,1.0f,
  -1.0f,-1.0f,0.0f,-0.113259f,-0.986756f,-0.116122f,0.5f,1.0f,
  -1.43425f,2.38419e-07f,0.0f,-0.956466f,0.206366f,0.206365f,0.5f,0.5f,
  -1.0f,1.78814e-07f,1.0f,-0.956466f,0.206366f,0.206365f,1.0f,0.5f,
  -1.0014f,1.00311f,1.00311f,-0.956466f,0.206366f,0.206365f,1.0f,1.0f,
  -1.0f,1.0f,0.0f,-0.956466f,0.206366f,0.206365f,0.5f,1.0f,
  2.38419e-07f,1.0f,0.0f,-0.113259f,0.986756f,0.116122f,0.5f,0.5f,
  1.8999e-07f,1.26346f,-1.26346f,-0.113259f,0.986756f,0.116122f,1.0f,0.5f,
  -1.0014f,1.00311f,-1.00311f,-0.113259f,0.986756f,0.116122f,1.0f,1.0f,
  -1.0f,1.0f,0.0f,-0.113259f,0.986756f,0.116122f,0.5f,1.0f,
  2.5332e-07f,1.26346f,1.26346f,-0.113259f,0.986756f,-0.116121f,0.0f,0.5f,
  2.38419e-07f,1.0f,0.0f,-0.113259f,0.986756f,-0.116121f,0.5f,0.5f,
  -1.0f,1.0f,0.0f,-0.113259f,0.986756f,-0.116121f,0.5f,1.0f,
  -1.0014f,1.00311f,1.00311f,-0.113259f,0.986756f,-0.116121f,0.0f,1.0f,
  1.0014f,1.00311f,1.00311f,0.113259f,0.986757f,-0.116121f,0.0f,0.0f,
  1.0f,1.0f,0.0f,0.113259f,0.986757f,-0.116121f,0.5f,0.0f,
  2.38419e-07f,1.0f,0.0f,0.113259f,0.986757f,-0.116121f,0.5f,0.5f,
  2.5332e-07f,1.26346f,1.26346f,0.113259f,0.986757f,-0.116121f,0.0f,0.5f,
  1.0f,1.0f,0.0f,0.113259f,0.986756f,0.116122f,0.5f,0.0f,
  1.0014f,1.00311f,-1.00311f,0.113259f,0.986756f,0.116122f,1.0f,0.0f,
  1.8999e-07f,1.26346f,-1.26346f,0.113259f,0.986756f,0.116122f,1.0f,0.5f,
  2.38419e-07f,1.0f,0.0f,0.113259f,0.986756f,0.116122f,0.5f,0.5f,
  -1.0f,2.98023e-07f,-1.0f,-0.956466f,0.206366f,-0.206365f,0.0f,0.5f,
  -1.43425f,2.38419e-07f,0.0f,-0.956466f,0.206366f,-0.206365f,0.5f,0.5f,
  -1.0f,1.0f,0.0f,-0.956466f,0.206366f,-0.206365f,0.5f,1.0f,
  -1.0014f,1.00311f,-1.00311f,-0.956466f,0.206366f,-0.206365f,0.0f,1.0f,
  -1.0014f,-1.00311f,-1.00311f,-0.956466f,-0.206365f,-0.206365f,0.0f,0.0f,
  -1.0f,-1.0f,0.0f,-0.956466f,-0.206365f,-0.206365f,0.5f,0.0f,
  -1.43425f,2.38419e-07f,0.0f,-0.956466f,-0.206365f,-0.206365f,0.5f,0.5f,
  -1.0f,2.98023e-07f,-1.0f,-0.956466f,-0.206365f,-0.206365f,0.0f,0.5f,
  -1.0f,-1.0f,0.0f,-0.956466f,-0.206365f,0.206365f,0.5f,0.0f,
  -1.0014f,-1.00311f,1.00311f,-0.956466f,-0.206365f,0.206365f,1.0f,0.0f,
  -1.0f,1.78814e-07f,1.0f,-0.956466f,-0.206365f,0.206365f,1.0f,0.5f,
  -1.43425f,2.38419e-07f,0.0f,-0.956466f,-0.206365f,0.206365f,0.5f,0.5f,
  0.0f,-1.26346f,-1.26346f,-0.113259f,-0.986757f,0.116121f,0.0f,0.5f,
  -2.98023e-07f,-1.0f,0.0f,-0.113259f,-0.986757f,0.116121f,0.5f,0.5f,
  -1.0f,-1.0f,0.0f,-0.113259f,-0.986757f,0.116121f,0.5f,1.0f,
  -1.0014f,-1.00311f,-1.00311f,-0.113259f,-0.986757f,0.116121f,0.0f,1.0f,
  1.0014f,-1.00311f,-1.00311f,0.113259f,-0.986757f,0.116121f,0.0f,0.0f,
  1.0f,-1.0f,0.0f,0.113259f,-0.986757f,0.116121f,0.5f,0.0f,
  -2.98023e-07f,-1.0f,0.0f,0.113259f,-0.986757f,0.116121f,0.5f,0.5f,
  0.0f,-1.26346f,-1.26346f,0.113259f,-0.986757f,0.116121f,0.0f,0.5f,
  1.0f,-1.0f,0.0f,0.113258f,-0.986756f,-0.116122f,0.5f,0.0f,
  1.0014f,-1.00311f,1.00311f,0.113258f,-0.986756f,-0.116122f,1.0f,0.0f,
  -5.66244e-07f,-1.26346f,1.26346f,0.113258f,-0.986756f,-0.116122f,1.0f,0.5f,
  -2.98023e-07f,-1.0f,0.0f,0.113258f,-0.986756f,-0.116122f,0.5f,0.5f,
  1.0f,-5.96046e-08f,-1.0f,0.956466f,-0.206366f,-0.206365f,0.0f,0.5f,
  1.43425f,-2.98023e-07f,0.0f,0.956466f,-0.206366f,-0.206365f,0.5f,0.5f,
  1.0f,-1.0f,0.0f,0.956466f,-0.206366f,-0.206365f,0.5f,1.0f,
  1.0014f,-1.00311f,-1.00311f,0.956466f,-0.206366f,-0.206365f,0.0f,1.0f,
  1.0014f,1.00311f,-1.00311f,0.956466f,0.206365f,-0.206365f,0.0f,0.0f,
  1.0f,1.0f,0.0f,0.956466f,0.206365f,-0.206365f,0.5f,0.0f,
  1.43425f,-2.98023e-07f,0.0f,0.956466f,0.206365f,-0.206365f,0.5f,0.5f,
  1.0f,-5.96046e-08f,-1.0f,0.956466f,0.206365f,-0.206365f,0.0f,0.5f,
  1.0f,1.0f,0.0f,0.956466f,0.206365f,0.206365f,0.5f,0.0f,
  1.0014f,1.00311f,1.00311f,0.956466f,0.206365f,0.206365f,1.0f,0.0f,
  1.0f,-5.36442e-07f,1.0f,0.956466f,0.206365f,0.206365f,1.0f,0.5f,
  1.43425f,-2.98023e-07f,0.0f,0.956466f,0.206365f,0.206365f,0.5f,0.5f,
  1.0f,-5.36442e-07f,1.0f,0.113259f,0.116121f,0.986756f,0.0f,0.5f,
  -1.49012e-07f,-1.78814e-07f,1.0f,0.113259f,0.116121f,0.986756f,0.5f,0.5f,
  -5.66244e-07f,-1.26346f,1.26346f,0.113259f,0.116121f,0.986756f,0.5f,1.0f,
  1.0014f,-1.00311f,1.00311f,0.113259f,0.116121f,0.986756f,0.0f,1.0f,
  1.0014f,1.00311f,1.00311f,0.113259f,-0.116122f,0.986756f,0.0f,0.0f,
  2.5332e-07f,1.26346f,1.26346f,0.113259f,-0.116122f,0.986756f,0.5f,0.0f,
  -1.49012e-07f,-1.78814e-07f,1.0f,0.113259f,-0.116122f,0.986756f,0.5f,0.5f,
  1.0f,-5.36442e-07f,1.0f,0.113259f,-0.116122f,0.986756f,0.0f,0.5f,
  2.5332e-07f,1.26346f,1.26346f,-0.113259f,-0.116122f,0.986757f,0.5f,0.0f,
  -1.0014f,1.00311f,1.00311f,-0.113259f,-0.116122f,0.986757f,1.0f,0.0f,
  -1.0f,1.78814e-07f,1.0f,-0.113259f,-0.116122f,0.986757f,1.0f,0.5f,
  -1.49012e-07f,-1.78814e-07f,1.0f,-0.113259f,-0.116122f,0.986757f,0.5f,0.5f,
  1.8999e-07f,1.26346f,-1.26346f,-0.113259f,-0.116122f,-0.986756f,0.0f,0.5f,
  5.96046e-08f,1.19209e-07f,-1.0f,-0.113259f,-0.116122f,-0.986756f,0.5f,0.5f,
  -1.0f,2.98023e-07f,-1.0f,-0.113259f,-0.116122f,-0.986756f,0.5f,1.0f,
  -1.0014f,1.00311f,-1.00311f,-0.113259f,-0.116122f,-0.986756f,0.0f,1.0f,
  1.0014f,1.00311f,-1.00311f,0.113259f,-0.116122f,-0.986756f,0.0f,0.0f,
  1.0f,-5.96046e-08f,-1.0f,0.113259f,-0.116122f,-0.986756f,0.5f,0.0f,
  5.96046e-08f,1.19209e-07f,-1.0f,0.113259f,-0.116122f,-0.986756f,0.5f,0.5f,
  1.8999e-07f,1.26346f,-1.26346f,0.113259f,-0.116122f,-0.986756f,0.0f,0.5f,
  1.0f,-5.96046e-08f,-1.0f,0.113259f,0.116122f,-0.986756f,0.5f,0.0f,
  1.0014f,-1.00311f,-1.00311f,0.113259f,0.116122f,-0.986756f,1.0f,0.0f,
  0.0f,-1.26346f,-1.26346f,0.113259f,0.116122f,-0.986756f,1.0f,0.5f,
  5.96046e-08f,1.19209e-07f,-1.0f,0.113259f,0.116122f,-0.986756f,0.5f,0.5f,
}; // end cubeVertices

static const unsigned indices[] = {
  0, 1, 2,
  0, 2, 3,
  4, 5, 6,
  4, 6, 7,
  8, 9, 10,
  8, 10, 11,
  12, 13, 14,
  12, 14, 15,
  16, 17, 18,
  16, 18, 19,
  20, 21, 22,
  20, 22, 23,
  24, 25, 26,
  24, 26, 27,
  28, 29, 30,
  28, 30, 31,
  32, 33, 34,
  32, 34, 35,
  36, 37, 38,
  36, 38, 39,
  40, 41, 42,
  40, 42, 43,
  44, 45, 46,
  44, 46, 47,
  48, 49, 50,
  48, 50, 51,
  52, 53, 54,
  52, 54, 55,
  56, 57, 58,
  56, 58, 59,
  60, 61, 62,
  60, 62, 63,
  64, 65, 66,
  64, 66, 67,
  68, 69, 70,
  68, 70, 71,
  72, 73, 74,
  72, 74, 75,
  76, 77, 78,
  76, 78, 79,
  80, 81, 82,
  80, 82, 83,
  84, 85, 86,
  84, 86, 87,
  88, 89, 90,
  88, 90, 91,
  92, 93, 94,
  92, 94, 95,
}; // end cubeTriangles