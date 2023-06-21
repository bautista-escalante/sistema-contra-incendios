# sistema contra incendios
El objetivo de este proyecto es diseñar un sistema de incendio utilizando Arduino que puedadetectar cambios de temperatura y activar un servo motor en caso de detectar un incendio.Además, se mostrará la temperatura actual y la estación del año en un display LCD.

# componentes
* Arduino UNO
* Sensor de temperatura
* Control remoto IR (Infrarrojo)
* Display LCD (16x2 caracteres)
* Servo motor
* Cables y 3 resistencias de 220 Ω
* Protoboard para realizar las conexiones
* Dos leds (uno verde y uno rojo).
  
## esquematico

![Circuit design 2do parcial _ Tinkercad - Google Chrome 19_6_2023 08_49_43 (2)](https://github.com/bautista-escalante/sistema-contra-incendios/assets/123372673/3a098bed-a021-4faf-9cdd-6dd2c10246ae)

## circuito
![Circuit design 2do parcial _ Tinkercad - Google Chrome 19_6_2023 08_49_26 (2)](https://github.com/bautista-escalante/sistema-contra-incendios/assets/123372673/1b3a90d1-d3c7-4fbb-ad2a-d9adb9d82c20)

# conexiones del LCD

### puertos de alimentacion 
cables de color rojo y negro para 5v y gnd 
  * vcc --> 5v
  * gnd --> 0v
  * A --> anodo del back ligth
  * k --> catodo del back ligth
  * V0 --> contaste recive entre 0v a 1.5v para lograr esto usaremos una resistencia variable de 10kohm
### puertos de datos
cables de color lila --> pines digitales
  * D4
  * D5
  * D6
  * D7
### puertos de control
cables de color azul
  * RS --> pin digital
  * R/W --> gnd para escritura /5v para lectura
  * E --> pin digital
# funciones

### CalcularEstacion()
es la funcion principal del sistema, se ingresa la temperatura obtenida del sensor y se opera con ella y usando la funcion _OperarLcd_ muesta en pantalla la estacion del año  segun el rango de temperatura, y en caso de un incendio utiliza la funcion _MoverServo()_ y para apagar el sistema usa la funcion _UsarControl()_

``` cpp
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
```
### OperarLcd
esta funcion recive un string con la estacion que se desea mostrar y un int con la temperatura, denro de la funcion se castea temp para poder concatenarlo a el string
```cpp
void OperarLcd(const char* estacion,int temp)
{
  lcd.print(estacion);
  lcd.setCursor(0, 1);
  lcd.print("temperatura: " + String(temp)+"c");
  delay(200); 
  lcd.clear();
  lcd.setCursor(0, 0);
}
```
### EncenderDiodo()
enciende un led segun el numero que se pasa por parametro, si es 1 enciende el verde que indica que el sistema se encuentra dentro del rango establecido y si es 2 entonces enciede el led rojo que indica que el sistema detecto un incendio
```cpp
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
```
### MoverServo()
esta funcion mueve el servo en los grados que se indique por parametro
```cpp
void MoverServo(int grados)
{
  myservo.write(0); 
  delay(700);      
  myservo.write(grados); 
  delay(700);     
}
```
### UsarControl()
esta funcion apaga el sistema con un control remoto
```cpp
}
void UsarControl() {
  if (IrReceiver.decode()) {
      IrReceiver.resume();
    if(IrReceiver.decodedIRData.decodedRawData == power)
    {
      activo=false;
     Serial.println("apagado");
    }
    else if(IrReceiver.decodedIRData.decodedRawData == func)
    {
     activo=true;
     Serial.println("encendido"); 
    }
  }
}
```
# link del proyecto
https://www.tinkercad.com/things/gJdcS0MnkMV-2do-parcial/editel?sharecode=BHd2l6CWNNyz-uC4-E2yNhhAMRBsZ_Hp7laVMdXjlVU






