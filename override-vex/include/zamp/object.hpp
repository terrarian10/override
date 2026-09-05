#include "zamp/airCylinder.hpp"
#include "zamp/state.hpp"
#include <unordered_map>
#include <vector>
namespace amp {
	class object {
	public:
		explicit object(
		    std::unordered_map<std::string, std::vector<amp::motor>>& motors,
		    std::unordered_map<std::string, std::vector<amp::airCylinder>>&
		        airs)
		    : airs(airs)
		    , motors(motors) {};

	private:
		std::unordered_map<std::string, std::vector<amp::motor>>& motors;
		std::unordered_map<std::string, std::vector<amp::airCylinder>>& airs;
	};
}