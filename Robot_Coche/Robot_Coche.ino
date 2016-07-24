///////////////////////////////////////////////////////////
//
//@author Antonio David Lopez Machado
//
////////////////////////////////////////////////////////

//Clavijas a la que esta conectado el potenciador L298N
int IN3 = 5; 
int IN4 = 4;
int IN5 = 6;
int IN6 = 7;

//Clavijas a las que esta conectado el modulo ultrasonico
int PIN_TRIG=12;
int PIN_ECO=13;

int duracion=0;
int distancia=0;

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

}

//////////////////////////////
//Bucle de acciones del Robot
//////////////////////////////
void loop()
{
  //Hacemos el disparo 
  digitalWrite(PIN_TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG,LOW);


  //Recibimos el disparo 
  duracion=pulseIn(PIN_ECO,HIGH);
  //Realizamos el calculo en cm
  distancia=(duracion/2)/29;
  
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
    
    //Detenemos su movimiento hacia delante
    digitalWrite (IN4, LOW);
    digitalWrite (IN6, LOW);  
  
    //Motor gira hacia la derecha
    digitalWrite (IN3, HIGH);   
    digitalWrite (IN6, HIGH);
    delay(250);
    
    //Detiene su giro
    digitalWrite (IN3, LOW);   
    digitalWrite (IN6, LOW);
  
  }
}
