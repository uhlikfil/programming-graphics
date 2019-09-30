#pragma once

#include "pgr.h"
#include <iostream>
#include <vector>
#include "shader_manager.h"


#define PI 3.14159265f;


class model {
public:
	model(const shader_struct& shader_s);
	virtual ~model();
	virtual void create();
	virtual void draw(const glm::mat4 & projection_matrix, const glm::mat4 & view_matrix);
	virtual void update();
	virtual void destroy();

	virtual glm::vec3 get_position() const;
protected:
	glm::vec3 position, direction;
	float size;

	void set_transformation_uniforms(const glm::mat4& projection_matrix, const glm::mat4& view_matrix, const glm::mat4& model_matrix);
	virtual void set_up_model_matrix();

	glm::mat4 model_matrix;

	const shader_struct& shader_s;
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	GLuint texture;
	unsigned int num_of_triangles;
	float start_time;
};
