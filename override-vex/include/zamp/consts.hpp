#pragma once
#include <cmath>
#include <numbers>

// Constants
namespace amp::WHEELS { // Wheel sizes, not in the namespace because why the
                        // frick not
	static constexpr std::double_t IN_2_OMNI = 5.08;
}
namespace amp {
	namespace numbers { // Important numbers
		const std::double_t PI =
		    std::numbers::pi; // Pi is ours now. We invented it
		// const std::double_t toRADS = PI / 180;
		const std::double_t toDEGS = 180 / PI;
	};
	// Pose
	struct pose {
		std::double_t x;
		std::double_t y;
		std::double_t theta = 0;
		double getDegrees() const { return theta; };
		void setDegrees(double degrees) { theta = degrees; }
	};
	// Settings for handling a motion
	struct moveSettings {
		const double maxVolt;
	};

}