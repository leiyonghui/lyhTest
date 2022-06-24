#pragma once
#include "configs.h"
#include "core/IntrusiveNode.h"
class A;
class tag1;
class tag2;

using NodeList1 = IntrusiveNode<A, tag1>;
using NodeList2 = IntrusiveNode<A, tag2>;

class A : public NodeList1, public NodeList2// (nodelist1, nodelist2, A)
{
public:
	int32 a{ 1 };
};

#define PN(pr) cout<<int64(pr)<<endl;

void push1(NodeList1* a)
{
	PN(a);
}

void push2(NodeList2* a)
{
	PN(a);
}

void test_buju()
{
	PN(FPOS(A, NodeList1::_prev));
	PN(FPOS(A, NodeList2::_prev));
	PN(FPOS(A, a));

	A* node = new A();
	PN(node);

	PN(&node->a);

	auto* node1 = static_cast<NodeList1*>(node);
	auto* node2 = static_cast<NodeList2*>(node);
	PN(node1);
	PN(node2);
}