#pragma once

#include <string>

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Posledni jeskyne"

struct window_info {

	std::string name;
	int width, height;
	int position_x, position_y;
	bool is_reshapable;

	window_info() {
		name = WINDOW_TITLE;
		width = WINDOW_WIDTH; 
		height = WINDOW_HEIGHT;
		position_x = 100;
		position_y = 100;
		is_reshapable = true;
	}

	window_info(std::string name, int start_position_x, int start_position_y, int width, int height, bool is_reshapable) {

		this->name = name;
		this->position_x = start_position_x;
		this->position_y = start_position_y;

		this->width = width;
		this->height = height;
		this->is_reshapable = is_reshapable;
	}

	//copy constructor
	window_info(const window_info& windowInfo) {
		name = windowInfo.name;
		position_x = windowInfo.position_x;
		position_y = windowInfo.position_y;

		width = windowInfo.width;
		height = windowInfo.height;
		is_reshapable = windowInfo.is_reshapable;
	}

	void operator=(const window_info& windowInfo) {

		name = windowInfo.name;

		position_x = windowInfo.position_x;
		position_y = windowInfo.position_y;

		width = windowInfo.width;
		height = windowInfo.height;
		is_reshapable = windowInfo.is_reshapable;
	}

};