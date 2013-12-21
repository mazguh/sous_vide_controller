#ifndef PID_H
#define PID_H

class Pid
{
public:
	Pid();
	void setKp(float);
	void setKi(float);
	void setKd(float);
	int  update(float);
	void setTarget(float);

private:
	float last_error;
	float integral;
	float target;
	float Kp, Ki, Kd;
	unsigned long time;
};


#endif // PID_H