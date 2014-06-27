#ifndef SLOT_H
#define SLOT_H

#include "SlotBase.h"
template <class T>
class Slot: public SlotBase<T>{//I created this class only to give an example of inheritance
                               // and polymorphism especially for you Dr. Lehr although it is
                               //completely pointless to the game...

public:
    void praiseWinner();
};

    template <class T>
    void Slot<T>::praiseWinner(){
        cout << "Nobody flips like you do!!! Points Bonus = " << prsAmt << endl;
 }

#endif // SLOT_H

