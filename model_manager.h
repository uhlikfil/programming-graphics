#pragma once

#include <map>
#include "shader_manager.h"
#include "loaded_model.h"
#include "campfire.h"
#include "skybox.h"
#include "bird.h"
#include "ufo.h"
#include "happy_cube.h"

class model_manager {
public:
	model_manager();
	~model_manager();

	void draw_models(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
	void update_models();
	const model* get_model(const int& position) const;

	void generate_trees();
	void create_tree(const glm::vec3& position, const glm::vec3& direction, const float& size);
	void create_bird(const glm::vec3& position, const glm::vec3& direction);
private:
	std::vector<model*> model_list;
	unsigned int num_of_objects = 0;
};