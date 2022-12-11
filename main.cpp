// --- Global variables ---
	// Ports
		#include <string>
		int LEFT_MOTOR_1_PORT = 10; 		// Left motor 1 port
		int RIGHT_MOTOR_1_PORT = 1; 	// Right motor 1 port
		int BAND_WHEEL_PORT = 20;		// Rubber band wheel port
		int FLYWHEEL_PORT_1 = 6;		// Flywheel 1 port
		int FLYWHEEL_PORT_2 = 7;		// Flywheel 2 port
		int BELT_MOTOR_PORT = 20;		// Motor for the belt intake
		#define PNEUMATICS_A 'A' 		// PNEUMATICS port A
		#define PNEUMATICS_B 'B' 		// PNEUMATICS port A
	// Other
		int PNEUMATICS_DELAY = 200;
		int ROLLER_SPEED = 50;

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
			pros::Motor right_mtr1(RIGHT_MOTOR_1_PORT); 	// Right side motor
			pros::Motor wheel_mtr(BAND_WHEEL_PORT);		// Rubber band wheel motor
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
			pros::delay(PNEUMATICS_DELAY); 	// Delay to allow the piston to expand
			pneumaticsA.set_value(false);					// Retract piston
			pneumaticsB.set_value(false);					// Retract piston

		}

		if (buttonA) { // Autonomous test
			// --- Motor setup ---
				// Edit the ports using the global variables, please
				pros::Motor left_mtr1(LEFT_MOTOR_1_PORT); 	// Left side motor
				pros::Motor right_mtr1(RIGHT_MOTOR_1_PORT); 	// Right side motor
				pros::Motor wheel_mtr(BAND_WHEEL_PORT);		// Rubber band wheel motor
				pros::Motor Flywheel1(FLYWHEEL_PORT_1);		// Flywheel motor 1
				pros::Motor Flywheel2(FLYWHEEL_PORT_2);		// Flywheel motor 2
				pros::Motor BeltMotor(BELT_MOTOR_PORT);		// Belt intake motor

			// Turn 45 degrees
			left_mtr1 = 100; right_mtr1 = 0;
			pros::delay(500);
			// Go full speed ahead for 2 seconds
			left_mtr1 = 255; right_mtr1 = -255;
			pros::delay(2000);			
			// Turn 45 degrees
			left_mtr1 = 100; right_mtr1 = 0;
			pros::delay(500);
			/** // Go full speed ahead for 2 seconds
			left_mtr1 = 255; right_mtr1 = -255;
			pros::delay(2000);
			// Push disks in
			left_mtr1 = 255; right_mtr1 = -100;
			pros::delay(2000); */
		

		}

		
		// Output to motors
			left_mtr1 = left_stickY; 					// Left and right side motors move by the sticks of their respective sides (tank controls)
			right_mtr1 = - right_stickY;				// This motor is reversed
			wheel_mtr = buttonA;						// The band wheel moves on button A

			if (bumperR1) {
				Flywheel1 = -255;
				Flywheel2 = 255;
			}
			else{
				Flywheel1 = 0;
				Flywheel2 = 0;
			}

			if (bumperL1) {
				pros::lcd::set_text(3, "L1");
				BeltMotor = - ROLLER_SPEED;
			}
			else if (bumperL2) {
				pros::lcd::set_text(3, "L2");
				BeltMotor = ROLLER_SPEED;
			}
			else {
				pros::lcd::set_text(3, "OFF");
				BeltMotor = 0;
			}


		pros::delay(20); // This is required for the screen to function
	}
}
