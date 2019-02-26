#include <ros.h>
#include <std_msgs/String.h>
#include <bauv_motor_control/motor_Values.h>
#include <sensor_msgs/BatteryState.h>
#include <Arduino.h>
#include <Servo.h>

ros::NodeHandle nh;
bauv_motor_control::motor_Values motor_values_msg;

Servo vfl;
Servo vfr;
Servo vbl;
Servo vbr;
Servo hfl;
Servo hfr;
Servo hbl;
Servo hbr;

void motor_Cb(const bauv_motor_control::motor_Values& data) {
	vfl.writeMicroseconds(data.vfl);
	vfr.writeMicroseconds(data.vfr);
	vbl.writeMicroseconds(data.vbl);
	vbr.writeMicroseconds(data.vbr);
	hfl.writeMicroseconds(data.hfl);
	hfr.writeMicroseconds(data.hfr);
	hbl.writeMicroseconds(data.hbl);
	hbr.writeMicroseconds(data.hbr);
}

ros::Subscriber<bauv_motor_control::motor_Values> sub("/thruster_values", &motor_Cb );

void setup()
{
	nh.initNode();
	nh.subscribe(sub);
	
	vfl.attach(2);
	vfr.attach(3);
	vbl.attach(4);
	vbr.attach(5);
	hfl.attach(6);
	hfr.attach(7);
	hbl.attach(8);
	hbr.attach(9);
}

void loop()
{
	nh.spinOnce();
	delay(1);
}
