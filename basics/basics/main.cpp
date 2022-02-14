#include<atomic>                                                                
#include <stdio.h>
using namespace std;

atomic<int> a;
int j;

class AA {
public:
    AA(int aa = 0):a(aa) {

    }

    operator int() {
        return a;
    }

    ~ AA(){

    }
public:
    int a;
};


void testA(int a)
{
    printf("%d", a);
}

int main()
{
    int n;

    a.store(1, memory_order_acquire);
    n = j;

    {
        AA* ta = new AA();
        testA(*ta);
    }
    return 0;
}