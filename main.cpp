// --- Global variables ---
	// Ports
		#include <string>
		int LEFT_MOTOR_1_PORT = 11; 		// Left motor 1 port
		int LEFT_MOTOR_2_PORT = 12; 		// Left motor 2 port
		int RIGHT_MOTOR_1_PORT = 19; 	// Right motor 1 port
		int RIGHT_MOTOR_2_PORT = 20; 	// Right motor 1 port
		int STRINGDROP_PORT = 7;		// Rubber band wheel port
		int FLYWHEEL_PORT_1 = 1;		// Flywheel 1 port
		int FLYWHEEL_PORT_2 = 10;		// Flywheel 2 port
		int BELT_MOTOR_PORT = 14;		// Motor for the belt intake
		#define PNEUMATICS_A 'H' 		// PNEUMATICS port A
		#define PNEUMATICS_B 'B' 		// PNEUMATICS port A
	// Other
		int PNEUMATICS_DELAY = 200;
		float STRINGDROP_MULTIPLIER = 0.2;
		float FLYWHEEL_MULTIPLIER = 1.0;

// PROS libraries
	#include "main.h"
	#include "pros/misc.h"
	#include "pros/llemu.hpp"


void initialize() {
	/**
		* Runs initialization code. This occurs as soon as the program is started.
		*
		* All other competition modes are blocked by initialize; it is recommended
		* to keep execution time for this mode under a few seconds.
		*/
	pros::lcd::initialize();
	pros::lcd::set_text(1, "A moment of silence");
	pros::lcd::set_text(2, "for the deceased...");
}

void disabled() {
	/**
		* Runs while the robot is in the disabled state of Field Management System or
		* the VEX Competition Switch, following either autonomous or opcontrol. When
		* the robot is enabled, this task will exit.
		*/
}

void competition_initialize() {
	/**
		* Runs after initialize(), and before autonomous when connected to the Field
		* Management System or the VEX Competition Switch. This is intended for
		* competition-specific initialization routines, such as an autonomous selector
		* on the LCD.
		*
		* This task will exit when the robot is enabled and autonomous or opcontrol
		* starts.
		*/
	}


void autonomous() {
	/**
		* Runs the user autonomous code. This function will be started in its own task
		* with the default priority and stack size whenever the robot is enabled via
		* the Field Management System or the VEX Competition Switch in the autonomous
		* mode. Alternatively, this function may be called in initialize or opcontrol
		* for non-competition testing purposes.
		*
		* If the robot is disabled or communications is lost, the autonomous task
		* will be stopped. Re-enabling the robot will restart the task, not re-start it
		* from where it left off.
		*/	


}

void opcontrol() {
	/**
		* Runs the operator control code. This function will be started in its own task
		* with the default priority and stack size whenever the robot is enabled via
		* the Field Management System or the VEX Competition Switch in the operator
		* control mode.
		*
		* If no competition control is connected, this function will run immediately
		* following initialize().
		*
		* If the robot is disabled or communications is lost, the
		* operator control task will be stopped. Re-enabling the robot will restart the
		* task, not resume it from where it left off.
		*/

	// --- Controller, pneumatics and motor setup ---
		pros::Controller master(pros::E_CONTROLLER_MASTER); // Controller setup

		pros::ADIDigitalOut pneumaticsA (PNEUMATICS_A);	// PNEUMATICS setup
		pros::ADIDigitalOut pneumaticsB (PNEUMATICS_B);	// PNEUMATICS setup

		
		// --- Motor setup ---
			// Edit the ports using the global variables, please
			pros::Motor left_mtr1(LEFT_MOTOR_1_PORT); 	// Left side motor
			pros::Motor left_mtr2(LEFT_MOTOR_2_PORT); 	// Left side motor
			pros::Motor right_mtr1(RIGHT_MOTOR_1_PORT); 	// Right side motor
			pros::Motor right_mtr2(RIGHT_MOTOR_2_PORT); 	// Right side motor
			pros::Motor stringdrop_mtr(STRINGDROP_PORT);	// Rubber band wheel motor
			pros::Motor Flywheel1(FLYWHEEL_PORT_1);		// Flywheel motor 1
			pros::Motor Flywheel2(FLYWHEEL_PORT_2);		// Flywheel motor 2
			pros::Motor BeltMotor(BELT_MOTOR_PORT);		// Belt intake motor



	while (true) { // Infinite loop while the opcontrol is running to refresh controller input and output it to the motors

		// Read controller
			int left_stickY = master.get_analog(ANALOG_LEFT_Y);
			int right_stickY = master.get_analog(ANALOG_RIGHT_Y);
			bool buttonA = master.get_digital(DIGITAL_A);
			bool buttonX = master.get_digital(DIGITAL_X);
			bool bumperL1 = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
			bool bumperL2 = master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
			bool bumperR1 = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
			bool bumperR2 = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);




		if (buttonX) { // PNEUMATICS function
			pneumaticsA.set_value(true); 					// Expand piston
			pneumaticsB.set_value(true); 					// Expand piston
		}

		
		// Output to motors
			left_mtr1 = left_stickY; 					// Left and right side motors move by the sticks of their respective sides (tank controls)
			left_mtr2 = left_stickY;
			right_mtr1 = - right_stickY;				// This motor is reversed
			right_mtr2 = - right_stickY;

			if (bumperR1) {
				Flywheel1 = -255 * FLYWHEEL_MULTIPLIER;
				Flywheel2 = 255 * FLYWHEEL_MULTIPLIER;
			}
			else if (bumperR2) {
				Flywheel1 = 30 * FLYWHEEL_MULTIPLIER;
				Flywheel2 = -30 * FLYWHEEL_MULTIPLIER;

			}
			else {
				Flywheel1 = 0;
				Flywheel2 = 0;
			}



			if (bumperL1) {
				BeltMotor = 255;
			}
			else if (bumperL2) {
				BeltMotor = -255;

			}
			else {
				BeltMotor = 0;
			}

			

		pros::delay(20); // This is required for the screen to function
	}
}
