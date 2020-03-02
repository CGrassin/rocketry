/**
 * This file is an ultra light/simple PID controller
 * library for Arduino.
 * 
 * Charles GRASSIN, 2019
 * MIT License
 */
 
class PIDController {
  
private:
  float kp, ki, kd, lastErr, cumulErr;
  
public:
  PIDController(float kp, float ki,float kd) : kp(kp), kd(kd), ki(ki), lastErr(0), cumulErr(0){}
  
  float compute(float setPoint,float current, long detaT){
     /*Compute all the working error variables*/
     float error = setPoint - current;
     float dErr = (detaT==0)?0:(error - lastErr) / detaT;
     
     /*Remember some variables for next time*/
     lastErr = error;
     cumulErr += error * detaT;

     /*Compute PID Output*/
     return kp * error + ki * cumulErr +  kd * dErr;
  }
  
  void reset(){
    lastErr=0;cumulErr=0;
  }
};
