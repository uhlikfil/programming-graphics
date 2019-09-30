#include "init_glut.h"


scene_manager* init_glut::scene_m = NULL;
window_info init_glut::window_information;

constexpr int refresh_time_ms = 16;

void init_glut::init(const window_info & window, const frame_buffer_info & frame_buffer_info) {

	// fake arguments
	int fakeargc = 1;
	char *fakeargv[] = { "fake", NULL };

	window_information = window;

	glutInit(&fakeargc, fakeargv);

	// context
	glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	// frame buffer and window
	glutInitDisplayMode(frame_buffer_info.flags);
	glutInitWindowPosition(window.position_x, window.position_y);
	glutInitWindowSize(window.width, window.height);

	glutCreateWindow(window.name.c_str());

	// callbacks
	glutIdleFunc(display_callback);
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutKeyboardFunc(keyboard_callback);
	glutKeyboardUpFunc(keyboard_up_callback);
	glutSpecialFunc(special_keyboard_callback);
	glutSpecialUpFunc(special_keyboard_up_callback);
	glutPassiveMotionFunc(mouse_move_callback);
	glutMouseFunc(mouse_callback);
	glutCloseFunc(close_callback);
	glutTimerFunc(refresh_time_ms, timer_callback, 0);

	if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR)) {
		pgr::dieWithError("oops");
	}

	// clean up
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}

void init_glut::run() {
	std::cout << "GLUT:\t Start Running " << std::endl;
	glutMainLoop();
}

void init_glut::close() {
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void init_glut::set_managers(scene_manager *& scn_m) {
	scene_m = scn_m;
}

void init_glut::display_callback() {
	// check for NULL
	if (scene_m) {
		scene_m->notify_display_frame();

		glutSwapBuffers();
	}
}

void init_glut::reshape_callback(int width, int height) {
	if (window_information.is_reshapable) {
		if (scene_m) {
			scene_m->notify_reshape(width, height, window_information.width, window_information.height);
		}
		window_information.width = width;
		window_information.height = height;
	}
}

void init_glut::keyboard_callback(unsigned char key_pressed, int mouse_x, int mouse_y) {
	if (scene_m) {
		scene_m->notify_key_pressed(key_pressed);
	}
}

void init_glut::keyboard_up_callback(unsigned char key_released, int mouse_x, int mouse_y) {
	if (scene_m) {
		scene_m->notify_key_released(key_released);
	}
}

void init_glut::special_keyboard_callback(int special_key_pressed, int mouse_x, int mouse_y) {
	if (scene_m) {
		scene_m->notify_special_key_pressed(special_key_pressed);
	}
}

void init_glut::special_keyboard_up_callback(int special_key_released, int mouse_x, int mouse_y) {
	if (scene_m) {
		scene_m->notify_special_key_released(special_key_released);
	}
}

void init_glut::mouse_move_callback(int mouse_x, int mouse_y) {
	float delta_x = window_information.width / 2.0f - mouse_x;
	float delta_y = window_information.height / 2.0f - mouse_y;

	if (scene_m) {
		scene_m->process_mouse_movement(delta_x, delta_y);
	}
	glutWarpPointer(window_information.width / 2.0f, window_information.height / 2.0f); // centers cursor
}

void init_glut::mouse_callback(int button_pressed, int button_state, int mouse_x, int mouse_y) {
	if (button_pressed == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN) {
		// stores value from the stencil buffer (byte)
		unsigned char object_id = 0;
		// read value from the stencil buffer for one pixel under the mouse cursor into object_id variable
		// recalculate y, as glut has origin in upper left corner
		glReadPixels(mouse_x, WINDOW_HEIGHT - mouse_y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &object_id);
		// ========  END OF SOLUTION - TASK 6_3-3  ======== //
		glDisable(GL_STENCIL_TEST);
		// the buffer was initially cleared to zeros
		scene_m->notify_object_interaction(object_id);
	}
	if (button_pressed == GLUT_RIGHT_BUTTON && button_state == GLUT_DOWN) {
		scene_m->notify_right_click();
	}
}

void init_glut::timer_callback(int) {
	if (scene_m) {
		scene_m->process_keyboard_input();
		scene_m->notify_update();
	}

	glutTimerFunc(refresh_time_ms, timer_callback, 0);
}

void init_glut::close_callback() {
	close();
}