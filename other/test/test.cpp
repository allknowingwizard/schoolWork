#include "test.h"

class test2 : public test {
    // public:
    //     virtual void sayHi();
    public:
    virtual void sayHi() {
        cout << "Hi\n";
    }
};