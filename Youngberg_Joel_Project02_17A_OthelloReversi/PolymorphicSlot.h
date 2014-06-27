#ifndef POLYMORPHICSLOT_H
#define POLYMORPHICSLOT_H
#include "SlotBase.h"
template <class T>
class PolySlot: public SlotBase<T>{//I created this class only to give an example of inheritance
                            // and polymorphism especially for you Dr. Lehr although it is
                            //completely pointless to the core game...
public:
    void praiseWinner();
};

    template <class T>
    void PolySlot<T>::praiseWinner(){
        cout << "You are the best!!! Points Bonus = " << prsAmt << endl;
 }
#endif // POLYMORPHICSLOT_H
