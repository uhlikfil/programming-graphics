#pragma once

#include "model.h"
#include "pgr.h"


class skybox : public model {
public:
	skybox(const shader_struct& shader_s);
	virtual void create() override final;
	virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
private:
	GLuint texture2;
};