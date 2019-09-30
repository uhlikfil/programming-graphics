#pragma once

#include "shader_manager.h"
#include "model_manager.h"
#include "camera.h"
#include <time.h>


#define INIT_DAY_LENGTH 24000.0f
#define ONE_SEC 1000.0f
enum { KEY_W, KEY_S, KEY_A, KEY_D, KEY_SPACE, KEY_X, KEY_UP_ARR, KEY_DOWN_ARR, KEY_LEFT_ARR, KEY_RIGHT_ARR, KEY_COUNT };


class scene_manager {
public:
	scene_manager();
	~scene_manager();

	void notify_update();
	void notify_display_frame();
	void notify_reshape(int w, int h, int prev_w, int prev_h);

	void notify_key_pressed(unsigned char key_pressed);
	void notify_key_released(unsigned char key_released);
	void notify_special_key_pressed(int special_key_pressed);
	void notify_special_key_released(int special_key_released);
	void notify_object_interaction(int object_id);
	void notify_right_click();

	void process_keyboard_input();
	void process_mouse_movement(int mouse_x, int mouse_y);
private:
	shader_manager* shader_m;
	model_manager* model_m;
	camera* cam;
	float day_length;

	bool key_map[KEY_COUNT] = { false };
};