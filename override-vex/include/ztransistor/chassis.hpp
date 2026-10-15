#include "zamp/chassis.hpp"
#include "zamp/consts.hpp"
#include "zamp/math.hpp"
#include "ztransistor/consts.hpp"
#include "ztransistor/main.hpp"
namespace amp {
	class moveToPose : amp::command {
	public:
		moveToPose(amp::pose pose,
		           amp::chassis& chassis,
		           std::pair<double, double> threshold,
		           amp::motionSettings settings = { 12700, 300 })
		    : pose(pose)
		    , chassis(chassis)
		    , settings(settings) {}
		bool run() {
			amp::poseTo(
			    chassis.getPos(),
			    pose,
			    { chassis.getCtrl().lateralKP, chassis.getCtrl().angularKP },
			    settings);

			return false;
		}

	private:
		amp::pose pose;
		amp::chassis& chassis;
		amp::motionSettings settings;
	};
}