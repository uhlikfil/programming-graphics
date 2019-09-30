#pragma once

#include "pgr.h"

template <typename T>
T cyclic_clamp(const T value, const T minBound, const T maxBound) {

	T amp = maxBound - minBound;
	T val = fmod(value - minBound, amp);

	if (val < T(0))
		val += amp;

	return val + minBound;
}

glm::vec3 evaluate_curve_segment(
	const glm::vec3& P0,
	const glm::vec3& P1,
	const glm::vec3& P2,
	const glm::vec3& P3,
	const float t
);

glm::vec3 evaluate_curve_segment_1st_derivative(
	const glm::vec3& P0,
	const glm::vec3& P1,
	const glm::vec3& P2,
	const glm::vec3& P3,
	const float t
);

glm::vec3 evaluate_closed_curve(
	const glm::vec3 points[],
	const size_t    count,
	const float     t
);

glm::vec3 evaluate_closed_curve_1st_derivative(
	const glm::vec3 points[],
	const size_t    count,
	const float     t
);