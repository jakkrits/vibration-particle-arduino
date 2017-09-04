
#include "Ubidots/Ubidots.h"


#define TOKEN "xST1cjaovCvlVOAhJ7KRsMUwngelHf"
#define DATA_SOURCE_NAME "VibroElectron"

Ubidots ubidots(TOKEN);

void setup() {
    Particle.keepAlive(45);
    Serial.begin(115200);
    ubidots.setDatasourceName(DATA_SOURCE_NAME);
}

void loop() {
    float sensor1_value = analogRead(A0);
    ubidots.add("ubidots_vibration_variable1", sensor1_value);
        ubidots.sendAll();
        Serial.print("Measure: ");
        Serial.println(sensor1_value);

        if (sensor1_value > 10) {
            digitalWrite(D7,HIGH);
            delay(1000);
            digitalWrite(D7,LOW);
        }

    delay(500);
}

//http://www.seeedstudio.com/wiki/Grove_-_Piezo_Vibration_Sensor
//Groove Vibration Sensor - MEAS-SPEC.com
/*
int val;
void setup() {
    Particle.keepAlive(45);
    Serial.begin(9600);
}

void loop() {
    val = analogRead(A0);
    Serial.println(val);
    delay(500);
}
*/


/*
//http://www.dfrobot.com/wiki/index.php/DFRobot_Digital_Vibration_Sensor_(SKU:DFR0027)
//DFROBOT - Vibration Sensor
//Pin 1 - Input, Pin 2 - Power, Pin 3 - Ground
#define SensorLED     D7
#define SensorINPUT   D3  //Connect the sensor to digital Pin 3 which is Interrupts 1.

unsigned char state = 0;

void setup()
{
    Serial.begin(9600);
    Particle.keepAlive(45);
    pinMode(SensorLED, OUTPUT);
    pinMode(SensorINPUT, INPUT);
    attachInterrupt(1, blink, FALLING);// Trigger the blink function when the falling edge is detected
}

void loop()
{
      if(state!=0)
      {
        state = 0;
        digitalWrite(SensorLED,HIGH);
        delay(500);
      }
      else {
         digitalWrite(SensorLED,LOW);
      }

    Serial.println(SensorINPUT);
    delay(500);
}


void blink()//Interrupts function
{
  state++;
}
*/
