cmake_minimum_required(VERSION 2.8.3)
project(bauv_arduino)

#find_package(catkin REQUIRED
#  rosserial_arduino
#  rosserial_client
#  bauv_motor_control
#  std_msgs
#)


find_package(catkin REQUIRED COMPONENTS
  rosserial_arduino
  rosserial_client
  motor_control
  std_msgs
  message_generation
)

#add_executable(firmware code/firmware.cpp)
#add_dependencies(firmware ${catkin_EXPORTED_TARGETS})


generate_messages()

#catkin_package()
catkin_package(
#  CATKIN_DEPENDS message_runtime bauv_motor_control std_msgs
)

include_directories(${catkin_INCLUDE_DIRS})

rosserial_generate_ros_lib(
  PACKAGE rosserial_arduino
  SCRIPT make_libraries.py
)

rosserial_configure_client(
  DIRECTORY code
  TOOLCHAIN_FILE ${ROSSERIAL_ARDUINO_TOOLCHAIN}
)

rosserial_add_client_target(code firmware ALL)
rosserial_add_client_target(code firmware-upload)



