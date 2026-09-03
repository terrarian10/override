#include "zamp/airCylinder.hpp"
#include "zamp/motor.hpp"
#include <vector>
namespace amp {
	class subsystem {
	public:
		explicit subsystem(std::vector<amp::airCylinder>& airs,
		                   std::vector<amp::motor>& motors)
		    : airs(airs)
		    , motors(motors) {};

	private:
		std::vector<amp::airCylinder>& airs;
		std::vector<amp::motor>& motors;
	};
}