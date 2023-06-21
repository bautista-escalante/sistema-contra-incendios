//Bautista Escalante
#include <LiquidCrystal.h>
#include <Servo.h>
#include <IRremote.h>
#define D4 5
#define D5 6
#define D6 7
#define D7 8
#define RS 10
#define E 9
#define rojo 13
#define verde 12
#define IR 2

bool activo = true;
Servo myservo;  
LiquidCrystal lcd(RS,E,D4,D5,D6,D7);// Inicializar el objeto LiquidCrystal
decode_results infrarrojo;

void EncenderDiodo(int led);
void OperarLcd(const char* estacion,int temp);
void CalcularEstacion(int temperatura);
void MoverServo(int grados);
void UsarControl();

void setup()
{
  // Inicializar el LCD con 2 columnas y 16 filas
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(rojo, OUTPUT);
  pinMode(verde, OUTPUT);
  myservo.attach(11);
  IrReceiver.begin(IR, ENABLE_LED_FEEDBACK);  // Iniciar el receptor IR
}

void loop()
{
  int sensor = analogRead(A0);
  int temperatura = map(sensor,20,358,-40,125);
  CalcularEstacion(temperatura);
}

void EncenderDiodo(int led)
{
  if(led==1){
  digitalWrite(rojo, LOW);
  digitalWrite(verde, HIGH);
  }
  else if(led==2){
  	digitalWrite(rojo, HIGH);
  	digitalWrite(verde, LOW);
  }
}
void CalcularEstacion(int temperatura)
{
	if (temperatura>=0 && temperatura<=10)
  {
    OperarLcd("invierno",temperatura);
    EncenderDiodo(1);
  }
  else	if (temperatura>=17 && temperatura<=24)
  {
    OperarLcd("primavera ",temperatura);
    EncenderDiodo(1);
  }
  else if (temperatura>=25 && temperatura<=45)
  {
    OperarLcd("verano ",temperatura);
    EncenderDiodo(1);
  }
    else if (temperatura>=11 && temperatura<=16)
  {
	OperarLcd("otonio",temperatura);
    EncenderDiodo(1);
  }
  else if(temperatura>=45 && activo==true)
  {
   EncenderDiodo(2);
   OperarLcd("INCENDIO ",temperatura);
   MoverServo(90);
   UsarControl();
  }
}

void OperarLcd(const char* estacion,int temp)
{
  lcd.print(estacion);
  lcd.setCursor(0, 1);
  lcd.print("temperatura: " + String(temp)+"c");
  delay(200); 
  lcd.clear();
  lcd.setCursor(0, 0);
}
void MoverServo(int grados)
{
  myservo.write(0); 
  delay(700);      
  myservo.write(grados); 
  delay(700);     
}
void UsarControl() {
  if (IrReceiver.decode()) {
      IrReceiver.resume();
    if(IrReceiver.decodedIRData.decodedRawData == 0xFF00BF00)
    {
      activo==false;
     Serial.print("apagado");
    }
    else if(IrReceiver.decodedIRData.decodedRawData == 0xFD02BF00)
    {
      activo==true;
     Serial.print("encendido"); 
    }
  }
}
