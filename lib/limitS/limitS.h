#ifndef limitS_h
#define limitS_h

#include <Arduino.h>

class limitS{
    private: 
        int _limitSR;
        int _limitSL;
        int _Value1;
        int _Value2;
    public:
        limitS(int R, int L){
            _limitSR=R;
            _limitSL=L;

        };
        void setup(){
            pinMode(_limitSL,INPUT);
            pinMode(_limitSR,INPUT);
        };
        int value(){
            _Value1=digitalRead(_limitSL);
            _Value2=digitalRead(_limitSR);
            return(_Value1);

            if ((_Value1==1)||(_Value2==0))
            {
                return(0);
            }
            else if ((_Value1==0)||(_Value2==1))
            {
                return(1);
            }
        };

};
#endif
