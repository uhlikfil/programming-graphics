#pragma once

#include "loaded_model.h"
#include "flight_assistant.h"


static constexpr float ufo_speed = 0.0001f;
static constexpr size_t  ufo_curve_size = 15;
static glm::vec3 ufo_route[] = {
	glm::vec3(-15.0f, 0.0f,  15.0f),
	glm::vec3(-33.0f, 0.0f, 33.0f),
	glm::vec3(-66.0f, 0.0f, 33.0f),
	glm::vec3(-66.0f, 0.0f, -15.0f),
	glm::vec3(-15.0f, 0.0f, -15.0f),
	glm::vec3(-33.0f, 0.0f, -33.0f),
	glm::vec3(-15.0f,  0.0f, -66.0f),
	glm::vec3(33.0f, 0.0f, -66.0f),
	glm::vec3(33.0f, 0.0f, -15.0f),
	glm::vec3(66.0f,  0.0f, -33.0f),
	glm::vec3(66.0f, 0.0f, 0.0f),
	glm::vec3(66.0f, 0.0f, 33.0f),
	glm::vec3(15.0f, 0.0f, 33.0f),
	glm::vec3(33.0f, 0.0f, 66.0f),
	glm::vec3(0.0f, 0.0f, 15.0f),
};

class ufo : public loaded_model {
public:
	ufo(const shader_struct& shader_s, const std::string& path, const glm::vec3& position, const glm::vec3& direction, const float& size);

	virtual void update() override final;
	void change_light_color();

	glm::vec3 get_light_color();
	
private:
	glm::vec3 start_position;
	glm::vec3 light_color;
};