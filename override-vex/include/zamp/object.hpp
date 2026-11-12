
#pragma once

#include "zamp/state.hpp"

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
// Mechanisms

namespace amp {
	// Sensors
	struct objectSensors {};

	// WHy is this called object and not mechanism or subsystem oR SOMETHING
	class object {
	public:
		explicit object( // Initialize it
		    std::string mechName,
		    std::map<std::string, std::vector<amp::motor>>& motors,
		    std::map<std::string, std::vector<amp::airCylinder>>& airs,
		    objectSensors& sensors)
		    : mechName(std::move(mechName))
		    , motors(motors)
		    , airs(airs)
		    , sensors(sensors) {}

		// How to properly kill
		virtual ~object() = default;

		// Add a state to the list of possible states. You gotta to this schitzo
		// stuff because of funny inheritance messer-upery
		template<typename T, typename... Args>
		void addState(const std::string& id, Args&&... args) {
			auto newState = std::make_unique<T>(
			    id, motors, airs, std::forward<Args>(args)...);

			states.insert_or_assign(id, std::move(newState));
		}
		std::string getName() { return mechName; } // Self explanitory

		// Sets active state, also pretty self explanitory
		void setState(const std::string id) {
			auto it = states.find(id);

			if (it == states.end()) {
				throw std::out_of_range("State not found: " + id);
			}

			it->second->activate();
			activeState = id;
		}

		void update() { getActiveState().activate(); }

		amp::state& getActiveState() { return *states.at(activeState); }

		const std::string& getActiveStateId() const { return activeState; }
		std::map<std::string, std::vector<amp::motor>>& motors;
		std::map<std::string, std::vector<amp::airCylinder>>& airs;

	private:
		objectSensors& sensors;

		std::string mechName;
		std::string activeState;

		std::map<std::string, std::unique_ptr<amp::state>> states;
	};

}
