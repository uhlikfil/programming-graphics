#version 450 core


uniform float day_length;
uniform float t;
uniform samplerCube day_skybox_sampler;
uniform samplerCube night_skybox_sampler;
in vec3 tex_coord_v;
out vec4 color_f;

void main() {
	float time = 0.5 * cos(3.14 * t / day_length) + 0.5;
	vec4 day_tex = texture(day_skybox_sampler, tex_coord_v);
	vec4 night_tex = texture(night_skybox_sampler, tex_coord_v);
	color_f = mix(night_tex, day_tex, time);
}