Plataforma Modular Basada en RPi y Arduino

Autor:
Sifaqes Zerrouki
![image](https://user-images.githubusercontent.com/64240372/145916512-f5b0eb46-d80b-48e6-a629-27b729190055.png)
















Open LXTerminal en Raspberry Pi

Paso1
roscd brazo_serial
roslaunch brazo_serial arduino.launch

Paso2:
python arduino.python

Paso3:
rosnode list 
rostopic list 

Paso4:
rostopic echo monitor_de_control
