#include "campfire.h"


campfire::campfire(const shader_struct& shader_s, const std::string & path, const glm::vec3 & position, const glm::vec3 & direction, const float & size) : loaded_model(shader_s, path, position, direction, size) {
	glm::vec3 flame_position = position;
	flame_position.y += 0.75f;

	flame = new fire(shader_manager::get_shader("fire_shader"), "data/objects/fire.jpg", flame_position, direction, size);
	flame->create();
	
	is_burning = true;
}

void campfire::create() {
	loaded_model::create();
}

void campfire::draw(const glm::mat4 & projection_matrix, const glm::mat4 & view_matrix) {
	loaded_model::draw(projection_matrix, view_matrix);

	if (is_burning) {
		flame->draw(projection_matrix, view_matrix);
	}
}

void campfire::update() {
	loaded_model::update();
}

void campfire::destroy() {
	flame->destroy();
	model::destroy();
}

void campfire::change_burning() {
	if (is_burning) {
		is_burning = false;
	} else {
		is_burning = true;
	}
}

bool& campfire::get_burning() {
	return is_burning;
}
