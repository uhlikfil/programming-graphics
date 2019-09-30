#include "scene_manager.h"


scene_manager::scene_manager() {
	glEnable(GL_DEPTH_TEST);
	glClearStencil(0);  // this is the default value
	srand((unsigned int)time(NULL));

	// load shaders
	shader_m = new shader_manager();
	shader_m->create_shader("light_shader", "light_vert_shader.glsl", "light_frag_shader.glsl");
	shader_m->create_shader("skybox_shader", "skybox_vert_shader.glsl", "skybox_frag_shader.glsl");
	shader_m->create_shader("animated_shader", "animated_vert_shader.glsl", "animated_frag_shader.glsl");
	shader_m->create_shader("fire_shader", "fire_vert_shader.glsl", "fire_frag_shader.glsl");

	cam = new camera();

	model_m = new model_manager();

	day_length = INIT_DAY_LENGTH;
}

scene_manager::~scene_manager() {
	delete shader_m;
	delete cam;
	delete model_m;
}

void scene_manager::notify_update() {
	model_m->update_models();
	if (cam->is_following()) {
		cam->follow();
	}
}

void scene_manager::notify_display_frame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(0.4f, 0.6f, 0.9f, 1.0f);

	const shader_struct& light_shader = shader_manager::get_shader("light_shader");
	const shader_struct& skybox_shader = shader_manager::get_shader("skybox_shader");
	float time = glutGet(GLUT_ELAPSED_TIME);
	ufo* reflector = (ufo*)model_m->get_model(3);
	campfire* camp_fire = (campfire*)model_m->get_model(2);

	glUseProgram(light_shader.program);
	glUniform3fv(light_shader.reflector_position_loc, 1, glm::value_ptr(reflector->get_position()));
	glUniform3fv(light_shader.reflector_direction_loc, 1, glm::value_ptr(glm::vec3(0.0f, -1.0f, 0.0f)));
	glUniform3fv(light_shader.reflector_ambient_loc, 1, glm::value_ptr(reflector->get_light_color()));
	glUniform1f(light_shader.reflector_cut_off_loc, 12.5f);
	glUniform1f(light_shader.reflector_outer_cut_off_loc, 0.9f);
	glUniform1i(light_shader.campfire_burning_loc, camp_fire->get_burning());
	glUniform1f(light_shader.t_loc, time);
	glUniform1f(light_shader.day_length_loc, day_length);
	glUseProgram(0);

	glUseProgram(skybox_shader.program);
	glUniform1f(skybox_shader.t_loc, time);
	glUniform1f(skybox_shader.day_length_loc, day_length);
	glUseProgram(0);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	CHECK_GL_ERROR();

	model_m->draw_models(cam->get_projection_matrix(), cam->get_view_matrix());
	glDisable(GL_STENCIL_TEST);
}

void scene_manager::notify_reshape(int w, int h, int prev_w, int prev_h) {
	cam->on_resize(w, h);
}

void scene_manager::notify_key_pressed(unsigned char key_pressed) {
	switch (key_pressed) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 49:
		cam->set_fixed_view(glm::vec3(-1.4f, 0.1f, -1.7f), glm::vec3(0.0f, 0.2f, 1.4f));
		break;
	case 50:
		cam->set_fixed_view(glm::vec3(13.8f, 26.0f, 41.7f), glm::vec3(-0.5f, -0.8f, -1.3f));
		break;
	case 51:
		cam->set_fixed_view(glm::vec3(-64.3f, 0.1f, 64.4f), glm::vec3(1.1f, 0.1f, -1.1f));
		break;
	case 'c':
		cam->set_free();
		break;
	case 'm':
		day_length += ONE_SEC;
		break;
	case 'n':
		if (day_length > ONE_SEC) {
			day_length -= ONE_SEC;
		}
		break;
	case 'w':
		key_map[KEY_W] = true;
		break;
	case 's':
		key_map[KEY_S] = true;
		break;
	case 'a':
		key_map[KEY_A] = true;
		break;
	case 'd':
		key_map[KEY_D] = true;
		break;
	case ' ':
		key_map[KEY_SPACE] = true;
		break;
	case 'x':
		key_map[KEY_X] = true;
		break;
	}
}

