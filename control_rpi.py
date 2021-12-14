import rospy
from std_msgs.msg import Int16
from std_msgs.msg import String
def callback1(data1):
    rospy.loginfo(" La valor recibe por Servo1 es :   %s ", data1.data)
    pub1 = rospy.Publisher('servo1', Int16, queue_size=1)
    pub1.publish(data1.data)
def callback2(data2):
    rospy.loginfo(" La valor recibe por Servo2 es :   %s ", data2.data)
    pub2 = rospy.Publisher('servo2', Int16, queue_size=1)
    pub2.publish(data2.data)
def callback3(data3):
    rospy.loginfo(" La valor recibe por Servo3 es :   %s ", data3.data)
    pub3 = rospy.Publisher('servo3', Int16, queue_size=1)
    pub3.publish(data3.data)
def callback4(data4):
    rospy.loginfo(" La valor recibe por Servo4 es :   %s ", data4.data)
    pub4 = rospy.Publisher('servo4', Int16, queue_size=1)
    pub4.publish(data4.data)
def callback5(data5):
    rospy.loginfo(" La valor recibe por Servo5 es :   %s ", data5.data)
    pub5 = rospy.Publisher('servo5', Int16, queue_size=1)
    pub5.publish(data5.data)
def callback6(data6):
    rospy.loginfo(" La valor recibe por Servo6 es :   %s ", data6.data)
    pub6 = rospy.Publisher('servo6', Int16, queue_size=1)
    pub6.publish(data6.data)
def answer(data):
    rospy.loginfo(" x  :   %s ", data.data)
    pub7 = rospy.Publisher('monitor_de_control', String, queue_size=10)
    pub7.publish(data.data)
def nodo_python():
    rospy.init_node('nodo_rpi', anonymous=False)
    rospy.Subscriber("datos1", Int16,callback1,queue_size=1)
    rospy.Subscriber("datos2", Int16,callback2,queue_size=1)
    rospy.Subscriber("datos3", Int16,callback3,queue_size=1)
    rospy.Subscriber("datos4", Int16,callback4,queue_size=1)
    rospy.Subscriber("datos5", Int16,callback5,queue_size=1)
    rospy.Subscriber("datos6", Int16,callback6,queue_size=1)
    rospy.Subscriber("answer", String,answer,queue_size=1)
    print("Bienvenido a aplicacion de nodo de RPi")
    rospy.spin()
    print("Adios (*_*)")
if __name__ == '__main__':
    nodo_python()
