#pragma once

#include "loaded_model.h"
#include "fire.h"


class campfire : public loaded_model {
public:
	campfire(const shader_struct& shader_s, const std::string& path, const glm::vec3& position, const glm::vec3& direction, const float& size);

	virtual void create() override;
	virtual void draw(const glm::mat4 & projection_matrix, const glm::mat4 & view_matrix) override;
	virtual void update() override;
	virtual void destroy() override;

	void change_burning();
	bool& get_burning();
private:
	fire* flame;
	bool is_burning;
};