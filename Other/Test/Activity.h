
#pragma once
#include "core/Configs.h"

//struct has_regOpen {
//
//    template <typename C, void (C::*)(const typename C::value_type&)>
//    struct Helper;
//
//    template <typename C, void (C::*)(typename C::value_type)>
//    struct Helper2;
//
//    template <typename C>
//    static bool test(...) .open()//        return false;
//    }
//    template <typename C>
//    static bool test(Helper<C, &C::regOpen>*) {
//        return true;
//    }
//    template <typename C>
//    static bool test(Helper2<C, &C::regOpen>*) {
//        return true;
//    }
//};

enum EActivity
{
    EActivity_1 = 1,
    EActivity_Rank = 2,
    EActivity_Target = 5,
    EActivity_End = 5,
};

struct CHandler
{
    std::function<void()> open;
    std::function<void()> close;
};

static std::map<int, CHandler> handlers;


#define GENERATE_REG_EVENT(event)\
    template<int T>\
    void reg_##event()\
    {\
        std::cout << "reg" << #event <<"void" << T << std::endl;\
        reg_##event<T - 1>();\
    }\
    template<>\
    void reg_##event<0>()\
    {\
        std::cout << "reg" <<#event<< "end!!" << std::endl;\
    }

#define REG_ACTIVITY_EVENT(event, act, funcname)\
    template<>\
    void reg_##event<int(EActivity_##act)>()\
    {\
        std::cout<<"reg"<<#event<< EActivity_##act <<std::endl; \
        assert(handlers[EActivity_##act].##event == nullptr);\
        handlers[EActivity_##act].##event = std::bind(&Activity::funcname, this);\
        reg_##event<EActivity_##act - 1>();\
    }

#define REG_ACTIVITY_OPEN(act, funcname, ...) REG_ACTIVITY_EVENT(open, act, funcname)
//#define REG_ACTIVITY_CLOSE(act, funcname) REG_ACTIVITY_EVENT(close, act, funcname)
#define REG_ACTIVITY_CLOSE(act, funcname, ...) REG_ACTIVITY_EVENT(close, act, funcname)
    

class Activity
{
public:
    GENERATE_REG_EVENT(open);
    GENERATE_REG_EVENT(close);

    REG_ACTIVITY_CLOSE(Rank, onCloseRank);
    void onCloseRank();

    REG_ACTIVITY_OPEN(Target, onOpenTarget, true);
    void onOpenTarget();

    REG_ACTIVITY_CLOSE(Target, onCloseTarget, true);
    void onCloseTarget();

    void init()
    {
        reg_open<EActivity_End>();
        reg_close<EActivity_End>();
        for (auto& iter : handlers)
        {
            if (iter.second.open)
            {
                iter.second.open();
            }
            if (iter.second.close)
            {
                iter.second.close();
            }
        }
    }
};