#pragma once
#include "zamp/airCylinder.hpp"
#include "zamp/motor.hpp"
#include <map>
#include <string>
namespace amp {
	class state {
	public:
		explicit state(std::map<std::string, amp::motor>& motors,
		               std::map<std::string, amp::airCylinder>& airs,
		               std::string id)
		    : airs(airs)
		    , motors(motors)
		    , id(std::move(id)) {};
		virtual ~state() = default;
		virtual void activate() = 0;
		const std::string& getId() const { return id; }

	protected:
		amp::airCylinder& air(const std::string& name) { return airs.at(name); }
		amp::motor& motor(const std::string& name) { return motors.at(name); }

	private:
		std::map<std::string, amp::airCylinder> airs;
		std::map<std::string, amp::motor>& motors;
		std::string id;
	};
}