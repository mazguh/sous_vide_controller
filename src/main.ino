// main.ino

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Timer.h>
#include "pid.h"

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 6

#define PWM_PIN 10

int32_t frequency = 1000;


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
DeviceAddress temperatureSensor;

Pid pid;
Timer t;
int temperatureTimer;

void temperatureHandler()
{
  float temp;
  int pwm;
  sensors.requestTemperatures();
  temp = sensors.getTempC(temperatureSensor);
  pwm = pid.update(temp);
  analogWrite(PWM_PIN, pwm);
}

void setup(void)
{
  // start serial port
  Serial.begin(9600);

  pinMode(PWM_PIN, OUTPUT);
  TCCR2B = TCCR2B & 0b11111000 | 0x07; // Set the prescaler for TIMER2 (used by pwm on pin 10) to 1024 giving around 30.5Hz frequency

  // Start up the library
  sensors.begin();
  Serial.print("Number of temperature sensors detected is: ");
  Serial.println(sensors.getDeviceCount());
  sensors.getAddress(temperatureSensor, 0);

  pid.setKp(42);
  pid.setKi(0.00008);
  pid.setKd(300000);

  pid.setTarget(68.4);

  temperatureTimer = t.every(2000, temperatureHandler);
}

void loop(void)
{ 
  t.update();
}

