#include "camera.h"
#include <iostream>

camera::camera() : 
	perspective_matrix(calculate_perspective((float) GLUT_WINDOW_WIDTH, (float) GLUT_WINDOW_HEIGHT)),
	cam_position(INITIAL_CAM_POSITION), 
	cam_direction(INITIAL_CAM_DIRECTION),
	cam_up(glm::vec3(0.0f, 1.0f, 0.0f)) {}

camera::~camera() {}

glm::mat4 camera::get_projection_matrix() const {
	return perspective_matrix;
}

glm::mat4 camera::get_view_matrix() const {
	return glm::lookAt(cam_position, cam_position + cam_direction, cam_up);
}

glm::vec3 camera::get_position() {
	return cam_position;
}

glm::vec3 camera::get_direction() {
	return cam_direction;
}

glm::mat4 camera::calculate_perspective(int width, int height) const {
	return glm::perspective(FOV, (float) width / (float) height, Z_NEAR, Z_FAR);
}

void camera::move(glm::vec3 & step) {
	if (free_movement) {
		glm::vec3 next_position = cam_position + step;
		
		if (check_collision(next_position)) {
			step = glm::vec3(0.0f);
		}
		if (next_position.y < 0.0f || next_position.y > SCENE_HEIGHT) {
			step.y = 0;
		}
		if (abs(next_position.x) > SCENE_WIDTH) {
			step.x = 0;
		}
		if (abs(next_position.z) > SCENE_WIDTH) {
			step.z = 0;
		}
		cam_position += step;
	}
}

bool camera::check_collision(glm::vec3& position) {
	glm::vec3 collision_object_position = glm::vec3(-20.0f, 5.0f, 10.0f);
	return glm::dot(position - collision_object_position, position - collision_object_position) <= (25.0f);
}

void camera::move_forward() {
	glm::vec3 step = MOVEMENT_SPEED * cam_direction;
	move(step);
}

void camera::move_backwards() {
	glm::vec3 step = MOVEMENT_SPEED * -cam_direction;
	move(step);

}

void camera::move_left() {
	glm::vec3 strafe_direction = glm::normalize(glm::cross(cam_direction, cam_up));
	glm::vec3 step = MOVEMENT_SPEED * -strafe_direction;
	move(step);

}

void camera::move_right() {
	glm::vec3 strafe_direction = glm::normalize(glm::cross(cam_direction, cam_up));
	glm::vec3 step = MOVEMENT_SPEED * strafe_direction;
	move(step);
}

void camera::move_up() {
	glm::vec3 step = MOVEMENT_SPEED * cam_up;
	move(step);
}

void camera::move_down() {
	glm::vec3 step = MOVEMENT_SPEED * -cam_up;
	move(step);
	/*
	std::cout << "pos x " << cam_position.x << "\n";
	std::cout << "pos y " << cam_position.y << "\n";
	std::cout << "pos z " << cam_position.z << "\n";
	std::cout << "dir x " << cam_direction.x << "\n";
	std::cout << "dir y " << cam_direction.y << "\n";
	std::cout << "dir z " << cam_direction.z << "\n\n";
	*/
}

void camera::horizontal_rotation(int x) {
	if (free_rotation) {
		cam_direction = glm::mat3(glm::rotate(glm::mat4(1.0f), x * MOUSE_SPEED, cam_up)) * cam_direction;
	}
}

void camera::vertial_rotation(int y) {
	if (free_rotation) {
		glm::vec3 to_rotate_around = glm::cross(cam_direction, cam_up);
		cam_direction = glm::mat3(glm::rotate(glm::mat4(1.0f), y * MOUSE_SPEED, to_rotate_around)) * cam_direction;
	}
}

void camera::set_free() {
	free_movement = true;
	free_rotation = true;
	following = false;
	followed_object = nullptr;
}

void camera::set_fixed_view(glm::vec3 position, glm::vec3 direction) {
	free_movement = false;
	free_rotation = false;

	cam_position = position;
	cam_direction = direction;
}

void camera::set_followed_object(model * object) {
	followed_object = object;
	following = true;
	free_movement = false;
}

bool camera::is_following() {
	return following;
}

void camera::follow() {
	cam_position = followed_object->get_position() + cam_up;
}

void camera::on_resize(int width, int height) {
	perspective_matrix = calculate_perspective(width, height);
}
