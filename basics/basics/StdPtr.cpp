#include "StdPtr.h"
#include  <memory>
#include <iostream>
using int32 = int;
using namespace std;
class AA : public  std::enable_shared_from_this<AA> {
public:

	~AA()
	{
		cout << "del--" << endl;
	}
};

void testShare()
{
	AA* p = new AA;
	std::shared_ptr<AA> pt(p);//±ÿ–Îœ»÷¥––share
	std::shared_ptr<AA> pt2 = p->shared_from_this();
	std::shared_ptr<AA> pt3 = p->shared_from_this();
}