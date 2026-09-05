#pragma once
#include <cstdint>
namespace amp {

	class airCylinder {
	public:
		/**
		 * @brief Construct a new smart Cylinder object
		 *
		 * @param port
		         The ADI port number (from 1-8, 'a'-'h', 'A'-'H') to configure
		 * @param value
		         The value that the piston STARTS WITH
		 */
		// Pneumatics use weird wording
		airCylinder(std::uint8_t port, bool value = false)
		    : port(port)
		    , value(value) {}

		/**
		 * @brief Set the value object
		 *
		 * @param value
		 */
		void set(bool value) { this->value = value; }
		/**
		 * @brief Toggles the pneumatic cylinder to the other state
		 *
		 */
		// Peak effort
		void toggle(void) { this->set(!this->value); }
		/**
		 * @brief Get the state of the air cylinder
		 *
		 * @return true The cylinder is extended
		 * @return false The cylinder is not extended
		 */
		bool get(void) { return this->value; }

	private:
		bool value;
		int port;
	};
}