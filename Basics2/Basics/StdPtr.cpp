#include "headers.h"

class AA : public  std::enable_shared_from_this<AA> {
public:

	~AA()
	{
		cout << "del--" << endl;
	}
};


namespace share
{
	void testShare()
	{
		AA* p = new AA;
		std::shared_ptr<AA> pt(p);//±ØĞëÏÈÖ´ĞĞshare
		std::shared_ptr<AA> pt2 = p->shared_from_this();
		std::shared_ptr<AA> pt3 = p->shared_from_this();
	}
}

