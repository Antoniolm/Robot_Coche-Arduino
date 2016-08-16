# Robot_Coche-Arduino

#Descripción
Proyecto en el cual he realizado un coche bimotor en arduino el cual puede detectar obstáculos cercanos.
Internamente es un agente con 3 estados por los que va pasando según los obstáculos que detecte con su módulo ultrasónico(mu).<br>
Los estados son:<br>
-<strong>Detectando obstáculos</strong>:En el cual interviene un servomotor y el mu.El servomotor cambia de ángulo al mu para que este pueda detectar los obstaculos a una distancia de 25cm<br>
-<strong>Acelerando</strong>: Si el robot no detecta obstáculos acelera durante un determinado periodo de tiempo.<br>
-<strong>Girando</strong>: Si detecta obstáculo gira hacia la derecha o izquierda según donde se haya detectado dicho obstáculo.<br>
#Componentes
Para este diseño necesitaremos<br>
-Servomotor<br>
-Módulo Ultrasónico<br>
-Módulo potenciador L298N<br>
-Placa arduino UNO<br>
-Dos motores de CC<br>
-Chasis con dos ruedas<br>
-Pila de 9v<br>
-4 pilas de 1.5v<br>
