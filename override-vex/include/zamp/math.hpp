#pragma once
#include "zamp/consts.hpp"
#include <cmath>
#include <numbers>
#include <utility>

// Math lib. Does math
namespace amp {
	inline const std::double_t angleTo(amp::pose initial, amp::pose final) {
		return std::atan2(
		    (final.y - initial.y),
		    (final.x - initial.x)); // Gets angle needed to point to a point
	};
	inline const std::double_t constrainAngle(std::double_t x) {
		x = x * (amp::numbers::PI / 180);
		x = fmod(x + amp::numbers::PI, 2 * amp::numbers::PI);
		if (x < 0) x += 2 * amp::numbers::PI;
		return (180 / amp::numbers::PI) *
		       (x - amp::numbers::PI); // Constrains an angle to [-180, 180]
	}

	inline double distanceTo(const amp::pose& a, const amp::pose& b) {
		return std::hypot(b.x - a.x, b.y - a.y); // Distance to point from point
	}

	inline std::pair<double, double> poseTo(
	    const amp::pose& chassisPose,
	    const amp::pose& target,
	    std::pair<double /*LinearKP*/, double /*AngularKP*/> kp,
	    amp::moveSettings settings) { // Function that gets the speeds both
		                              // sides of DT need to be at to approach a
		                              // point
		double distance = amp::distanceTo(chassisPose, target);
		double targetAngle = amp::angleTo(chassisPose, target);
		double angleErr = amp::constrainAngle(targetAngle - chassisPose.theta);

		// Controllers
		double forward = distance * kp.first;
		double turn = angleErr * kp.second;

		// Turn Into Sides
		double left = forward - turn;
		double right = forward + turn;
		double largest = std::max(left, right);
		if (largest > settings.maxVolt) {
			left *= settings.maxVolt / largest;
			right *= settings.maxVolt / largest;
		}
		return { left, right };
	}
}
