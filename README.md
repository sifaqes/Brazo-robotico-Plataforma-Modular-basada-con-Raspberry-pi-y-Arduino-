# Proyecto Plataforma Modular Basada en RPi y Arduino (Brazo robotico con ROS)
Autor: Sifaqes Zerrouki.
Univrssidad de Alicante .
Escuela Superior Politécnica. 
Máster Universitario en Automática y Robótica.
Personal email:siphaxtfm@gmail.com

https://user-images.githubusercontent.com/64240372/145921452-13b28959-db05-458c-92cb-032f5368e480.mp4


![image](https://user-images.githubusercontent.com/64240372/145919115-a0a8b98a-b2bb-4938-9030-4f4bcfa72618.png)

# Resumen

•	Capítulo 1: Introducción 
	El primer capítulo presenta el alcance de este proyecto. Además, explica los problemas planteados y los objetivos deseados y los pasos que seguirán.

•	Capítulo 2: Preparación del entorno ROS para RPi.
	Preparamos lo necesario de la plataforma, así como las tarjetas el software y sus bibliotecas y paquetes del trabajo.

•	Capítulo 3: Diseño 3D de la plataforma modular.
	El tercer capítulo está reservado para el diseño la plataforma modular que desarrollaremos.

•	Capítulo 4: Un brazo desarrollado con la comunicación serial RPi y Arduino
	El tercer capítulo construimos un brazo 6DOF y detalla el proceso de desarrollar una comunicación serial entre la RPi y Arduino, es decir cómo se comunica entre ellos.

# 1-Introduccion
  Este proyecto pretende crear una plataforma modular basada en RPi y Arduino, en la que se conecten entre ellas con comunicación serial. El proyecto se puede probar en empresas emergentes de tecnología industrial que busquen una alternativa fácil, barata y de código abierto. 
Aunque estos robots en teoría están basados en diferentes lenguajes de programación y en consecuencia no sería posible de ninguna manera comunicarse entre ellos (así como Arduino y Python, por ejemplo) el gran reto en este trabajo es hacerlo posible mediante la instalación de diferentes robots que se controlen entre ellos gracias a la comunicación serial. Por otro lado, la plataforma tiene aplicación en las empresas agrícolas e industriales; desde un brazo robótico que hace un proceso de tratamiento de una cinta de producción de frutas o hasta un brazo robótico industrial que suelda   carrocería del coche.

![image](https://user-images.githubusercontent.com/64240372/145923710-1f90015d-1d6f-43d7-88a7-e2b4451928d1.png)

# Capítulo 2: Preparación del entorno ROS para RPi.
Para instalar la versión ROS kinetic tendremos iniciar sesión en RPi. Luego ejecute estos comandos para agregar el repositorio de paquetes ROS [2], construir herramientas e inicializar la herramienta de dependencia ROS .

	sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

	sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654

	sudo apt-get update

	sudo apt-get install -y python-rosdep python-rosinstall-generator python-wstool python-rosinstall build-essential cmake

	sudo rosdep init

	rosdep update

Creé un espacio de trabajo para construir ROS Kinetic desde la fuente.
	
	mkdir ~/ros_catkin_ws
	cd ~/ros_catkin_ws
	rosdep update
	
Despues Install el sistema:

	rosinstall_generator ros_comm --rosdistro kinetic --deps --wet-only --tar > kinetic-ros_comm-wet.rosinstall
	wstool init -j8 src kinetic-ros_comm-wet.rosinstall
	rosdep install --from-paths src --ignore-src --rosdistro kinetic -y


La construcción de ROS en este punto fallará con varios errores. Arreglemos esos errores editando manualmente el código fuente de ROS. Vamos a editar este fechero. Retomaremos este punto en el apartado de las conclusiones:

línea 885: enlace siguiente:

Creé un espacio de trabajo para construir ROS Kinetic desde la fuente.
	
	/home/pi/ros_catkin_ws/src/opencv3/modules/python/src2/cv2.cpp
Debemos reemplazar 
	
	char* str = PyString_AsString(obj);
con
	
	const char* str = PyString_AsString(obj);
A continuación, editamos los archivos.
	
	/home/pi/ros_catkin_ws/src/rospack/include/rospack/rospack.h 
	/home/pi/ros_catkin_ws/src/rospack/src/rospack.cpp 
	/home/pi/ros_catkin_ws/src/rospack/src/utils.cpp
	
Eliminamos todas las apariciones de
	
	/tr1
Y reemplazamos todas las apariciones de
	
	std::tr1
con
	
	boost
Editamos los archivos a continuación.
	
	/home/pi/ros_catkin_ws/src/actionlib/include/actionlib/client/simple_action_client.h
	/home/pi/ros_catkin_ws/src/actionlib/include/actionlib/destruction_guard.h /home/pi/ros_catkin_ws/src/actionlib/include/actionlib/server/simple_action_server_imp.h 
	/home/pi/ros_catkin_ws/src/actionlib/src/connection_monitor.cpp /home/pi/ros_catkin_ws/src/actionlib/test/destruction_guard_test.cpp
	/home/pi/ros_catkin_ws/src/bond_core/bondcpp/src/bond.cpp /home/pi/ros_catkin_ws/src/ros_comm/roscpp/include/ros/timer_manager.h
	/home/pi/ros_catkin_ws/src/ros/roslib/test/utest.cpp
	
Reemplazamos todas las apariciones de todos los archivos cada uno manualmente.
	
	boost::posix_time::milliseconds(…)
con:
	
	boost::posix_time::milliseconds(int(…))
Y editamos el archivo a continuación.
	
	/home/pi/ros_catkin_ws/src/geometry2/tf2/src/buffer_core.cpp
Debemos Reemplazamos  
	
	logWarn
con:
	
	CONSOLE_BRIDGE_logWarn
Y reemplazamos 
	
	logError
con:
	
	CONSOLE_BRIDGE_logError
Ahora, se construye ROS Kinetic en este punto, la compilación debería realizarse correctamente.
	
	cd ~/ros_catkin_ws
	sudo ./src/catkin/bin/catkin_make_isolated --install -DCMAKE_BUILD_TYPE=Release --install-space /opt/ros/kinetic
Agregamos a ~ / .bashrc y también ejecutamos en su Shell:
	
	source /opt/ros/kinetic/setup.bash
o puede usar esto:
	
	source /opt/ros/kinetic/setup.bash


![image](https://user-images.githubusercontent.com/64240372/145917627-1a341d6c-97ce-4033-819f-19d763b01995.png)

# Capítulo 3: Diseño 3D de la plataforma modular
  Para el modelado paramétrico usaremos FreeCAD con licencia de código abierto, con el objetivo de diseñar una caja que necesitaríamos para la RPi y Arduino Mega y Arduino Uno. Esto nos permitirá diseñar una plataforma modular 3D, compatible con los tres modelos [4]. 

![image](https://user-images.githubusercontent.com/64240372/145917933-2a781c5c-3e4f-42fb-aeef-49c1be5ed71e.png)

# Capítulo 4: Desarrollar un Brazo serial RPi y Arduino

4.1.	Circuito de alimentación
	Es muy fácil controlar el servomotor directamente desde el Arduino. Sin embargo, el servomotor puede requerir más corriente de la que puede proporcionar Arduino. El siguiente ejemplo utiliza un servomotor que recibe corriente directamente del Arduino a través de USB.
	
  	![image](https://user-images.githubusercontent.com/64240372/145918058-d5938eb4-3e8f-4ec3-9c25-2ac4de9d1924.png)
  	![image](https://user-images.githubusercontent.com/64240372/145918220-b82bf293-8780-48eb-bbcf-7bba9fd7a1bc.png)
  
4.2.	 Estudiar las entradas y salidas
	En este paso, construimos un circuito de control que permite a transmitir datos a nuestra Nodo de ROS, Así pues, el circuito tiene seis potenciómetros de resistencia 1k que varía la señal entre 0 ° y180 °, Lo hacemos una simulación diagrama en ISIS.
	
  	![image](https://user-images.githubusercontent.com/64240372/145918294-eeacaf18-3cd9-4bce-bff1-48f1e4f0c340.png)
	![image](https://user-images.githubusercontent.com/64240372/145918310-55ae1444-5676-4762-aa30-bdec02dfc2ab.png)
  
  Además, creamos un archivo que se acaba con .launch y construimos el script siguiente, Así pues, se ejecuta el ROS y llama a dos Nodos diferente al mismo tiempo y abre dos puertos seriales vincula con el maestro:


# Para Ejecutar el programa abrimos:

Paso1: Despues crear un pacakge ros sellama brazo_serial, despuies ejecutar el  nodo de Arduino uno y mega con roslaunch archivo  
	
	$ roscd brazo_serial
	$ roslaunch brazo_serial arduino.launch

Paso2:ejecutar la nudo de RPi
	
	$ python arduino.python

Paso3:lista de topicos y nodos
	
	$ rosnode list 
	$ rostopic list 

Paso4:escuchar mensajes de resuesta
	
	$ rostopic echo monitor_de_control



# Bibliografía
RPi: Raspberry Pi4


