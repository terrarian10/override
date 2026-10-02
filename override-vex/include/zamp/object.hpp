#pragma once
#include "zamp/airCylinder.hpp"
#include "zamp/state.hpp"
#include <cstdint>
#include <map>
#include <unordered_map>
#include <vector>
namespace amp {
	class object {
	public:
		explicit object(
		    std::map<std::string, std::vector<amp::motor>>& motors,
		    std::map<std::string, std::vector<amp::airCylinder>>& airs)
		    : airs(airs)
		    , motors(motors) {};
		virtual ~object() = default;
		std::map<int, int> getMotors() {
			std::map<int, int> toRet;
			for (auto& group : motors) {
				for (auto& motor : group.second) {
					toRet[motor.get(motorStats::PORT)] =
					    motor.get(motorStats::SPEED);
				}
			}
			return toRet;
		}
		std::map<std::pair<std::uint8_t, std::uint8_t>, int> getAirs() {
			std::map<std::pair<std::uint8_t, std::uint8_t>, int> toRet;
			for (auto& group : airs) {
				for (auto& air : group.second) {
					toRet[air.getPort()] = air.get();
				}
			}
			return toRet;
		}

	private:
		std::map<std::string, std::vector<amp::motor>>& motors;
		std::map<std::string, std::vector<amp::airCylinder>>& airs;
	};
}