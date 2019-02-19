cmake_minimum_required(VERSION 2.8.3)
project(bauv_arduino)

find_package(catkin REQUIRED COMPONENTS
  rosserial_arduino
  rosserial_client
  bauv_motor_control
  std_msgs
)

rosserial_generate_ros_lib(
  PACKAGE rosserial_arduino
  SCRIPT make_libraries.py
)

generate_messages(
   DEPENDENCIES
   std_msgs
   bauv_motor_control
)

rosserial_configure_client(
  DIRECTORY code
  TOOLCHAIN_FILE ${ROSSERIAL_ARDUINO_TOOLCHAIN}
)

rosserial_add_client_target(code firmware ALL)
rosserial_add_client_target(code firmware-upload)



