///////////////////////////////////////////////////////////
//
//@author Antonio David Lopez Machado
//
////////////////////////////////////////////////////////
#include <Servo.h>

//Clavijas a la que esta conectado el potenciador L298N
int IN3 = 5; 
int IN4 = 4;
int IN5 = 6;
int IN6 = 7;

//Clavijas a las que esta conectado el modulo ultrasonico
int PIN_TRIG=12;
int PIN_ECO=13;

int distancia=0;

//Enum para la alida de buscarObstaculo
enum salidaComprobacion{   noGiro,  giroDerecha,   giroIzquierda };

//Definimos buscaObstaculo con return enum
salidaComprobacion buscarObstaculo();

//Creamos un objeto salidaComprobacion
salidaComprobacion giro=noGiro;

//Creamos el enum de estados 
enum Estado {
  detectandoObstaculos, //Estado para que el robot compruebe su alrededor
  girando, //Estado para cuando el robot necesite girar
  acelerando //EStado para cuando el robot vaya en linea recta

};

//Creamos un objeto de enum estados
Estado state=detectandoObstaculos;

//Servo que movera nuestro ultrasonico para detectar todos los obstaculos
Servo servo;

int angle=0;
//Boolean para saber cuando hace falta ir hacia delante o girar
boolean estaGirando=true;

////////////
//Inicializamos los valores de los pin
///////////
void setup()
{
  //Configuramos los pins del L298N
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);    
  pinMode (IN5, OUTPUT);
  pinMode (IN6, OUTPUT); 
  
  //Configuramos los pins del modulo ultrasonico
  pinMode(PIN_TRIG,OUTPUT);
  pinMode(PIN_ECO,INPUT);
  
   servo.attach(11);
}

//////////////////////////////
//Bucle de acciones del Robot
//////////////////////////////
void loop()
{
  
  switch(state){
  
    /////////////////////////
    //Despues de realizar un giro entramos en este estado en el cual se realiza un sondeo
    //de obstaculos con el robot parado. En este sondeo se comprueba en que angulos hay obstaculos
    //y se selecciona una posicion de giro. En el caso de no existir obstaculo alguno el robot 
    //pasara al estado acelerando
    ////////////////////////
    case detectandoObstaculos:
        giro=buscarObstaculo();
        if(giro!=noGiro)
          state=girando;//cambiamos estado
        else
          state=acelerando; 
          
    break;
    
    /////////////////////////
    //
    //
    ////////////////////////
    case acelerando:
        // Motor va hacia delante

        estaGirando=false; 
        acelerar();
        //Cambiamos de estado
        state=detectandoObstaculos;
        //Reiniciamos el angulo del servo
    break;
    
    /////////////////////////
    //
    //
    ////////////////////////
    case girando:
        estaGirando=true;
        if(giro==giroDerecha)
            girarDerecha();
        else
            girarIzquierda();
        state=detectandoObstaculos;
    
    break;
  
  
  
  };
  
}

/**
*  Metodo para girar hacia la derecha el robot
*
*/
void girarDerecha(){
    //Motor gira hacia la derecha
    digitalWrite (IN3, HIGH);
    digitalWrite (IN4, LOW);   
    digitalWrite (IN5, LOW);
    digitalWrite (IN6, HIGH);
    delay(250);

    //Detenemos el giro 
    digitalWrite (IN3, LOW);   
    digitalWrite (IN6, LOW);
   
}


/**
*  Metodo para girar hacia la izquierda el robot
*
*/
void girarIzquierda(){
    //Motor gira hacia la derecha
    digitalWrite (IN3, LOW);
    digitalWrite (IN4, HIGH);   
    digitalWrite (IN5, HIGH);
    digitalWrite (IN6, LOW);
    delay(250);

    //Detenemos el giro 
    digitalWrite (IN4, LOW);   
    digitalWrite (IN5, LOW);
}

/**
*  Metodo para girar 180grados el robot
*
*/
void acelerar(){
    //Motor acelera
    digitalWrite (IN3, LOW);
    digitalWrite (IN4, HIGH);
    digitalWrite (IN3, LOW);
    digitalWrite (IN6, HIGH); 
    delay(400);

    //Detenemos la aceleracion 
    digitalWrite (IN4, LOW);   
    digitalWrite (IN6, LOW);
}
/**
*  Metodo que nos permite saber la distancia a la que se encuentra nuestro obstaculo
*
*/
int detectarDistanciaObstaculo(){
  int salida,duracion;
  //Hacemos el disparo 
  digitalWrite(PIN_TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG,LOW);


  //Recibimos el disparo 
  duracion=pulseIn(PIN_ECO,HIGH);
  //Realizamos el calculo en cm
  salida=(duracion/2)/29;
  
  return salida;
}

/**
*  Metodo que nos permite realizar una busqueda completa de obstaculos despues de realizar un giro
*  para asi detectar los obstaculos
*
*/

salidaComprobacion buscarObstaculo(){
  int angleBusqueda=45;
  int dist;
  salidaComprobacion salida=noGiro;
  boolean ladoDerecho=false ,ladoIzquierdo=false;
  while(angleBusqueda<=135){
    //Posicionamos nuestro servo
    servo.write(angleBusqueda);
    dist=detectarDistanciaObstaculo(); //detectamos obstaculos
    
    if(distancia>0 && distancia<=25){ //Si hay obstaculo
      //Comprobamos si es el lado derecho
      if(angleBusqueda>=10 && angleBusqueda<=20){
        ladoDerecho=true;
      }//O si es el lado izquierdo
      else if(angleBusqueda>20 && angleBusqueda<=40){
        ladoIzquierdo=true;
      }      
    }
    
    //Aumentamos el angulo
    angleBusqueda=angleBusqueda+10;
    delay(200);
  }
  //Segun que lados haya detectado realizamos un giro u otro
  if(ladoDerecho && ladoIzquierdo){
     int rand=random(0,2);
     if(rand==0)girarDerecha();
     else girarIzquierda();
  }
  else if(ladoDerecho) girarIzquierda();
  else if(ladoIzquierdo) girarDerecha();
      
  return salida;
  
}


