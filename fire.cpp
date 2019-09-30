#include "fire.h"

fire::fire(const shader_struct& shader_s, const std::string & path, const glm::vec3 & position, const glm::vec3 & direction, const float & size) : model(shader_s) {
	texture = pgr::createTexture(path);
	this->position = position;
	this->direction = direction;
	this->size = size;
}

void fire::create() {
	start_time = glutGet(GLUT_ELAPSED_TIME);
	num_of_triangles = fire_num_of_quad_vertices;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fire_vertex_data), fire_vertex_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(shader_s.position_loc);
	glVertexAttribPointer(shader_s.position_loc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(shader_s.texture_coord_loc);
	glVertexAttribPointer(shader_s.texture_coord_loc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);

}

void fire::draw(const glm::mat4 & projection_matrix, const glm::mat4 & view_matrix) {
	glUseProgram(shader_s.program);

	set_up_model_matrix(view_matrix);
	set_transformation_uniforms(projection_matrix, view_matrix, model_matrix);
	glUniform1f(shader_s.t_loc, glutGet(GLUT_ELAPSED_TIME) - start_time);
	glUniform1i(shader_s.tex_sampler_loc, 0);

	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, num_of_triangles);

	glBindVertexArray(0);
	glUseProgram(0);
}

void fire::update() {
	model::update();
}

void fire::set_up_model_matrix(const glm::mat4& view_matrix) {
	glm::mat4 billboard_rotation_matrix = glm::mat4(
		view_matrix[0],
		view_matrix[1],
		view_matrix[2],
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);
	// inverse view rotation
	billboard_rotation_matrix = glm::transpose(billboard_rotation_matrix);

	model_matrix = glm::translate(glm::mat4(1.0f), position);
	model_matrix = glm::scale(model_matrix, glm::vec3(size));
	model_matrix = model_matrix * billboard_rotation_matrix;
}
