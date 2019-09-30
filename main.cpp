#include "pgr.h"
#include "init_glut.h"
#include <iostream>
#include "scene_manager.h"


int main(int argc, char** argv) {

	// window
	window_info window;
	frame_buffer_info fbi(true, true, true, true);
	init_glut::init(window, fbi);
	
	// managers
	scene_manager* scene = new scene_manager();
	init_glut::set_managers(scene);


	init_glut::run();

	delete scene;
	return 0;
}