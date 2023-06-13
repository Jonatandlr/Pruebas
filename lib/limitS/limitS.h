#ifndef limitS_h
#define limitS_h
#include <Arduino.h>

class limitS{
    private: 
        int _limitS;
        int _Value1;
    public:
        limitS(int limit){
            _limitS=limit;
            pinMode(_limitS,INPUT_PULLUP);
        };
        int value(){
            _Value1=digitalRead(_limitS);
            return(_Value1);
        };
};
#endif