void scene_manager::notify_key_released(unsigned char key_released) {
	switch (key_released) {
	case 'w':
		//std::cout << "w released\n";
		key_map[KEY_W] = false;
		break;
	case 's':
		//std::cout << "s released\n";
		key_map[KEY_S] = false;
		break;
	case 'a':
		//std::cout << "a released\n";
		key_map[KEY_A] = false;
		break;
	case 'd':
		//std::cout << "d released\n";
		key_map[KEY_D] = false;
		break;
	case ' ':
		//std::cout << "space released\n";
		key_map[KEY_SPACE] = false;
		break;
	case 'x':
		//std::cout << "x released\n";
		key_map[KEY_X] = false;
		break;
	}
}

void scene_manager::notify_special_key_pressed(int special_key_pressed) {
	switch (special_key_pressed) {
	case GLUT_KEY_UP:
		key_map[KEY_UP_ARR] = true;
		break;
	case GLUT_KEY_DOWN:
		key_map[KEY_DOWN_ARR] = true;
		break;
	case GLUT_KEY_LEFT:
		key_map[KEY_LEFT_ARR] = true;
		break;
	case GLUT_KEY_RIGHT:
		key_map[KEY_RIGHT_ARR] = true;
		break;
	case GLUT_KEY_F1:
		cam->set_fixed_view(glm::vec3(-1.4f, 0.1f, -1.7f), glm::vec3(0.0f, 0.2f, 1.4f));
		break;
	case GLUT_KEY_F2:
		cam->set_fixed_view(glm::vec3(13.8f, 26.0f, 41.7f), glm::vec3(-0.5f, -0.8f, -1.3f));
		break;
	case GLUT_KEY_F3:
		cam->set_fixed_view(glm::vec3(-64.3f, 0.1f, 64.4f), glm::vec3(1.1f, 0.1f, -1.1f));
		break;
	}
}

void scene_manager::notify_special_key_released(int special_key_released) {
	switch (special_key_released) {
	case GLUT_KEY_UP:
		key_map[KEY_UP_ARR] = false;
		break;
	case GLUT_KEY_DOWN:
		key_map[KEY_DOWN_ARR] = false;
		break;
	case GLUT_KEY_LEFT:
		key_map[KEY_LEFT_ARR] = false;
		break;
	case GLUT_KEY_RIGHT:
		key_map[KEY_RIGHT_ARR] = false;
		break;
	}
}

void scene_manager::notify_object_interaction(int object_id) {
	printf("Clicked on object with ID: %d\n", (int)object_id);
	if (object_id == 2) {
		campfire* camp_fire = (campfire*)model_m->get_model(object_id);
		camp_fire->change_burning();
	} else if (object_id == 3) {
		ufo* ufoo = (ufo*)model_m->get_model(object_id);
		ufoo->change_light_color();
	} else if (object_id > 46) {
		bird* followed_bird = (bird*)model_m->get_model(object_id);
		cam->set_followed_object(followed_bird);
	}
}

void scene_manager::notify_right_click() {
	glm::vec3 new_bird_pos = cam->get_position() + cam->get_direction() * 10.0f;
	model_m->create_bird(new_bird_pos, glm::vec3(0.0f, 0.0f, 1.0f));
}

void scene_manager::process_keyboard_input() {
		if (key_map[KEY_W] || key_map[KEY_UP_ARR]) {
			cam->move_forward();
		}
		if (key_map[KEY_S] || key_map[KEY_DOWN_ARR]) {
			cam->move_backwards();
		}
		if (key_map[KEY_A] || key_map[KEY_LEFT_ARR]) {
			cam->move_left();
		}
		if (key_map[KEY_D] || key_map[KEY_RIGHT_ARR]) {
			cam->move_right();
		}
		if (key_map[KEY_SPACE]) {
			cam->move_up();
		}
		if (key_map[KEY_X]) {
			cam->move_down();
		}
}

void scene_manager::process_mouse_movement(int mouse_x, int mouse_y) {
	cam->horizontal_rotation(mouse_x);
	cam->vertial_rotation(mouse_y);
}