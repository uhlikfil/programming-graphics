#version 450 core


in vec3 position;
in vec3 vert_normal;
in vec2 tex_coord;

uniform mat4 pvm_matrix;     // Projection * View * Model  --> model to clip coordinates
uniform mat4 v_matrix;       // View                       --> world to eye coordinates
uniform mat4 m_matrix;       // Model                      --> model to world coordinates
uniform mat4 normal_matrix;  // inverse transposed Mmatrix
 
smooth out vec2 out_tex_coord;  // outgoing texture coordinates
smooth out vec4 out_color;
smooth out vec3 frag_position;
smooth out vec3 frag_normal;

void main()  {

	// vertex position after the projection (gl_Position is built-in output variable)
	gl_Position = pvm_matrix * vec4(position, 1.0);   // out:v vertex in clip coordinates

	out_tex_coord = tex_coord;
	frag_position = vec3(m_matrix * vec4(position, 1.0));
    frag_normal = vec3(normal_matrix * vec4(vert_normal, 0.0));
}