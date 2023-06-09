#ifndef limitS_h
#define limitS_h

#include <Arduino.h>

class limitS{
    private: 
        int _limitS;
        int _Value1;
        int _a;
        int _b;
    public:
        limitS(int limit){
            _limitS=limit;
            pinMode(_limitS,INPUT_PULLUP);

        };
        int value(){
            _Value1=digitalRead(_limitS);
            return(_Value1);
        };
        int interrupt(int a, int b){
            _a=a;
            _b=b;
            if ((_a==0)|| (_b==0))
            {
                return(0);
            }
            else{
               return(1); 
            }
        };

};
#endif
