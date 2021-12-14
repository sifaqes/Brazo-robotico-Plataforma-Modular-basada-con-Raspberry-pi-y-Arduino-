//Aplicacion de control brazo ros arduino uno
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif
#include <Servo.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/String.h>
ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher datos_answer("answer", &str_msg);
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
char max[35] = "El servo llega al estado maximo";
char min[35] = "El servo llega al estado minimo";
char medio[35] = "El servo llega al estado activo";
void servo1_cb( const std_msgs::Int16& cmd_msg) {
  servo1.write(cmd_msg.  data);
  if (cmd_msg.  data == 0  ) {
    str_msg.data = "s1 minimo";
    datos_answer.publish( &str_msg );
  }
  if (cmd_msg.  data > 0 and cmd_msg.  data < 180 ) {
    str_msg.data = "s1 activo";
    datos_answer.publish( &str_msg );
  }
  if (cmd_msg.  data == 180 ) {
    str_msg.data = "s1 maximo";
    datos_answer.publish( &str_msg );
  }
}
void servo2_cb( const std_msgs::Int16& cmd_msg) {
  servo2.write(cmd_msg.  data);
  if (cmd_msg.  data == 0  ) {
    str_msg.data = "s2 minimo";
    datos_answer.publish( &str_msg );
  }
  if (cmd_msg.  data > 0 and cmd_msg.  data < 180 ) {
    str_msg.data = "s2 activo";
    datos_answer.publish( &str_msg );
  }
  if (cmd_msg.  data == 180 ) {
    str_msg.data = "s2 maximo";
    datos_answer.publish( &str_msg );
  }
}
void servo3_cb( const std_msgs::Int16& cmd_msg) {
  servo3.write(cmd_msg.  data);
  if (cmd_msg.  data == 0  ) {
    str_msg.data = "s3 minimo";
    datos_answer.publish( &str_msg );
  }
  if (cmd_msg.  data > 0 and cmd_msg.  data < 180 ) {
    str_msg.data = "s3 activo";
    datos_answer.publish( &str_msg );
  }
  if (cmd_msg.  data == 180 ) {
    str_msg.data = "s3 maximo";
    datos_answer.publish( &str_msg );
  }
}
void servo4_cb( const std_msgs::Int16& cmd_msg) {
  servo4.write(cmd_msg.  data);

  if (cmd_msg.  data == 0  ) {
    str_msg.data = "s4 minimo";
    datos_answer.publish( &str_msg );
  }
  if (cmd_msg.  data > 0 and cmd_msg.  data < 180 ) {
    str_msg.data = "s4  activo";
    datos_answer.publish( &str_msg );
  }
  if (cmd_msg.  data == 180 ) {
    str_msg.data = "s4 maximo";
    datos_answer.publish( &str_msg );
  }
}
void servo5_cb( const std_msgs::Int16& cmd_msg) {
  servo5.write(cmd_msg.  data);

  if (cmd_msg.  data == 0  ) {
    str_msg.data = "s5 minimo";
    datos_answer.publish( &str_msg );
  }
  if (cmd_msg.  data > 0 and cmd_msg.  data < 180 ) {
    str_msg.data = "s5 activo";
    datos_answer.publish( &str_msg );
  }
  if (cmd_msg.  data == 180 ) {
    str_msg.data = "s5 maximo ";
    datos_answer.publish( &str_msg );
  }
}
void servo6_cb( const std_msgs::Int16& cmd_msg) {
  servo6.write(cmd_msg.  data);

  if (cmd_msg.  data == 100  ) {
    str_msg.data = "s6 minimo";
    datos_answer.publish( &str_msg );
  }
  if (cmd_msg.  data > 100 and cmd_msg.  data < 179 ) {
    str_msg.data = "s6 activo";
    datos_answer.publish( &str_msg );
  }
  if (cmd_msg.  data == 179 ) {
    str_msg.data = "s6 maximo ";
    datos_answer.publish( &str_msg );
  }
}
ros::Subscriber<std_msgs::Int16> sub1("servo1", servo1_cb);
ros::Subscriber<std_msgs::Int16> sub2("servo2", servo2_cb);
ros::Subscriber<std_msgs::Int16> sub3("servo3", servo3_cb);
ros::Subscriber<std_msgs::Int16> sub4("servo4", servo4_cb);
ros::Subscriber<std_msgs::Int16> sub5("servo5", servo5_cb);
ros::Subscriber<std_msgs::Int16> sub6("servo6", servo6_cb);
void setup() {
  pinMode(13, OUTPUT);
  int answer = 100;
  nh.initNode();
  nh.advertise(datos_answer);
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
  nh.subscribe(sub5);
  nh.subscribe(sub6);
  servo1.attach(11);
  servo2.attach(10);
  servo3.attach(9);
  servo4.attach(6);
  servo5.attach(5);
  servo6.attach(3);
}
void loop() {
  nh.spinOnce();
}