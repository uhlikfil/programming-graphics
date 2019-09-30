#pragma once

#include <iostream>
#include "pgr.h"
#include "window_info.h"
#include "frame_buffer_info.h"
#include "scene_manager.h"


class init_glut {

public:
	static void init(const window_info& window, const frame_buffer_info& frame_buffer_info);

	static void run();
	static void close();

	static void set_managers(scene_manager*& scn_m);

private:
	static scene_manager* scene_m;
	static window_info window_information;

	static void display_callback();
	static void reshape_callback(int width, int height);
	static void close_callback();
	static void keyboard_callback(unsigned char key_pressed, int mouse_x, int mouse_y);
	static void keyboard_up_callback(unsigned char key_pressed, int mouse_x, int mouse_y);
	static void special_keyboard_callback(int special_key_pressed, int mouse_x, int mouse_y);
	static void special_keyboard_up_callback(int special_key_released, int mouse_x, int mouse_y);
	static void mouse_move_callback(int mouse_x, int mouse_y);
	static void mouse_callback(int button_pressed, int button_state, int mouse_x, int mouse_y);
	static void timer_callback(int);
};