#include "skybox.h"

skybox::skybox(const shader_struct & shader_s) : model(shader_s) {
}

void skybox::create() {
	// 2D coordinates of 2 triangles covering the whole screen (NDC), draw using triangle strip
	static const float screen_coords[] = {
	  -1.0f, -1.0f,
	   1.0f, -1.0f,
	  -1.0f,  1.0f,
	   1.0f,  1.0f
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(screen_coords), screen_coords, GL_STATIC_DRAW);

	glEnableVertexAttribArray(shader_s.screen_coord_loc);
	glVertexAttribPointer(shader_s.screen_coord_loc, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	glUseProgram(0);

	num_of_triangles = 2;

	glActiveTexture(GL_TEXTURE0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	const char * suffixes[] = { "posx", "negx", "posy", "negy", "posz", "negz" };
	GLuint targets[] = {
	  GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	  GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	  GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	for (int i = 0; i < 6; i++) {
		std::string tex_name = std::string("data/skybox/day/skybox") + "_" + suffixes[i] + ".jpg";
		std::cout << "Loading cube map texture: " << tex_name << std::endl;
		if (!pgr::loadTexImage2D(tex_name, targets[i])) {
			pgr::dieWithError("Skybox cube map loading failed!");
		}
	}

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	// unbind the texture (just in case someone will mess up with texture calls later)
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


	// night skybox
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture2);

	for (int i = 0; i < 6; i++) {
		std::string tex_name = std::string("data/skybox/night/skybox") + "_" + suffixes[i] + ".jpg";
		std::cout << "Loading cube map texture: " << tex_name << std::endl;
		if (!pgr::loadTexImage2D(tex_name, targets[i])) {
			pgr::dieWithError("Skybox cube map loading failed!");
		}
	}

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	// unbind the texture (just in case someone will mess up with texture calls later)
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	CHECK_GL_ERROR();
}

void skybox::draw(const glm::mat4 & projection_matrix, const glm::mat4 & view_matrix) {
	glUseProgram(shader_s.program);
	// compose transformations
	glm::mat4 matrix = projection_matrix * view_matrix;

	// crate view rotation matrix by using view matrix with cleared translation
	glm::mat4 view_rotation = view_matrix;
	view_rotation[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	// vertex shader will translate screen space coordinates (NDC) using inverse PV matrix
	glm::mat4 inverse_pv_matrix = glm::inverse(projection_matrix * view_rotation);

	glUniformMatrix4fv(shader_s.inverse_pv_matrix_loc, 1, GL_FALSE, glm::value_ptr(inverse_pv_matrix));
	glUniform1i(shader_s.day_skybox_sampler_loc, 0);
	glUniform1i(shader_s.night_skybox_sampler_loc, 1);


	// draw "skybox" rendering 2 triangles covering the far plane
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0 + 0); // Texture unit 0
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glActiveTexture(GL_TEXTURE0 + 1); // Texture unit 0
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture2);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, num_of_triangles + 2);

	glBindVertexArray(0);
	glUseProgram(0);
}
