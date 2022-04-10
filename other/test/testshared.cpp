#include "headers.h"

using namespace core;
using namespace std;


class Cbase;
class CDer
{
public:
	CDer() {

	}

	void operator()(Cbase* ptr)
	{
		cout << "Der...." << ptr << endl;
		return;
	}
};

class Cbase : public std::enable_shared_from_this<Cbase>
{
public:
	int32 a;

	shared_ptr<Cbase> get()
	{
		auto p = shared_from_this();
		//auto d =  std::get_deleter <CDer, Cbase> (p);
		//cout << d << endl;
		return p;
	}
};

void testShare()
{
	//shared_ptr<Cbase> p(new Cbase(), [](Cbase *ptr) {
	//		
	//});
	shared_ptr<Cbase> p2;
	{
		shared_ptr<Cbase> p(new Cbase(), [](Cbase *p) {
			cout << "..." <<p<< endl;
		});
		p2 =  p->get();
		cout << "======" << endl;
	}
}