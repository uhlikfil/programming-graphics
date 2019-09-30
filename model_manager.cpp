#include "model_manager.h"


model_manager::model_manager() {

	const shader_struct& light_shader = shader_manager::get_shader("light_shader");
	const shader_struct& animated_shader = shader_manager::get_shader("animated_shader");

	model* sky = new skybox(shader_manager::get_shader("skybox_shader"));
	sky->create();
	model_list.push_back(sky);

	model* terr = new loaded_model(light_shader, "data/terrain/terrain.obj", glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 100.0f);
	terr->create();
	model_list.push_back(terr);

	model* camp_fire = new campfire(light_shader, "data/objects/campfire.obj", glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.f), 1.0f);
	camp_fire->create();
	model_list.push_back(camp_fire);

	model* ufoo = new ufo(light_shader, "data/objects/ufo.obj", glm::vec3(3.0f, 30.0f, 3.0f), glm::vec3(0.0f, 0.0f, 1.0f), 3.5f);
	ufoo->create();
	model_list.push_back(ufoo);

	model* cave = new loaded_model(light_shader, "data/objects/cave.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.2f), 8.0f);
	cave->create();
	model_list.push_back(cave);

	model* skeleton = new loaded_model(light_shader, "data/objects/skeleton.obj", glm::vec3(-2.0f, -2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f);
	skeleton->create();
	model_list.push_back(skeleton);

	model* quad = new happy_cube(light_shader, glm::vec3(-20.0f, 5.0f, 10.0f), glm::vec3(0.4f, 1.0f, 1.0f), 3.0f);
	quad->create();
	model_list.push_back(quad);

	generate_trees();

	create_bird(glm::vec3(1.0f, 20.0f, -3.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

model_manager::~model_manager() {
	for (auto &model : model_list) {
		delete model;
	}
	model_list.clear();
}

void model_manager::draw_models(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) {
	int i = 0;
	for (auto &model : model_list) {
		glStencilFunc(GL_ALWAYS, i, -1);
		model->draw(projection_matrix, view_matrix);
		i++;
	}
}

void model_manager::update_models() {
	for (auto &model : model_list) {
		model->update();
	}
}

const model* model_manager::get_model(const int& position) const {
	return model_list.at(position);
}

void model_manager::generate_trees() {
	float height = 6.0f;
	int range = 80;
	int offset = 20;
	int num_of_trees = 40;

	for (size_t i = 0; i < num_of_trees / 4; i++) {
		glm::vec3 random_position = glm::vec3(rand() % range + offset, height, rand() % range + offset);
		create_tree(random_position, glm::vec3(i, 0.0f, 1.0f), rand() % 2 + 8);
	}
	for (size_t i = 0; i < num_of_trees / 4; i++) {
		glm::vec3 random_position = glm::vec3(-(rand() % range + offset), height, -(rand() % range + offset));
		create_tree(random_position, glm::vec3(i, 0.0f, 1.0f), rand() % 2 + 8);
	}
	for (size_t i = 0; i < num_of_trees / 4; i++) {
		glm::vec3 random_position = glm::vec3(-(rand() % range + offset), height, rand() % range + offset);
		create_tree(random_position, glm::vec3(i, 0.0f, 1.0f), rand() % 2 + 8);
	}
	for (size_t i = 0; i < num_of_trees / 4; i++) {
		glm::vec3 random_position = glm::vec3(rand() % range + offset, height, -(rand() % range + offset));
		create_tree(random_position, glm::vec3(i, 0.0f, 1.0f), rand() % 2 + 8);
	}
}

void model_manager::create_tree(const glm::vec3 & position, const glm::vec3 & direction, const float & size) {
	model* tree = new loaded_model(shader_manager::get_shader("light_shader"), "data/objects/tree.obj", position, direction, size);
	tree->create();
	model_list.push_back(tree);
}

void model_manager::create_bird(const glm::vec3& position, const glm::vec3& direction) {
	model* raven = new bird(shader_manager::get_shader("animated_shader"), position, direction, 0.005f);
	raven->create();
	model_list.push_back(raven);
}