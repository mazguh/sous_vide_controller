#include <Arduino.h>
#include "pid.h"

Pid::Pid()
{
	last_error = 0;
	integral   = 0;
	target     = 0;
	Kp         = 0;
	Ki         = 0;
	Kd         = 0;
	time       = millis();
}

void Pid::setKp(float val)
{
	Kp = val;
}

void Pid::setKi(float val)
{
	Ki = val;
}

void Pid::setKd(float val)
{
	Kd = val;
}

void Pid::setTarget(float newTarget)
{
	target   = newTarget;
	integral = 0;
}

int Pid::update(float measuredValue)
{
	unsigned long dt;
	float error;
	float derivative;
	float result;

    dt         = millis() - time;
	error      = target - measuredValue;
	integral  += (error * dt);
	derivative = (error - last_error)/dt;

	last_error = error;
	time       = millis();
	result = (Kp * error + Ki * integral + Kd * derivative);
    Serial.print("P: ");
    Serial.print(Kp * error);
    Serial.print(" I: ");
    Serial.print(Ki * integral);
    Serial.print(" D: ");
    Serial.println(Kd * derivative);

    if(result>255)
    {
    	Serial.println("Result too high. Returning 255");
    	return 255;
    }
    if(result<0)
    {
    	Serial.println("Result too low. Returning 0");
    	return 0;
    }

    Serial.print("PWM: ");
    Serial.println((int)(Kp * error + Ki * integral + Kd * derivative));
	return (int)(Kp * error + Ki * integral + Kd * derivative);

}
