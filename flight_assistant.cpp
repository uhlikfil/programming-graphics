#include "flight_assistant.h"


glm::vec3 evaluate_curve_segment(const glm::vec3 & P0, const glm::vec3 & P1, const glm::vec3 & P2, const glm::vec3 & P3, const float t) {
	const float t2 = t * t;
	const float t3 = t2 * t;
	glm::mat4 matrix = glm::mat4(-1.0f, 3.0f, -3.0f, 1.0f, 2.0f, -5.0f, 4.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f);
	glm::mat4x3 p_matrix = glm::mat4x3(P0, P1, P2, P3);
	glm::vec4 t_vec = glm::vec4(t3, t2, t, 1.0f);

	return 0.5f * p_matrix * matrix * t_vec;
}

glm::vec3 evaluate_curve_segment_1st_derivative(const glm::vec3 & P0, const glm::vec3 & P1, const glm::vec3 & P2, const glm::vec3 & P3, const float t) {
	const float t2 = t * t;
	glm::mat4 matrix = glm::mat4(-1.0f, 3.0f, -3.0f, 1.0f, 2.0f, -5.0f, 4.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f);
	glm::mat4x3 p_matrix = glm::mat4x3(P0, P1, P2, P3);
	glm::vec4 t_vec = glm::vec4(3 * t2, 2 * t, 1.0f, 0.0f);

	return 0.5f * p_matrix * matrix * t_vec;
}

glm::vec3 evaluate_closed_curve(const glm::vec3 points[], const size_t count, const float t) {
	glm::vec3 result(0.0, 0.0, 0.0);

	float param = cyclic_clamp(t, 0.0f, float(count));
	size_t index = size_t(param);

	glm::vec3 p0 = points[(index - 1 + count) % count];
	glm::vec3 p1 = points[(index) % count];
	glm::vec3 p2 = points[(index + 1) % count];
	glm::vec3 p3 = points[(index + 2) % count];

	return evaluate_curve_segment(p0, p1, p2, p3, param - floor(param));
}

glm::vec3 evaluate_closed_curve_1st_derivative(const glm::vec3 points[], const size_t count, const float t) {
	glm::vec3 result(0.0, 0.0, 0.0);

	float param = cyclic_clamp(t, 0.0f, float(count));
	size_t index = size_t(param);

	glm::vec3 p0 = points[(index - 1 + count) % count];
	glm::vec3 p1 = points[(index) % count];
	glm::vec3 p2 = points[(index + 1) % count];
	glm::vec3 p3 = points[(index + 2) % count];

	return evaluate_curve_segment_1st_derivative(p0, p1, p2, p3, param - floor(param));
}
