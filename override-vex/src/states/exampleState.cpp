#include "zamp/airCylinder.hpp"
#include "zamp/state.hpp"
#include <map>
#include <string>

namespace amp {
	class testState : public amp::state {
		testState(std::map<std::string, amp::motor> motors,
		          std::map<std::string, amp::airCylinder> airs)
		    : state("state", motors, airs) {}
		void activate() override {}
	};
}