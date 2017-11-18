# Robot_Coche-Arduino

# Descripción
Proyecto en el cual he realizado un coche bimotor en arduino el cual puede detectar obstáculos cercanos.
Internamente es un agente con 3 estados por los que va pasando según los obstáculos que detecte con su módulo ultrasónico(mu).

Los estados son:
* **Detectando obstáculos** :En el cual interviene un servomotor y el mu.El servomotor cambia de ángulo al mu para que este pueda detectar los obstaculos a una distancia de 25cm
* **Acelerando**: Si el robot no detecta obstáculos acelera durante un determinado periodo de tiempo.
* **Girando**: Si detecta obstáculo gira hacia la derecha o izquierda según donde se haya detectado dicho obstáculo.
# Componentes
Para este diseño necesitaremos:
* Servomotor
* Módulo Ultrasónico
* Módulo potenciador L298N
* Placa arduino UNO
* Dos motores de CC
* Chasis con dos ruedas
* Pila de 9v
* 4 pilas de 1.5v

# Diseño
El diseño del proyecto se puede ver en la siguiente imagen

![design](https://github.com/Antoniolm/Robot_Coche-Arduino/blob/master/Dise%C3%B1o/Dise%C3%B1oV2/Dise%C3%B1oElectronico_v2.png)

### Licencia

 Este proyecto ha sido liberado bajo la licencia [GNU GLP V3](https://github.com/Antoniolm/Robot_Coche-Arduino/blob/master/LICENSE)
