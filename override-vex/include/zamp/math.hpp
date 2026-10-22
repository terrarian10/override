#pragma once
#include "zamp/consts.hpp"
#include <cmath>
#include <numbers>
#include <utility>
namespace amp {
	inline const std::double_t angleTo(amp::pose initial, amp::pose final) {
		return std::atan2((final.y - initial.y), (final.x - initial.x));
	};
	inline const std::double_t constrainAngle(std::double_t x) {
		x = x * (amp::numbers::PI / 180);
		x = fmod(x + amp::numbers::PI, 2 * amp::numbers::PI);
		if (x < 0) x += 2 * amp::numbers::PI;
		return (180 / amp::numbers::PI) * (x - amp::numbers::PI);
	}

	inline double distanceTo(const amp::pose& a, const amp::pose& b) {
		return std::hypot(b.x - a.x, b.y - a.y);
	}

	inline std::pair<double, double> poseTo(
	    const amp::pose& chassisPose,
	    const amp::pose& target,
	    std::pair<double /*LinearKP*/, double /*AngularKP*/> kp,
	    amp::moveSettings settings) {
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
