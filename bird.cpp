#include "bird.h"

bird::bird(const shader_struct& shader_s, const glm::vec3 & position, const glm::vec3 & direction, const float & size) : model(shader_s) {
	this->direction = position;
	this->position = direction;
	this->size = size;
	start_position = position;
}

void bird::create() {
	
	set_up_model_matrix();
	num_of_frames = 11;
	num_of_triangles = sizeof(birds_faces) / (sizeof(unsigned short) * 3);
	num_of_vertices = 315;
	animation_frame_time_ms = 150;
	start_time = glutGet(GLUT_ELAPSED_TIME);
	
	glUseProgram(shader_s.program);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, num_of_frames * num_of_vertices * 3 * sizeof(float), birds_vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_of_triangles * 3 * sizeof(short), birds_faces, GL_STATIC_DRAW);

	glEnableVertexAttribArray(shader_s.position_loc);
	glVertexAttribPointer(shader_s.position_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(shader_s.next_position_loc);
	glVertexAttribPointer(shader_s.next_position_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void bird::draw(const glm::mat4 & projection_matrix, const glm::mat4 & view_matrix) {
	glUseProgram(shader_s.program);

	set_transformation_uniforms(projection_matrix, view_matrix, model_matrix);

	if (animation_param > -1) {
		glUniform1f(shader_s.t_loc, animation_param);
	}

	glBindVertexArray(vao);
	glVertexAttribPointer(shader_s.position_loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(frame * num_of_vertices * 3 * sizeof(float)));
	glVertexAttribPointer(shader_s.next_position_loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(next_frame * num_of_vertices * 3 * sizeof(float)));
	glDrawElements(GL_TRIANGLES, num_of_triangles * 3, GL_UNSIGNED_SHORT, 0);
	
	glBindVertexArray(0);
	glUseProgram(0);

	CHECK_GL_ERROR();
}

void bird::update() {

	int time_passed = glutGet(GLUT_ELAPSED_TIME);
	int e = time_passed % animation_frame_time_ms;
	frame = time_passed / animation_frame_time_ms;
	next_frame = frame + 1;
	frame %= num_of_frames;
	next_frame %= num_of_frames;
	animation_param = float(e) / float(animation_frame_time_ms);

	float curve_param = speed * (time_passed - start_time);

	position = start_position + evaluate_closed_curve(bird_route, curve_size, curve_param);
	direction = glm::normalize(evaluate_closed_curve_1st_derivative(bird_route, curve_size, curve_param));

	model::update();
}
