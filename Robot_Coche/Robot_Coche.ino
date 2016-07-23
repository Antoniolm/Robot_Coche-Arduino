int IN3 = 5; 
int IN4 = 4;
int IN5 = 6;
int IN6 = 7;
void setup()
{
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);    
  pinMode (IN5, OUTPUT);
  pinMode (IN6, OUTPUT); 
}
void loop()
{
  // Motor va hacia delante
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  digitalWrite (IN5, LOW);
  digitalWrite (IN6, HIGH);  
  delay(1500);
  // Motor no gira
  digitalWrite (IN4, LOW); 
  digitalWrite (IN6, LOW); 
  delay(500);
  //Motor gira hacia la derecha
  digitalWrite (IN3, HIGH); 
  digitalWrite (IN6, HIGH);
  delay(250); 
  
  // Motor gira en sentido inverso
  //digitalWrite (IN4, HIGH);
  //digitalWrite (IN6, HIGH);
  //delay(2000);
  
  // Motor no gira
  digitalWrite (IN3, LOW);
  digitalWrite (IN6, LOW); 
  //digitalWrite (IN6, LOW); 
  delay(500);
}
