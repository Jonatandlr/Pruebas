#ifndef joystick_h
#define joystick_h

#include <Arduino.h>

class joystick{
    private:
        int _xvr;
        int _xValue;

    public:
        joystick(int xvr){_xvr=xvr;};
        void setup(){pinMode(_xvr,INPUT);};
        int valor(){
            _xValue=analogRead(_xvr);
            return(_xValue);
        };
        String direction(){
            _xValue=analogRead(_xvr);
            // return(_xValue);
            if (_xValue>=800)
            {
                return("RIGHT");//right
            }
            else if (_xValue<=300)
            {
                return("LEFT");//left
            }
            else{
                return("CENTER");
            }
        };
};

#endif