///////////////////////////////////////////////////////////
//
//@author Antonio David Lopez Machado
//
////////////////////////////////////////////////////////

int IN3 = 5; 
int IN4 = 4;
int IN5 = 6;
int IN6 = 7;

int PIN_TRIG=12;
int PIN_ECO=13;

int duracion=0;
int distancia=0;

void setup()
{
  
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);    
  pinMode (IN5, OUTPUT);
  pinMode (IN6, OUTPUT); 
  
  pinMode(PIN_TRIG,OUTPUT);
  pinMode(PIN_ECO,INPUT);

}
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
  
  //Reiniciamos los valores
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
  digitalWrite (IN5, LOW);
  digitalWrite (IN6, LOW);  
  delay(200);
  
  //Si no tiene cercanos (50cm) 
  if(distancia >50 || distancia < 0){
    // Motor va hacia delante
    digitalWrite (IN4, HIGH);
    digitalWrite (IN6, HIGH);  
    delay(500);
  }
  else { //Si tenemos un obstaculo a menos de 50cm
    //Motor gira hacia la derecha
    digitalWrite (IN3, HIGH);   
    digitalWrite (IN6, HIGH);
    delay(200);
  
  }
}
