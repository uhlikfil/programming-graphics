#pragma once

#include "pgr.h"
#include <iostream>
#include <map>


struct shader_struct {
	GLuint program;
	GLint position_loc;
	GLint normal_loc;

	// matrices
	GLint pvm_matrix_loc;
	GLint v_matrix_loc;
	GLint m_matrix_loc;
	GLint normal_matrix_loc;

	//material
	GLint diffuse_loc;
	GLint ambient_loc;
	GLint specular_loc;
	GLint shininess_loc;
	GLint use_texture_loc;

	// texture
	GLint texture_coord_loc;
	GLint tex_sampler_loc;
	GLint rotate_texture_loc;

	// skybox stuff
	GLint screen_coord_loc;
	GLint inverse_pv_matrix_loc;
	GLint day_skybox_sampler_loc;
	GLint night_skybox_sampler_loc;

	// time stuff
	GLint next_position_loc;
	GLint t_loc;
	GLint day_length_loc;

	// light stuff
	GLint reflector_ambient_loc;
	GLint reflector_cut_off_loc;
	GLint reflector_outer_cut_off_loc;
	GLint reflector_position_loc;
	GLint reflector_direction_loc;
	GLint campfire_burning_loc;
};

class shader_manager {
public:
	shader_manager();
	~shader_manager();

	void create_shader(const std::string& shader_name, const std::string& vs_filename, const std::string& fs_filename);

	static const shader_struct& get_shader(const std::string& shader_name);
private:
	static std::map<std::string, shader_struct> all_shaders;
};