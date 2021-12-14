// Aplicación: Controlador_potonciometros_ros_arduino_mega
#include <ros.h>
#include <std_msgs/Int16.h>
#include <Servo.h>
ros::NodeHandle nh;
std_msgs::Int16 str_msg1,str_msg2,str_msg3,str_msg4,str_msg5,str_msg6;
ros::Publisher datos_servo1("datos1", &str_msg1);
ros::Publisher datos_servo2("datos2", &str_msg2);
ros::Publisher datos_servo3("datos3", &str_msg3);
ros::Publisher datos_servo4("datos4", &str_msg4);
ros::Publisher datos_servo5("datos5", &str_msg5);
ros::Publisher datos_servo6("datos6", &str_msg6);
void setup()
{
  nh.initNode();
  nh.advertise(datos_servo1);
  nh.advertise(datos_servo2);
  nh.advertise(datos_servo3);
  nh.advertise(datos_servo4);
  nh.advertise(datos_servo5);
  nh.advertise(datos_servo6);
}

void loop()
{
  int Value1 = analogRead(3);
  int Value2 = analogRead(4);
  int Value3 = analogRead(5);
  int Value4 = analogRead(6);
  int Value5 = analogRead(7);
  int Value6 = analogRead(8);
  Value1 = map(Value1, 0, 1023, 0, 180);
  Value2 = map(Value2, 0, 1023, 0, 180);
  Value3 = map(Value3, 0, 1023, 0, 180);
  Value4 = map(Value4, 0, 1023, 0, 180);
  Value5 = map(Value5, 0, 1023, 0, 180);
  Value6 = map(Value6, 0, 1023, 100, 179);
  str_msg1.data = Value1;
  datos_servo1.publish( &str_msg1 );
  str_msg2.data = Value2;
  datos_servo2.publish( &str_msg2 );
  str_msg3.data = Value3;
  datos_servo3.publish( &str_msg3 );
  str_msg4.data = Value4;
  datos_servo4.publish( &str_msg4 );
  str_msg5.data = Value5;
  datos_servo5.publish( &str_msg5 );
  str_msg6.data = Value6;
  datos_servo6.publish( &str_msg6 );
  nh.spinOnce();
  delay(60);
}
