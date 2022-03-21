#include "core/Types.h"
#include "core/RingBuff.h"
#include "headers.h"
#include <random>
#include <iostream>
#include <assert.h>

using namespace core;
using namespace std;

#define Random(N) (rand() % (N) + 1)

//namespace bf
//{
    char* generatestr(int32 len) {
        char* str = new char[len];
        for (int i = 0; i < len; i++)
            str[i] = 'a' + Random(25);
        return str;
    }

    TEST(ring)
    {
        //int32 total = Random(10);
        //std::vector<char*> vec;
        CRingBuff buff(120);
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
        CRingBuff buff(1024);

        int32 strCount = Random(10000);
        cout << "strCount:" << strCount << endl;
        std::vector<str> vec;
        std::vector<str> rvec;
        //rvec.resize(strCount);
        int32 count = 0;
        for (int32 i=0; i<strCount; i++)
        {
            auto len = Random(3000);
            count += len;
            vec.emplace_back(str(generatestr(len), len));
            rvec.emplace_back(str(generatestr(len), len));
        }
        cout << count << endl;
        int32 r = 0, w = 0, mx = 0, mxc = 0;
        uint32 maxcap = 0, maxs = 0;
        while(r < w || w < strCount)
        {
            if (Random(100) <= 60 && r < w || w >= strCount)//r 
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
            mx = max(mx, w-r);
            if (buff.size()) 
            {
                mxc = max(mxc, int32(buff.capacity() - buff.size()));
            }
            maxcap = max(maxcap, buff.capacity());
            maxs = max(maxs, buff.size());
        }
        cout << "mx:"<<mx << "  mxc:"<<mxc<< "  maxcap:"<< maxcap << "  maxs:"<< maxs << endl;
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

    TEST(ring3)
    {
		struct str {
			str(char* cc, int ll) : c(cc), len(ll) {}
			char* c;
			int32 len;
			void pr()
			{
				for (int32 i = 0; i < len; i++)
				{
					cout << char(c[i]);
				}
				cout << endl;
			}
		};

		int32 strCount = Random(10000);
        int32 count = 0;
		for (int32 i = 0; i < 10000; i++)
		{
			auto len1 = Random(980);
            auto str1 = str(generatestr(len1), len1);
			CRingBuff buff(1028);
            buff.write(str1.c, len1);
			auto len2 = Random(buff.capacity() - len1);
			auto str2 = str(generatestr(len2), len2);
            auto wr = buff.writerv();
            int32 l = wr[0].len >= len2 ? len2 : wr[0].len;
            memcpy(wr[0].buff, str2.c, l);
            if (l < len2)
            {
                memcpy(wr[1].buff, str2.c + l, len2 - l);
            }
            else
            {
                count++;
                continue;
            }
            buff.write(len2);
            char str3[1024 * 2 + 1];
            memset(str3, 0, sizeof(char)*(1024 * 2 + 1));
            buff.read(str3, len1 + len2);
            int32 j = 0;
			//str1.pr();
			//str2.pr();
   //         cout << str3 << endl;
            for (int32 i = 0 ; i < str1.len; i++)
            {
				if (char(str1.c[i]) != char(str3[j++]))
				{
					cout << "error" << "  " << char(str1.c[i]) << "  " << char(str3[j-1]) << endl;
					//assert(false);
				}
            }
			for (int32 i = 0; i < str2.len; i++)
			{
				if (char(str2.c[i]) != char(str3[j++]))
				{
					cout << "error" << "  " << char(str2.c[i]) << "  " << char(str3[j - 1]) << endl;
					//assert(false);
				}
			}
		}

        cout << count << endl;
    }

    void testbuff()
    {
        //test_ring();
        
        //test_ring2();

        test_ring3();
    }
//}
