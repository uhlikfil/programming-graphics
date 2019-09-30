#version 450 core
 
struct Material {           // structure that describes currently used material
	vec3  ambient;            // ambient component
	vec3  diffuse;            // diffuse component
	vec3  specular;           // specular component
	float shininess;          // sharpness of specular reflection

	bool use_texture;
};

struct Light
{
    vec3 position;
	vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;

	float cut_off;
	float outer_cut_off;
};

uniform bool rotate_texture;
uniform sampler2D tex_sampler;  // sampler for the texture access
uniform Material material;     // current material
uniform mat4 m_matrix;
uniform mat4 v_matrix;

smooth in vec2 out_tex_coord;     // fragment texture coordinates
smooth in vec3 frag_position;
smooth in vec3 frag_normal;

uniform float day_length;
uniform float t;
uniform bool campfire_burning;

uniform vec3 reflector_ambient;
uniform float reflector_cut_off;
uniform float reflector_outer_cut_off;
uniform vec3 reflector_position;
uniform vec3 reflector_direction;

out vec4 color_f;        // outgoing fragment color

Light sun;
Light campfire;
Light reflector;
void setup_lights() {
	// set up sun parameters
	sun.ambient = vec3(0.2 * (0.5 * cos(3.14 * t / day_length) + 0.5));
	sun.diffuse = vec3(0.2);
	sun.specular = vec3(0.4);

	sun.position = (v_matrix * vec4(10.0, 100.0, -10.0, 0.0)).xyz;

	campfire.ambient = vec3(1.0, 0.0, 0.0);
	campfire.diffuse = vec3(0.2);
	campfire.specular = vec3(0.5);
	campfire.constant = 1.0;
	campfire.linear = 0.22;
	campfire.quadratic = 0.20;

	campfire.position = vec3(0.0, -2.0, 0.0);

	reflector.ambient = reflector_ambient;
	reflector.diffuse = vec3(0.5);
	reflector. specular = vec3(0.5);
	reflector.constant = 1.0;
	reflector.linear = 0.35;
	reflector.quadratic = 0.44;
	reflector.cut_off = cos(radians(reflector_cut_off));
	reflector.outer_cut_off = reflector_outer_cut_off;

	reflector.position = reflector_position;
	reflector.direction = normalize(reflector_direction);
}

vec4 directional_light(Light light) {
	vec3 ret = vec3(0.0);

	vec3 eye_normal = normalize((v_matrix * vec4(frag_normal, 0.0)).xyz);
	vec3 eye_position = (v_matrix * vec4(frag_position, 1.0)).xyz;

	vec3 light_direction = normalize(light.position);
	vec3 light_reflection = reflect(-light_direction, eye_normal);
	vec3 view_direction = normalize(-eye_position);

	ret += material.ambient * light.ambient;
	ret += material.diffuse * light.diffuse * max(0.0, dot(eye_normal, light_direction));
	ret += material.specular * light.specular * pow(max(0.0, dot(light_reflection, view_direction)), material.shininess);

	return vec4(ret, 1.0);
}

vec4 point_light(Light light) {
	vec3 ret = vec3(0.0);

	vec3 light_direction = normalize(light.position - frag_position);
	vec3 light_reflection = reflect(-light_direction, frag_normal);
	vec3 view_direction = normalize(-frag_position);
	
	ret += material.ambient * light.ambient;
	ret += material.diffuse * light.diffuse * max(0.0, dot(frag_normal, light_direction));
	ret += material.specular * light.specular * pow(max(0.0, dot(light_reflection, view_direction)), material.shininess);

	float dst = length(light.position - frag_position);
	float attenuation = 1.0 / (light.constant + light.linear * dst + light.quadratic * (dst * dst));

	return vec4(ret * attenuation, 1.0);
}

vec4 spot_light(Light light) {
	vec3 ret = vec3(0.0);

	vec3 light_direction = normalize(light.position - frag_position);
	vec3 light_reflection = reflect(-light_direction, frag_normal);
	vec3 view_direction = normalize(-frag_position);

	float theta = dot(-light_direction, light.direction);
	float epsilon = (light.cut_off - light.outer_cut_off);
	float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);
	
	ret += material.ambient * light.ambient;
	ret += material.diffuse * light.diffuse * max(0.0, dot(frag_normal, light_direction));
	ret += material.specular * light.specular * pow(max(0.0, dot(light_reflection, view_direction)), material.shininess);

	return vec4(ret, 1.0) * intensity;
}

vec4 apply_fog(vec4 out_color) {
	vec4 fog_color = vec4(vec3(0.5), 1.0);
	float fog_density = 0.01;

	vec3 view_space = (v_matrix * vec4(frag_position, 1.0)).xyz;
	float dst = length(view_space);
	float fog_factor = 1 / exp((dst * fog_density) * (dst * fog_density));
	fog_factor = clamp(fog_factor, 0.0, 1.0);

	return mix(fog_color, out_color, fog_factor);
}

mat2 rotation_matrix(float angle) {
    float s = sin(angle);
    float c = cos(angle);
    
	return mat2(c, s, -s, c);
}

vec2 rotate_around_point(vec2 to_rotate, vec2 rotate_around, float angle) {
	mat2 rotation_m = rotation_matrix(angle);

	to_rotate = to_rotate - rotate_around;
	to_rotate = rotation_m * to_rotate;

	return to_rotate + rotate_around;
}

void main() {
	setup_lights();
	
	vec4 output_color = vec4(material.ambient, 0.0);
	
	// accumulate contributions from all lights
	output_color = directional_light(sun);
	if (campfire_burning) {
		output_color += point_light(campfire);
	}
	output_color += spot_light(reflector);



	// if material has a texture -> apply it
	if (material.use_texture) {
		vec2 tex_coord = out_tex_coord;

		// outputs entering the fragment shader
		if (rotate_texture) {
			tex_coord = rotate_around_point(tex_coord, vec2(0.5, 0.5), t / 5000);
		}
		output_color *= texture(tex_sampler, tex_coord);
	}
	
	color_f = apply_fog(output_color);
}