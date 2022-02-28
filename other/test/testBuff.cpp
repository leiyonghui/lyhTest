#include "core/Types.h"
#include "core/RingBuff.h"
#include "headers.h"
#include <random>
#include <iostream>
#include <assert.h>

using namespace core;
using namespace std;

#define Random(N) (rand() % N + 1)

namespace bf
{
    char* generatestr(int32 len) {
        char* str = new char[len];
        for (int i = 0; i < len; i++)
            str[i] = Random(255);
        return str;
    }

    TEST(ring)
    {
        //int32 total = Random(10);
        //std::vector<char*> vec;
        RingBuff buff(120);
        auto str1 = generatestr(100);
        buff.write(str1, 100);
        auto str2 = generatestr(100);
        buff.read(str2, 50);
        auto str3 = generatestr(100);
        buff.write(str3, 70);
        //buff.write(str2, 100);
        buff.size();
        buff.read(str3, 20);
        buff.size();
        buff.write(str3, 70);
    }

    TEST(ring2)
    {
        struct str {
            str(char* cc, int ll): c(cc), len(ll){}
            char* c;
            int32 len;
            void pr()
            {
                for (int32 i = 0; i< len; i++)
                {
                    cout << c[i];
                }
                cout << endl;
            }
        };
        RingBuff buff(1024);

        int32 strCount = Random(10000);
        cout << "strCount:" << strCount << endl;
        std::vector<str> vec;
        std::vector<str> rvec;
        //rvec.resize(strCount);
        for (int32 i=0; i<strCount; i++)
        {
            auto len = Random(3000);
            vec.emplace_back(str(generatestr(len), len));
            rvec.emplace_back(str(generatestr(len), len));
        }
        int32 r = 0, w = 0;
        while(r < w || w < strCount)
        {
            if (Random(10) %2 && r < w || w >= strCount)//r 
            {
                int32 len = vec[r].len;
                buff.read(rvec[r].c, len);
                r++;
            }
            else//w
            {
                buff.write(vec[w].c, vec[w].len);
                w++;
            }
        }
        for (int32 i = 0; i < strCount; i++)
        {
            //vec[i].pr();
            //rvec[i].pr();
            int32 len = vec[i].len;
            for (int32 j = 0; j < len; j++)
            {
                if (char(vec[i].c[j]) != char(rvec[i].c[j])) 
                {
                    cout <<"error"<<"  "<< char(vec[i].c[j])<<"  "<< char(rvec[i].c[j]) << endl;
                    //assert(false);
                }
            }
        }
    }

    void testbuff()
    {
        test_ring();
        
        test_ring2();
    }
}
