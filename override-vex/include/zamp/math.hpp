#pragma once
#include "zamp/consts.hpp"
#include <cmath>
namespace amp {
	inline const std::double_t getTargetTheta(amp::pose initial,
	                                          amp::pose final) {
		return std::atan2((final.y - initial.y), (final.x - initial.x)) *
		       amp::numbers::toDEGS;
	};

	inline const std::double_t constrainAngle(std::double_t x) {
		x = fmod(x + 180, 360);
		if (x < 0) x += 360;
		return x - 180;
	}

}