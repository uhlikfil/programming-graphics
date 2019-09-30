#include "happy_cube.h"

happy_cube::happy_cube(const shader_struct & shader_s, const glm::vec3 & position, const glm::vec3 & direction, const float & size) : loaded_model(shader_s, "x", position, direction, size) {
}

void happy_cube::create() {
	glUseProgram(shader_s.program);
	num_of_triangles = 48;

	int num_of_vertices = 96;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 8 * num_of_vertices * sizeof(float), &vertices[0], GL_STATIC_DRAW); // store vertices, normals, texture coords

	diffuse = glm::vec3(1.0f);
	specular = glm::vec3(1.0f);
	ambient = glm::vec3(1.0f);
	shininess = 10.0f;

	std::string texture_name = "data/objects/happy_cube.png";
	texture = pgr::createTexture(texture_name);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * num_of_triangles * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(shader_s.position_loc);
	glVertexAttribPointer(shader_s.position_loc, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(shader_s.normal_loc);
	glVertexAttribPointer(shader_s.normal_loc, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(shader_s.texture_coord_loc);
	glVertexAttribPointer(shader_s.texture_coord_loc, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	CHECK_GL_ERROR();
	glBindVertexArray(0);
	glUseProgram(0);
}

void happy_cube::set_material_uniforms(const glm::vec3 & ambient, const glm::vec3 & diffuse, const glm::vec3 & specular, float shininess, GLuint texture) {
	loaded_model::set_material_uniforms(ambient, diffuse, specular, shininess, texture);
	glUniform1i(shader_s.rotate_texture_loc, 1);
}
