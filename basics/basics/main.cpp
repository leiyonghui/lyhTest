#include<atomic>                                                                
#include <stdio.h>
#include <iostream>
#include "constructor.h"
#include "lambda.h"
#include <chrono>


//using namespace std;
//using namespace std::chrono;
//using namespace std::literals;

class AA {
public:
    int32 aa;
    AA(int32 a): aa(a){}
};

namespace core
{
    AA operator"" _s(unsigned long long  a) {
        return AA(a);
    };

    AA BB()
    {
        return AA(1);
    }
}
int main()
{
    //testConstructor();
    auto a = core::BB();
    cout << a.aa << endl;
    testLambad();
    system("pause");
    return 0;
}