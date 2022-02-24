#include "constructor.h"

void testConstructor()
{
    problem1::problem1();
}

namespace problem1
{
    class AA {
    public:
        AA(int ab = 0) :a(0) {
            cout << "construction" << endl;
        }

        void operator()() {
            cout << "operator()" << endl;
        }

        ~AA() {

        }
    public:
        int a;
    };

    void problem1()
    {
        AA aa();   //ÕâÊÇÊ²Ã´£¿
        AA bb;
        cout << /*aa.a <<*/ " " << bb.a << "  " << "" << endl;
    }
}

namespace problem2
{
    
}