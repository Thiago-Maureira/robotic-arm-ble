#include <ESP32Servo.h> 
#include <BluetoothSerial.h> 
 
BluetoothSerial SerialBT; 
 
Servo servoAltura; 
Servo servoAvance; 
Servo servoBase; 
Servo servoPinza; 
 
// Posición inicial de altura 
int altura = 90; 
// Posición inicial de avance 
int avance = 90; 
// Posición inicial de base 
int base = 90;   
// Posición inicial de la pinza 
int pinza = 60;  

void setup() { 
  Serial.begin(115200); 
  SerialBT.begin("YOUR_BLUETOOTH_SSID"); 
 
  servoAltura.attach(13);
  servoAvance.attach(12);
  servoBase.attach(14);
  servoPinza.attach(27); 
 
  // Inicializa los servos en las posiciones iniciales   
  servoAltura.write(altura);   
  servoAvance.write(avance);   
  servoBase.write(base);   
  servoPinza.write(pinza); 
}

void loop() {   
  if (SerialBT.available()) {     
    char command = SerialBT.read();
    procesarComando(command); 
  } 
}

void procesarComando(char command) {
  switch (command) {
    case '5':
      altura = constrain(altura + 10, 20, 160);
      servoAltura.write(altura);
      break;

    case '8':
      altura = constrain(altura - 10, 20, 160);
      servoAltura.write(altura);
      break;   
        
    case '1':
      avance = constrain(avance + 10, 20, 160);
      servoAvance.write(avance);
      break;

    case '2':
      avance = constrain(avance - 10, 20, 160);
      servoAvance.write(avance);
      break;
      
    case '3':
      base = constrain(base + 10, 0, 180);
      servoBase.write(base);
      break; 
      
    case '4':
      base = constrain(base - 10, 0, 180);
      servoBase.write(base);
      break;     
      
    case '7':
      pinza = constrain(pinza - 40, 40, 80);
      servoPinza.write(pinza);
      break;     
      
    case '6':
      pinza = constrain(pinza + 40, 40, 80);
      servoPinza.write(pinza);
      break; 

    case '0': 
      // Volver a la posición inicial  
      altura = 90;
      avance = 90;
      base = 90;
      pinza = 60;
      servoAltura.write(altura);
      servoAvance.write(avance);
      servoBase.write(base);
      servoPinza.write(pinza);
      break;
  }
}
