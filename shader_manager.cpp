#include "shader_manager.h"


std::map<std::string, shader_struct> shader_manager::all_shaders;

// constructor, destructor
shader_manager::shader_manager() {}
shader_manager::~shader_manager() {
	std::map<std::string, GLuint>::iterator i;
	for (auto i = all_shaders.begin(); i != all_shaders.end(); ++i) {
		GLuint pr = i->second.program;
		pgr::deleteProgramAndShaders(pr);
	}
	all_shaders.clear();
}

// creates program from shaders
void shader_manager::create_shader(const std::string& shader_name, const std::string& vs_filename, const std::string& fs_filename) {

	GLuint shaders[] = {
	  pgr::createShaderFromFile(GL_VERTEX_SHADER, vs_filename),
	  pgr::createShaderFromFile(GL_FRAGMENT_SHADER, fs_filename),
	  0,
	};

	shader_struct sh;

	sh.program = pgr::createProgram(shaders);

	sh.position_loc = glGetAttribLocation(sh.program, "position");
	sh.normal_loc = glGetAttribLocation(sh.program, "vert_normal");
	//matrices
	sh.pvm_matrix_loc = glGetUniformLocation(sh.program, "pvm_matrix");
	sh.v_matrix_loc = glGetUniformLocation(sh.program, "v_matrix");
	sh.m_matrix_loc = glGetUniformLocation(sh.program, "m_matrix");
	sh.normal_matrix_loc = glGetUniformLocation(sh.program, "normal_matrix");
	// material
	sh.diffuse_loc = glGetUniformLocation(sh.program, "material.diffuse");
	sh.ambient_loc = glGetUniformLocation(sh.program, "material.ambient");
	sh.specular_loc = glGetUniformLocation(sh.program, "material.specular");
	sh.shininess_loc = glGetUniformLocation(sh.program, "material.shininess");
	sh.use_texture_loc = glGetUniformLocation(sh.program, "material.use_texture");

	// texture
	sh.texture_coord_loc = glGetAttribLocation(sh.program, "tex_coord");
	sh.tex_sampler_loc = glGetUniformLocation(sh.program, "tex_sampler");
	sh.rotate_texture_loc = glGetUniformLocation(sh.program, "rotate_texture");
	// skybox
	sh.screen_coord_loc = glGetAttribLocation(sh.program, "screen_coord");
	sh.day_skybox_sampler_loc = glGetUniformLocation(sh.program, "day_skybox_sampler");
	sh.night_skybox_sampler_loc = glGetUniformLocation(sh.program, "night_skybox_sampler");
	sh.inverse_pv_matrix_loc = glGetUniformLocation(sh.program, "inverse_pv_matrix");
	// time
	sh.next_position_loc = glGetAttribLocation(sh.program, "next_position");
	sh.t_loc = glGetUniformLocation(sh.program, "t");
	sh.day_length_loc = glGetUniformLocation(sh.program, "day_length");
	// light
	sh.reflector_ambient_loc = glGetUniformLocation(sh.program, "reflector_ambient");
	sh.reflector_cut_off_loc = glGetUniformLocation(sh.program, "reflector_cut_off");
	sh.reflector_outer_cut_off_loc = glGetUniformLocation(sh.program, "reflector_outer_cut_off");
	sh.reflector_position_loc = glGetUniformLocation(sh.program, "reflector_position");
	sh.reflector_direction_loc = glGetUniformLocation(sh.program, "reflector_direction");
	sh.campfire_burning_loc = glGetUniformLocation(sh.program, "campfire_burning");

	all_shaders[shader_name] = sh;
}

const shader_struct& shader_manager::get_shader(const std::string & shader_name) {
	return all_shaders.at(shader_name);
}
