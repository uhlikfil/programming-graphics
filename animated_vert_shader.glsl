#version 450 core

in vec3 position;
in vec3 next_position;

smooth out vec3 color;
smooth out vec3 frag_position;

uniform mat4 v_matrix;       // View                       --> world to eye coordinates
uniform mat4 m_matrix;  
uniform mat4 pvm_matrix;     // Projection * View * Model  --> model to clip coordinates

uniform float t;

void main() {
	color = vec3(0.05, 0.05, 0.05);
	gl_Position = pvm_matrix * vec4(mix(position, next_position, t), 1.0);   // out:v vertex in clip coordinates

	frag_position = vec3(m_matrix * vec4(position, 1.0));
}