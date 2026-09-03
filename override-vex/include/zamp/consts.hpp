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
		float getDegrees() { return theta; };
		float getRadians() { return theta * std::numbers::pi / 180; }
		void setDegrees(std::double_t toSet) { theta = toSet; }
		void setRadians(std::double_t toSet) { theta = numbers::toDEGS; }
	};
}