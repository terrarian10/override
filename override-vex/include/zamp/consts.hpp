#pragma once
#include <cmath>
#include <numbers>
namespace amp::WHEELS {
	static constexpr std::double_t IN_2_OMNI = 5.08;

}
namespace amp {
	namespace numbers {
		const std::double_t PI = std::numbers::pi;
		const std::double_t toRADS = PI / 180;
		const std::double_t toDEGS = 180 / PI;
	};
	struct pose {
		std::double_t x;
		std::double_t y;
		std::double_t theta = 0;
		double getDegrees() const { return theta * amp::numbers::toDEGS; };
		double getRadians() const { return theta; }
		void setDegrees(double degrees) { theta = degrees * numbers::toRADS; }

		void setRadians(double radians) { theta = radians; }
	};
}