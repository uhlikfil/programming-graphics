#pragma once

#include "model.h"

static const int fire_num_of_quad_vertices = 4;
static const float fire_vertex_data[fire_num_of_quad_vertices * 5] = {
	// x      y     z     u     v
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
	 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
};

class fire : public model {
public:
	fire(const shader_struct& shader_s, const std::string& path, const glm::vec3& position, const glm::vec3& direction, const float& size);

	virtual void create() override;
	virtual void draw(const glm::mat4 & projection_matrix, const glm::mat4 & view_matrix) override;
	virtual void update() override;
protected:
	virtual void set_up_model_matrix(const glm::mat4& view_matrix);

};