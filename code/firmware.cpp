#include <ros.h>
#include <std_msgs/String.h>
#include <motor_control/motor_Values.h>
#include <sensor_msgs/BatteryState.h>
#include <Arduino.h>
#include <Servo.h>

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

void motor_Cb(const motor_control::motor_Values& data) {
	svfl.writeMicroseconds(data.vrf);
	svfr.writeMicroseconds(data.vlf);
	svbl.writeMicroseconds(data.vrb);
	svbr.writeMicroseconds(data.vlb);
	shfl.writeMicroseconds(data.hrf);
	shfr.writeMicroseconds(data.hlf);
	shbl.writeMicroseconds(data.hrb);
	shbr.writeMicroseconds(data.hlb);
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
}

void loop()
{
	nh.spinOnce();
	delay(1);
}
