#pragma once
#include "zamp/consts.hpp"
#include <cmath>
namespace amp {
	inline const std::double_t angleTo(amp::pose initial, amp::pose final) {
		return std::atan2((final.y - initial.y), (final.x - initial.x));
	};
	inline const std::double_t constrainAngle(std::double_t x) {
		x = fmod(x + amp::numbers::PI, 2 * amp::numbers::PI);
		if (x < 0) x += 2 * amp::numbers::PI;
		return x - amp::numbers::PI;
	}

	inline double distanceTo(const amp::pose& a, const amp::pose& b) {
		return std::hypot(b.x - a.x, b.y - a.y);
	}

}