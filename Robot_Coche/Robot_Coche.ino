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

//Servo que movera nuestro ultrasonico para detectar todos los obstaculos
Servo servo;

int angle=-10;
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
  //Reinicio del servo
  if(angle==60){
    angle=-10;
  }
  //Detectamos obstaculos 
  distancia=detectarDistanciaObstaculo();
  
  //Si no tiene cercanos (50cm) 
  //Caso -distancia se tienen en cuenta por fallos de lectura de
  //nuestro sensor ultrasonico
  if(estaGirando && (distancia >50 || distancia < 0)){
    // Motor va hacia delante
    digitalWrite (IN4, HIGH);
    digitalWrite (IN6, HIGH); 
    estaGirando=false; 
  }
  else if(distancia>0 && distancia<=50){ //Si tenemos un obstaculo a menos de 50cm
  
    estaGirando=true;
    
    girarDerecha();
    buscarObstaculo();
  
  }
  //Movemos el servo 10º mas
  angle=angle+10;
  servo.write(angle);
  delay(200);
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
void girarAtras(){
    //Motor gira hacia la derecha
    digitalWrite (IN3, LOW);
    digitalWrite (IN4, HIGH);   
    digitalWrite (IN5, HIGH);
    digitalWrite (IN6, LOW);
    delay(500);

    //Detenemos el giro 
    digitalWrite (IN4, LOW);   
    digitalWrite (IN5, LOW);
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

void buscarObstaculo(){
  int angleBusqueda=10;
  int dist;
  boolean ladoDerecha=false ,ladoIzquierdo=false;
  while(angleBusqueda<50){
    //Posicionamos nuestro servo
    servo.write(angleBusqueda);
    dist=detectarDistanciaObstaculo(); //detectamos obstaculos
    
    if(distancia>0 && distancia<=50){
      if(angleBusqueda>=10 && angleBusqueda<=20){
        girarDerecha();
      }
      else if(angleBusqueda>20 && angleBusqueda<=40){
        //int rand=random(0,2);
        //if(rand==0) girarDerecha();
        //else 
        girarIzquierda();
      }
      /*else if(angleBusqueda>40 && angleBusqueda<=60){
        girarIzquierda();
      }*/
      
    }
    
    //Aumentamos el angulo
    angleBusqueda=angleBusqueda+10;
    delay(200);
  }
  
}


