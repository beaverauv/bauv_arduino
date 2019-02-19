#include <ros.h>
#include <std_msgs/String.h>
#include <bauv_motor_control/motor_Values.h>
#include <Arduino.h>
#include <Servo.h>

ros::NodeHandle nh;
bauv_motor_control::motor_Values motor_values_msg;

void motor_Cb(const bauv_motor_control::motor_Values& data) {

}

ros::Subscriber<bauv_motor_control::motor_Values> sub("/thruster_values", &motor_Cb );

void setup()
{
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
