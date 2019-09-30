#pragma once

#include "model.h"
#include "pgr.h"


class loaded_model : public model {
public:
	loaded_model(const shader_struct& shader_s, const std::string& path, const glm::vec3& position, const glm::vec3& direction, const float& size);

	virtual void create() override;
	virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override;

protected:
	std::string obj_path;
	void load_mesh(const std::string &file_name);

	virtual void set_material_uniforms(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, GLuint texture);

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};