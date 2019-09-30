#version 450 core

uniform float t;
uniform mat4 v_matrix;
uniform sampler2D tex_sampler;

uniform ivec2 pattern = ivec2(4, 4);
uniform float frame_duration = 75.0;

smooth in vec2 tex_coord_v;

out vec4 color_f;

vec2 get_texture_part(int frame) {
	vec2 offset = vec2(1.0) / vec2(pattern);

	vec2 tex_coord_base = tex_coord_v / vec2(pattern);
	vec2 tex_coord = tex_coord_base + vec2(frame % pattern.x, -(frame / pattern.x)) * offset;

	return tex_coord;
}

void main() {
	
	int frame = int(t / frame_duration);

	vec4 color = texture(tex_sampler, get_texture_part(frame));

	if (color.x < 0.15 && color.y < 0.15 && color.z < 0.15) {
		discard;
	} else {
		color_f = color;
	}
}