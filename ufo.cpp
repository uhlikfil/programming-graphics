#include "ufo.h"

ufo::ufo(const shader_struct& shader_s, const std::string & path, const glm::vec3 & position, const glm::vec3 & direction, const float & size) :loaded_model(shader_s, path, position, direction, size) {
	start_position = position;
	light_color = glm::vec3(0.2f, 0.8f, 0.8f);
}

void ufo::update() {
	int time_passed = glutGet(GLUT_ELAPSED_TIME);

	float curve_param = ufo_speed * (time_passed - start_time);

	position = start_position + evaluate_closed_curve(ufo_route, ufo_curve_size, curve_param);
	direction = glm::normalize(evaluate_closed_curve_1st_derivative(ufo_route, ufo_curve_size, curve_param));

	loaded_model::update();
}

void ufo::change_light_color() {
	light_color = glm::vec3((rand()) / (float)RAND_MAX, (rand()) / (float)RAND_MAX, (rand()) / (float)RAND_MAX);
}

glm::vec3 ufo::get_light_color() {
	return light_color;
}
