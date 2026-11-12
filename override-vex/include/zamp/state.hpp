#pragma once
#include "zamp/airCylinder.hpp"
#include "zamp/motor.hpp"
#include <map>
#include <string>
namespace amp {
	// A mech state
	class state {
	public:
		explicit state(std::string id,
		               std::map<std::string, amp::motor>& motors,
		               std::map<std::string, amp::airCylinder>& airs)
		    : airs(airs)
		    , motors(motors)
		    , id(std::move(id)) {};

		// How to properly die
		virtual ~state() = default;

		// Do nothing most of the time
		virtual void activate() = 0;

		// Whats my nameee whats my nameee
		const std::string& getId() const { return id; }

	protected:
		// HE PROTECC from others. not the children. Its open to children.
		amp::airCylinder& air(const std::string& name) { return airs.at(name); }
		amp::motor& motor(const std::string& name) { return motors.at(name); }

	private:
		// Still in the  closet
		std::map<std::string, amp::airCylinder>& airs;
		std::map<std::string, amp::motor>& motors;
		std::string id;
	};
}