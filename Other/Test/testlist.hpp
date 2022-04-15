#include "core/FastNode.h"
#include <list>
#include <math.h>
#include <random>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

using namespace core;
using namespace std;
//default_random_engine eg;
//uniform_int_distribution<int> random(1, 10000);
#define random(N) (int32(rand()%N + N)%N)

void testList1();

class CValue : public CFastNode<CValue*>
{
    int32 data;
public:
    explicit CValue(int32 d) : data(d), CFastNode<CValue*>(this){

    };

    ~CValue() {

    }

    operator int32() {
        return data;
    }

    void show()
    {
        cout <<data<<" "<<(int32)_next<< "  "<<(int32)_prev << "  "<<int32(_data) << endl;
    }
};
using CList = CValue;
using CNode = CValue;

template<class T>
inline void lprint(const CFastNode<T>& list)
{
    for (auto iter = list.begin(); iter != list.end(); iter = iter->next())
        std::cout << " " << iter->data();
    cout << endl;
}

inline void lprint(CList& list)
{
    //list.data()->show();
    //cout << "---" << (int32)list.end() << "  "<<(int32)&list<<endl;
    for (auto iter = list.begin(); iter != list.end(); iter = iter->next())
    {
        std::cout << " " << *iter->data();
    }
    cout << endl;
}

template<class T>
inline void lprint(const std::list<T>& list)
{
    for (auto& iter : list)
        std::cout << " " << iter;
    cout << endl;
}

inline void testList1()
{
    srand(time(NULL));

    list<int32> list1;
    CList list2(0);

    auto show = [&list1, &list2]() {
        lprint(list1);
        //list2.show();
        lprint(list2);
    };

    auto check = [&list1, &list2]() {
        auto iter1 = list1.begin();
        auto iter2 = list2.begin();
        while (iter1 != list1.end())
        {
            if (*iter1 != *iter2->data()) 
            {
                assert(false);
                return false;
            }
            iter1++;
            iter2 = iter2->next();
        }
        return true;
    };

    int i = 1;
    int j = i++;
    cout << " " << j << "  " << i << endl;

    int32 len = 500000;
    while (len--)
    {
        int32 value = random(1000);
        CNode* node = new CNode(value);
        if (value&1) 
        {
            list1.push_back(value);
            list2.pushBack(*node);
            //cout << " " << list2.begin() << "  " << "  " << node << "  " << &list2 << endl;
            //printf("%d %d %d %d\n", list2.next(), list2.end(), node, &list2);
        }
        else 
        {
            list1.push_front(value);
            list2.pushFront(*node);
        }
    }
    //show();
    check();

    int32 len2 = 50000;
    while (len2--)
    {
        int32 value = random(10);
        if (value&1)
        {
            list1.pop_front();
            list2.popFront();
        }
        else
        {
            list1.pop_back();
            list2.popBack();
        }
    }
    check();

    int32 len3 = 5000;
    while (len3--)
    {
        int32 value = random(50000);
        auto iter1 = list1.begin();
        auto iter2 = list2.begin();
        while (value--)
        {
            iter1++;
            iter2 = iter2->next();
        }
        if (value&1)
        {
            list1.erase(iter1);
            iter2->leave();
        }
        else
        {
            list1.insert(iter1, value);
            CNode* node = new CNode(value);
            iter2->pushFront(*node);
        }
    }
    check();
}