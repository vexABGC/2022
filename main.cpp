// --- Global variables ---
	int LEFT_MOTOR_1_PORT = 1; 		// Left motor 1 port
	int RIGHT_MOTOR_1_PORT = 10; 	// Right motor 1 port
	int BAND_WHEEL_PORT = 12;		// Rubber band wheel port
	// #define PNEUMATICS 'A' 		// PNEUMATICS port
	int count = 0;					// Helps controller screen work
	// bool PneumaticsState = false;// Defaults the PneumaticsState to off, as it is off when the code first runs

// PROS libraries
	#include "main.h"
	#include "pros/misc.h"


void on_center_button() { // Runs when the center button of the brain's touch screen is pressed
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	
	pros::lcd::initialize();
	pros::lcd::set_text(1, "A moment of silence for the deceased...");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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
void autonomous() {
	// Motor setup
	pros::Motor left_mtr1(LEFT_MOTOR_1_PORT);
	pros::Motor right_mtr1(RIGHT_MOTOR_1_PORT);

	left_mtr1 = 100; right_mtr1 = -100;
	pros::delay(1000);
	left_mtr1 = 0; right_mtr1 = 0;
	
}
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
void opcontrol() {

	// --- Controller and motor setup ---
		pros::Controller master(pros::E_CONTROLLER_MASTER); // Controller setup

		// pros::ADIAnalogOut pneumatics (PNEUMATICS);	// PNEUMATICS setup

		// --- Motor setup ---
		pros::Motor left_mtr1(LEFT_MOTOR_1_PORT); 	// Left side motor
		pros::Motor right_mtr1(RIGHT_MOTOR_1_PORT); 	// Right side motor
		pros::Motor wheel_mtr(BAND_WHEEL_PORT);		// Wheel motor


		master.set_text(0, 0, "DLOW Best"); // useless



	while (true) { // Infinite loop while the opcontrol is running to refresh controller input and output it to the motors

		if (!(count % 10)) { // Run every 4th time the 20ms delay loop is ran
			// Only print every 60ms, the controller text update rate is slow
			}
			count++;


		// Read controller
			int left = master.get_analog(ANALOG_LEFT_Y);
			int right = master.get_analog(ANALOG_RIGHT_Y);
			bool buttonA = master.get_digital(DIGITAL_A);
			bool buttonX = master.get_digital(DIGITAL_X);

		if (buttonX) {



		}

		


		// Output to motors
			left_mtr1 = left;
			right_mtr1 = - right;
			wheel_mtr = buttonA;


		pros::delay(20); // This is required for the screen to function
	}
}
