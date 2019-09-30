#include "model.h"


model::model(const shader_struct& shader_s) : shader_s(shader_s){}

model::~model() {
	destroy();
}

void model::create() {}

void model::draw(const glm::mat4 & projection_matrix, const glm::mat4 & view_matrix) {
}

void model::update() {
	set_up_model_matrix();
}

void model::destroy() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
}

glm::vec3 model::get_position() const {
	return position;
}

void model::set_transformation_uniforms(const glm::mat4 & projection_matrix, const glm::mat4 & view_matrix, const glm::mat4 & model_matrix) {
	glm::mat4 PVM = projection_matrix * view_matrix * model_matrix;
	glUniformMatrix4fv(shader_s.pvm_matrix_loc, 1, GL_FALSE, glm::value_ptr(PVM));

	glUniformMatrix4fv(shader_s.v_matrix_loc, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(shader_s.m_matrix_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));
	const glm::mat4 model_rotation_matrix = glm::mat4(
		model_matrix[0],
		model_matrix[1],
		model_matrix[2],
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);
	glm::mat4 normal_matrix = glm::transpose(glm::inverse(model_rotation_matrix));
	glUniformMatrix4fv(shader_s.normal_matrix_loc, 1, GL_FALSE, glm::value_ptr(normal_matrix));  // correct matrix for non-rigid transform
}

void model::set_up_model_matrix() {
	glm::vec3 z = glm::normalize(direction);

	glm::vec3 x = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), z));

	glm::vec3 y = glm::cross(z, x);

	glm::mat4 translation_translation = glm::mat4(glm::vec4(x.x, x.y, x.z, 0.0), 
										glm::vec4(y.x, y.y, y.z, 0.0),
										glm::vec4(z.x, z.y, z.z, 0.0),
										glm::vec4(position.x, position.y, position.z, 1.0));

	model_matrix = glm::scale(translation_translation, glm::vec3(size));
}
