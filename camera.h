#pragma once

#include "pgr.h"
#include "model.h"

#define INITIAL_CAM_POSITION glm::vec3(0.0f, 10.0f, 10.0f)
#define INITIAL_CAM_DIRECTION glm::vec3(0.0f, -1.0f, -1.0f)
#define FOV 70.0f
#define Z_NEAR 0.01f
#define Z_FAR 2000.0f

#define MOVEMENT_SPEED 0.3f
#define MOUSE_SPEED 0.002f

#define SCENE_HEIGHT 50.0f
#define SCENE_WIDTH 80.0f

class camera {
public:
	camera();
	~camera();

	glm::mat4 get_projection_matrix() const;
	glm::mat4 get_view_matrix() const;
	glm::vec3 get_position();
	glm::vec3 get_direction();
	void on_resize(int width, int height);

	void move_forward();
	void move_backwards();
	void move_left();
	void move_right();
	void move_up();
	void move_down();
	void horizontal_rotation(int x);
	void vertial_rotation(int y);

	void set_free();
	void set_fixed_view(glm::vec3 position, glm::vec3 direction);
	void set_followed_object(model* object);
	bool is_following();
	void follow();

private:
	bool free_movement = true;
	bool free_rotation = true;
	bool following = false;
	int prev_mouse_x;
	int prev_mouse_y;

	glm::mat4 perspective_matrix;
	glm::vec3 cam_position;
	glm::vec3 cam_direction;
	glm::vec3 cam_up;

	model* followed_object;

	glm::mat4 calculate_perspective(int width, int height) const;
	void move(glm::vec3& step);
	bool check_collision(glm::vec3& position);
};