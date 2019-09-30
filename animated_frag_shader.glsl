#version 450 core

smooth in vec3 color;
smooth in vec3 frag_position;

uniform mat4 v_matrix;       // View                       --> world to eye coordinates

out vec4 color_f;

vec4 apply_fog(vec4 out_color) {
	vec4 fog_color = vec4(vec3(0.5), 1.0);
	float fog_density = 0.01;

	vec3 view_space = (v_matrix * vec4(frag_position, 1.0)).xyz;
	float dst = length(view_space);
	float fog_factor = 1 / exp((dst * fog_density) * (dst * fog_density));
	fog_factor = clamp(fog_factor, 0.0, 1.0);

	return mix(fog_color, out_color, fog_factor);
}

void main() {
	color_f = apply_fog(vec4(color, 1.0));
}