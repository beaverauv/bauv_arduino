#include <ros.h>
#include <std_msgs/String.h>
#include <motor_control/motor_Values.h>
#include <sensor_msgs/BatteryState.h>
#include <std_msgs/Bool.h>
#include <Arduino.h>
#include <Servo.h>

#define LIMITER 250

#define ESC_MAX_F_VALUE 2000-LIMITER
#define ESC_MIN_F_VALUE 1528 //1528
#define ESC_MAX_R_VALUE 1000+LIMITER
#define ESC_MIN_R_VALUE 1480 //1478

//hall effect connected to A0

bool flag = true;
bool motor_enabled = true;

ros::NodeHandle nh;
motor_control::motor_Values motor_values_msg;
std_msgs::Bool bool_msg;

ros::Publisher motor_enabler("motor_enabled", &bool_msg);

Servo svfl;
Servo svfr;
Servo svbl;
Servo svbr;
Servo shfl;
Servo shfr;
Servo shbl;
Servo shbr;

int motor_map(int value) {
	value = value * -1;

	if (value > 0) {
		return map(value, 0, 100, ESC_MIN_F_VALUE, ESC_MAX_F_VALUE);
	}
	else if (value < 0) {
		return map(value, 0, -100, ESC_MIN_R_VALUE, ESC_MAX_R_VALUE);
	}
	else {
		return 1500;
	}
}

void motor_Cb(const motor_control::motor_Values& data) {
	if (motor_enabled == true) {
		svfl.writeMicroseconds(motor_map(data.vlf));
		svfr.writeMicroseconds(motor_map(data.vrf));
		svbl.writeMicroseconds(motor_map(data.vlb));
		svbr.writeMicroseconds(motor_map(data.vrb));
		shfl.writeMicroseconds(motor_map(data.hlf));
		shfr.writeMicroseconds(motor_map(data.hrf));
		shbl.writeMicroseconds(motor_map(data.hlb));
		shbr.writeMicroseconds(motor_map(data.hrb));
	}
	else {
                svfl.writeMicroseconds(1500);
                svfr.writeMicroseconds(1500);
                svbl.writeMicroseconds(1500);
                svbr.writeMicroseconds(1500);
                shfl.writeMicroseconds(1500);
                shfr.writeMicroseconds(1500);
                shbl.writeMicroseconds(1500);
                shbr.writeMicroseconds(1500);
	}
}

ros::Subscriber<motor_control::motor_Values> sub("/thruster_values", &motor_Cb );

void setup() {
	nh.initNode();
	nh.subscribe(sub);
	nh.advertise(motor_enabler);

	svfl.attach(6);
	svfr.attach(4);
	svbl.attach(8);
	svbr.attach(3);
	shfl.attach(7);
	shfr.attach(5);
	shbl.attach(9);
	shbr.attach(2);

	svfl.writeMicroseconds(1500);
        svfr.writeMicroseconds(1500);
        svbl.writeMicroseconds(1500);
        svbr.writeMicroseconds(1500);
        shfl.writeMicroseconds(1500);
        shfr.writeMicroseconds(1500);
        shbl.writeMicroseconds(1500);
        shbr.writeMicroseconds(1500);
	delay(100);
}

void loop()
{
	int detectValue = abs(analogRead(A0)-515);
	
	if (detectValue > 50) {
		if (flag == false) {
			motor_enabled = true;

			bool_msg.data = motor_enabled;
		        motor_enabler.publish(&bool_msg);

			flag = true;
		}
	}
	else {
		if (flag == true) {
			motor_enabled = false;

			svfl.writeMicroseconds(1500);
	                svfr.writeMicroseconds(1500);
        	        svbl.writeMicroseconds(1500);
			svbr.writeMicroseconds(1500);
                	shfl.writeMicroseconds(1500);
                	shfr.writeMicroseconds(1500);
                	shbl.writeMicroseconds(1500);
                	shbr.writeMicroseconds(1500);

			bool_msg.data = motor_enabled;
		        motor_enabler.publish(&bool_msg);

			flag = false;
		}
	}

	nh.spinOnce();
	delay(1);
}
