#include <Servo.h>
  
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;

int joyX=0;
int joyY=1;
int joyX1=3;
int joyY1=4;

int sw=4;
int sw1=2;
int sw2=0;

int pulsador;
  
int joystickVal;
int angle;
int swVal;

void setup() 
{
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  servo5.attach(10);
  servo6.attach(11);
  
  servo7.attach(12);
  servo8.attach(13);


  // activa resistencias pull-up en pin pulsador
  pinMode(sw, INPUT_PULLUP);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);


  
  Serial.begin(9600);
}


void loop()
{
pulsador=digitalRead(sw2);
//de normal está en posición 1 y mientras pulsas pasa a estar en posición 0


//vuelta a la posición base de 90 grados en cada servo

if(pulsador==0)
{
  
  
  //servo 1
  angle=servo1.read();
  while(angle<=93)
  {
    angle=servo1.read();
    angle=angle+1;
    servo1.write(angle);
    delay(20);
    Serial.println(angle);
  }
  while(angle>=93)
  {
    angle=servo1.read();
    angle=angle-1;
    servo1.write(angle);
    delay(20);
    Serial.println(angle);
  }
  
  //servo 2
  angle=servo2.read();
  while(angle<=93)
  {
    angle=servo2.read();
    angle=angle+1;
    servo2.write(angle);
    delay(20);
    Serial.println(angle);
  }
  while(angle>=93)
  {
    angle=servo2.read();
    angle=angle-1;
    servo2.write(angle);
    delay(20);
    Serial.println(angle);
  }
  
//servo 3
  angle=servo3.read();
  while(angle<=93)
  {
    angle=servo3.read();
    angle=angle+1;
    servo3.write(angle);
    delay(20);
    Serial.println(angle);
  }
  while(angle>=93)
  {
    angle=servo3.read();
    angle=angle-1;
    servo3.write(angle);
    delay(20);
    Serial.println(angle);
  }

  //servo 4
  angle=servo4.read();
  while(angle<=93)
  {
    angle=servo4.read();
    angle=angle+1;
    servo4.write(angle);
    delay(20);
    Serial.println(angle);
  }
  while(angle>=93)
  {
    angle=servo4.read();
    angle=angle-1;
    servo4.write(angle);
    delay(20);
    Serial.println(angle);
  }
  
  
//servo 5
  angle=servo5.read();
  while(angle<=93)
  {
    angle=servo5.read();
    angle=angle+1;
    servo5.write(angle);
    delay(20);
    Serial.println(angle);
  }
  while(angle>=93)
  {
    angle=servo5.read();
    angle=angle-1;
    servo5.write(angle);
    delay(20);
    Serial.println(angle);
  }

  
//servo 6
  angle=servo6.read();
  while(angle<=93)
  {
    angle=servo6.read();
    angle=angle+1;
    servo6.write(angle);
    delay(20);
    Serial.println(angle);
  }
  while(angle>=93)
  {
    angle=servo6.read();
    angle=angle-1;
    servo6.write(angle);
    delay(20);
    Serial.println(angle);
  }

  
//servo 7+8 (doble)
  angle=servo7.read();
  while(angle<=93)
  {
    angle=servo7.read();
    angle=angle+1;
    servo7.write(angle);
    servo8.write(180-angle);
    delay(20);
    Serial.print(angle);
    Serial.print("+");
    Serial.println(180-angle);
  }
  while(angle>=93)
  {
    angle=servo7.read();
    angle=angle-1;
    servo7.write(angle);
    servo8.write(180-angle);
    delay(20);
    Serial.println(angle);
    Serial.print("+");
    Serial.println(180-angle);
  }
   
}






//motor 1 (503)
  
  joystickVal = analogRead(joyX);
  angle=servo1.read();
  swVal = digitalRead(sw1);

  while (joystickVal < 493 && angle>40 && swVal==1) {
    joystickVal = analogRead(joyX);
    angle=angle-4;
    servo1.write(angle);
    delay(25);
    
  Serial.print("Posición Joystick X Rojo = ");
  Serial.print(joystickVal);
  Serial.print(" / ");
  Serial.print("Posición servo 1 = ");
  Serial.print(angle);
  Serial.print("\n");

    }
  while (joystickVal > 513 && angle<100  && swVal==1) {
    joystickVal = analogRead(joyX);
    angle=angle+4;
    servo1.write(angle);
    delay(25);
    
  Serial.print("Posición Joystick X Rojo= ");
  Serial.print(joystickVal);
  Serial.print(" / ");
  Serial.print("Posición servo 1 = ");
  Serial.print(angle);
  Serial.print("\n");

    }

//motor 2 (521-522)


  
  joystickVal = analogRead(joyY);
  angle=servo2.read();
  swVal = digitalRead(sw1);

  while (joystickVal < 500 && angle>1 && swVal==1) {
    joystickVal = analogRead(joyY);
    angle=angle-4;
    servo2.write(angle);
    delay(25);
    
  Serial.print("Posición Joystick Y Rojo = ");
  Serial.print(joystickVal);
  Serial.print(" / ");
  Serial.print("Posición servo 2 = ");
  Serial.print(angle);
  Serial.print("\n");

    }
  while (joystickVal > 540 && angle<179 && swVal==1) {
    joystickVal = analogRead(joyY);
    angle=angle+4;
    servo2.write(angle);
    delay(25);
    
  Serial.print("Posición Joystick Y Rojo = ");
  Serial.print(joystickVal);
  Serial.print(" / ");
  Serial.print("Posición servo 2 = ");
  Serial.print(angle);
  Serial.print("\n");

    }


    
//motor 3 (501-502)
  
  joystickVal = analogRead(joyX1);
  angle=servo3.read();
  swVal = digitalRead(sw);

  while (joystickVal < 490 && angle>1 && swVal==1) {
    joystickVal = analogRead(joyX1);
    angle=angle-4;
    servo3.write(angle);
    delay(25);
    
  Serial.print("Posición Joystick X Morado = ");
  Serial.print(joystickVal);
  Serial.print(" / ");
  Serial.print("Posición servo 3 = ");
  Serial.print(angle);
  Serial.print("\n");

    }
  while (joystickVal > 520 && angle<179 && swVal==1) {
    joystickVal = analogRead(joyX1);
    angle=angle+4;
    servo3.write(angle);
    delay(25);
    
  Serial.print("Posición Joystick X Morado = ");
  Serial.print(joystickVal);
  Serial.print(" / ");
  Serial.print("Posición servo 3 = ");
  Serial.print(angle);
  Serial.print("\n");

    }
    
//motor 4 (497)
  
  joystickVal = analogRead(joyY1);
  angle=servo4.read();
  swVal = digitalRead(sw);

  while (joystickVal < 487 && angle>1 && swVal==1) {
    joystickVal = analogRead(joyY1);
    angle=angle-4;
    servo4.write(angle);
    delay(25);
    
  Serial.print("Posición Joystick Y Morado = ");
  Serial.print(joystickVal);
  Serial.print(" / ");
  Serial.print("Posición servo 4 = ");
  Serial.print(angle);
  Serial.print("\n");

    }
  while (joystickVal > 510 && angle<179 && swVal==1) {
    joystickVal = analogRead(joyY1);
    angle=angle+4;
    servo4.write(angle);
    delay(25);
    
  Serial.print("Posición Joystick Y Morado = ");
  Serial.print(joystickVal);
  Serial.print(" / ");
  Serial.print("Posición servo 4 = ");
  Serial.print(angle);
  Serial.print("\n");

    }

//motor 5 (sw & 501-502)

  joystickVal = analogRead(joyX1);
  angle=servo5.read();
  swVal = digitalRead(sw);

  while (joystickVal < 490 && angle>1 && swVal==0) {
    joystickVal = analogRead(joyX1);
    angle=angle-4;
    servo5.write(angle);
    delay(25);
    
  Serial.print("Posición Joystick X Morado = ");
  Serial.print(joystickVal);
  Serial.print(" / ");
  Serial.print("Posición servo 5 = ");
  Serial.print(angle);
  Serial.print(" / ");
  Serial.print("Posición switch sw = ");
  Serial.print(swVal);
  Serial.print("\n");

    }
  while (joystickVal > 520 && angle<179 && swVal==0) {
    joystickVal = analogRead(joyX1);
    angle=angle+4;
    servo5.write(angle);
    delay(25);
    
  Serial.print("Posición Joystick X Morado = ");
  Serial.print(joystickVal);
  Serial.print(" / ");
  Serial.print("Posición servo 5 = ");
  Serial.print(angle);
  Serial.print(" / ");
  Serial.print("Posición switch sw = ");
  Serial.print(swVal);
  Serial.print("\n");

    }

//motor 6 (sw & 497)

  joystickVal = analogRead(joyY1);
  angle=servo6.read();
  swVal=digitalRead(sw);

  while (joystickVal < 487 && angle>1 && swVal==0) {
    joystickVal = analogRead(joyY1);
    angle=angle-4;
    servo6.write(angle);
    delay(25);
    
  Serial.print("Posición Joystick Y Morado = ");
  Serial.print(joystickVal);
  Serial.print(" / ");
  Serial.print("Posición servo 6 = ");
  Serial.print(angle);
  Serial.print(" / ");
  Serial.print("Posición switch sw = ");
  Serial.print(swVal);
  Serial.print("\n");

    }
  while (joystickVal > 510 && angle<179 && swVal==0) {
    joystickVal = analogRead(joyY1);
    angle=angle+4;
    servo6.write(angle);
    delay(25);
    
  Serial.print("Posición Joystick Y Morado= ");
  Serial.print(joystickVal);
  Serial.print(" / ");
  Serial.print("Posición servo 6 = ");
  Serial.print(angle);
  Serial.print(" / ");
  Serial.print("Posición switch sw = ");
  Serial.print(swVal);
  Serial.print("\n");

  }

//motor doble, servos 7 y 8 (sw1 & 503)
  
  joystickVal = analogRead(joyX);
  angle=servo7.read();
  swVal=digitalRead(sw1);

  while (joystickVal < 493 && angle>1 && swVal==0) {
    joystickVal = analogRead(joyX);
    angle=angle-4;
    servo7.write(angle);
    servo8.write(180-angle);
    delay(25);
    
  Serial.print("Posición Joystick X Rojo = ");
  Serial.print(joystickVal);
  Serial.print(" / ");
  Serial.print("Posición servo 7 y  8 = ");
  Serial.print(angle);
  Serial.print(" - ");
  Serial.print(180-angle);
  Serial.print(" / ");
  Serial.print("Posición switch sw1= ");
  Serial.print(swVal);
  Serial.print("\n");

    }
  while (joystickVal > 513 && angle<179  && swVal==0) {
    joystickVal = analogRead(joyX);
    angle=angle+4;
    servo7.write(angle);
    servo8.write(180-angle);
    delay(25);
    
  Serial.print("Posición Joystick X Rojo = ");
  Serial.print(joystickVal);
  Serial.print(" / ");
  Serial.print("Posición servo 7 y 8 = ");
  Serial.print(angle);
  Serial.print(" - ");
  Serial.print(180-angle);
  Serial.print(" / ");
  Serial.print("Posición switch sw1= ");
  Serial.print(swVal);
  Serial.print("\n");

  }
  


//tasa refresco del void 20 ms
  
  delay(20);  
}
