#include <ros.h>
#include <std_msgs/String.h>
#include <motor_control/motor_Values.h>
#include <sensor_msgs/BatteryState.h>
#include <Arduino.h>
#include <Servo.h>

#define LIMITER 250

#define ESC_MAX_F_VALUE 2000-LIMITER
#define ESC_MIN_F_VALUE 1528
#define ESC_MAX_R_VALUE 1000+LIMITER
#define ESC_MIN_R_VALUE 1478

ros::NodeHandle nh;
motor_control::motor_Values motor_values_msg;

Servo svfl;
Servo svfr;
Servo svbl;
Servo svbr;
Servo shfl;
Servo shfr;
Servo shbl;
Servo shbr;

int motor_map(int value) {
	if (value > ESC_MIN_F_VALUE) {
		return map(value, 0, 100, ESC_MIN_F_VALUE, ESC_MAX_F_VALUE);
	}
	else if (value < ESC_MIN_R_VALUE) {
		return map(value, 0, -100, ESC_MIN_R_VALUE, ESC_MAX_R_VALUE);
	}
	else {
		return 1500;
	}
}

void motor_Cb(const motor_control::motor_Values& data) {
	svfl.writeMicroseconds(motor_map(data.vrf));
	svfr.writeMicroseconds(motor_map(data.vlf));
	svbl.writeMicroseconds(motor_map(data.vrb));
	svbr.writeMicroseconds(motor_map(data.vlb));
	shfl.writeMicroseconds(motor_map(data.hrf));
	shfr.writeMicroseconds(motor_map(data.hlf));
	shbl.writeMicroseconds(motor_map(data.hrb));
	shbr.writeMicroseconds(motor_map(data.hlb));
}

ros::Subscriber<motor_control::motor_Values> sub("/thruster_values", &motor_Cb );

void setup()
{
	nh.initNode();
	nh.subscribe(sub);
	
	svfl.attach(2);
	svfr.attach(3);
	svbl.attach(4);
	svbr.attach(5);
	shfl.attach(6);
	shfr.attach(7);
	shbl.attach(8);
	shbr.attach(9);

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
	nh.spinOnce();
	delay(1);
}
