/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.

 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {
//	lcdPrint(uart1, 1, "test");
	//bettergame();
	TaskHandle UPDATE = taskRunLoop(update, 10);
	TaskHandle LCDDEBUG = taskRunLoop(LCDDebugScreens, 10);
	while (1) {
		drive(joystickGetAnalog(1, 3), joystickGetAnalog(1, 2));
  	mogo(-127 * (joystickGetDigital(1, 5, JOY_UP) - joystickGetDigital(1, 5, JOY_DOWN)));
    lift(127 * (joystickGetDigital(1, 6, JOY_UP) - joystickGetDigital(1, 6, JOY_DOWN)));
    secondaryLift(127 * (joystickGetDigital(1, 8, JOY_UP) - joystickGetDigital(1, 8, JOY_DOWN)));
		if(joystickGetDigital(1, 7, JOY_UP)){roller(50);}
		else if(joystickGetDigital(1, 7, JOY_DOWN)){roller(-100);}
		else{roller(15);}
	delay(20);
	}
	//taskDelete(UPDATE);
	taskDelete(LCDDEBUG);
}