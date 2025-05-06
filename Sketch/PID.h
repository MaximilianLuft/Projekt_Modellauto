/////////////////////////////////////////////////////////
///// This file does not need any modification, /////////
///// if needed it can be extended //////////////////////
///////////////////////////////////////////////////////// 
#pragma once

struct pidParameterSet{
  double p, i, d, soll, base, antiWindup, outMin, outMax;
};


class PID {
  public:
    PID(pidParameterSet);
    ~PID();

    void setSoll(double soll);
    void resetIntegrator();
    double calcOutput(double input);
    double getBase();
    double getP();
    double getI();
    double getD();
    void setP(double parameterP);
    void setI(double parameterI);
    void setD(double parameterD);
    
        
  private:   
    double lastError, integral;
    double p, i, d;
    double outMin = 0, outMax = 255, soll, base;
    double antiWindup;  
};

