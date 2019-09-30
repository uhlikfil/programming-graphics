#version 450 core

uniform mat4 pvm_matrix;

in vec3 position;
in vec2 tex_coord;

smooth out vec2 tex_coord_v;

void main() {
	gl_Position = pvm_matrix * vec4(position, 1.0);

	tex_coord_v = tex_coord;
}