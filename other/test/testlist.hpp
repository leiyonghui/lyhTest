#include "core/FastNode.h"
#include "core/types.h"
#include <list>
#include <math.h>
#include <random>
#include <assert.h>

using namespace core;
using namespace std;
//default_random_engine eg;
//uniform_int_distribution<int> random(1, 10000);
#define random(N) (int32(rand()%N))

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
inline void lprint(CFastNode<T> list)
{
    for (auto iter = list.begin(); iter != list.end(); iter = iter->next())
        std::cout << " " << iter->data();
    cout << endl;
}

inline void lprint(CList list)
{
    //list.data()->show();
    cout << "---" << (int32)list.end() << "  "<<(int32)&list<<endl;
    /*for (auto iter = list.begin(); iter != list.end(); iter = iter->next())
    {
        std::cout << " " << *iter->data();
    }*/
    cout << endl;
}

template<class T>
inline void lprint(std::list<T> list)
{
    for (auto& iter : list)
        std::cout << " " << iter;
    cout << endl;
}

inline void testList1()
{
    list<int32> list1;
    CList list2(0);

    auto show = [&list1, &list2]() {
        //lprint(list1);
        list2.show();
        lprint(list2);
        cout << endl;
    };

    auto check = [&list1, &list2]() {
        auto len = list1.size();
        auto iter1 = list1.begin();
        auto iter2 = list2.begin();
        while (len--)
        {
            if (*iter1 != *iter2->data()) 
            {
                assert(false);
                return false;
            }
            iter1 = iter1++;
            iter2 = iter2->next();
        }
        return true;
    };


    int32 len = 1;
    while (len--)
    {
        int32 value = 3;
        CNode* node = new CNode(value);
        if (value&1) 
        {
            list1.push_back(value);
            list2.pushBack(*node);
            //cout << " " << list2.begin() << "  " << "  " << node << "  " << &list2 << endl;
            printf("%d %d %d %d\n", list2.next(), list2.end(), node, &list2);
        }
        else 
        {
            list1.push_front(value);
            list2.pushFront(*node);
        }
        show();
    }
    //check();


}