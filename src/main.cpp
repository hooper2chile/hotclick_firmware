#include<Arduino.h>
#include<PID_v1.h>

#define D11 11

double pwm    = 0;
double temp_m = 0;  //temp measure
double temp_s = 0;  //temp setpoint


double Kp=50, Ki=12, Kd=0.5;
PID HC_PID(&temp_m, &pwm, &temp_s, Kp, Ki, Kd, DIRECT);


void info() {
  Serial.print("Temp_DS18B20:\t"); Serial.print(temp_m);
  Serial.print("\tPWM Set:  ");    Serial.print(pwm);
  Serial.print("\tTemp_SET:\t");   Serial.print(temp_s);
  Serial.print("\n");
}

void setup(){
  Serial.begin(9600);
  pinMode(A4,  INPUT ); //for temp DS18B20 (digital)
  pinMode(D11, OUTPUT); //for pwm

  HC_PID.SetMode(AUTOMATIC);
  temp_s = 120;  //100 [ºC]
}

int i=0;
int N=500;
void loop() {
  //Code for measures
  for (i=0; i<N; i++)
    temp_m += analogRead(A4);
  temp_m = 0.488*temp_m/N;

  //Code for PID
  HC_PID.Compute();
  pwm = (int) pwm;
  analogWrite(D11, pwm);

  info();
}
