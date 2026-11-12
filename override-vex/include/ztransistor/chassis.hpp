#include "zamp/chassis.hpp"
#include "zamp/consts.hpp"
#include "zamp/math.hpp"
#include "zamp/robot.hpp"
#include "ztransistor/consts.hpp"
#include "ztransistor/main.hpp"
#include <cmath>
namespace amp {
	class moveToPose : amp::command {
	public:
		moveToPose(amp::pose pose,
		           amp::robot& robot,
		           std::pair<double, double> threshold,
		           amp::motionSettings settings = { 12700, 300, 12000 })
		    : pose(pose)
		    , robot(robot)
		    , settings(settings) {}
		bool run() {
			robot.moveToPose(pose, { .maxVolt = settings.maxVolt });
			if (std::hypot(std::abs(pose.x - robot.getPose().x),
			               std::abs(pose.y - robot.getPose().y)) <
			    threshold.first)
				return true;
			return false;
		}

	private:
		amp::pose pose;
		amp::robot& robot;
		std::pair<double, double> threshold;
		amp::motionSettings settings;
	};
	class setState : amp::command {
	public:
		setState(std::string state, std::string mech, amp::robot& robot)
		    : robot(robot)
		    , state(state)
		    , mech(mech) {}
		bool run() {
			robot.setState(mech, state);

			return true;
		}

	private:
		amp::robot& robot;
		std::string state;
		std::string mech;
	};
}