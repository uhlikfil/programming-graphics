#version 450 core

uniform mat4 inverse_pv_matrix;

in vec2 screen_coord;
out vec3 tex_coord_v;

void main() {
	vec4 farplane_coord = vec4(screen_coord, 0.9999, 1.0);
	vec4 world_view_coord = inverse_pv_matrix * farplane_coord;
	tex_coord_v = world_view_coord.xyz / world_view_coord.w;
	gl_Position = farplane_coord;
}