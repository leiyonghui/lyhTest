#pragma once
//list重写
template<class T>
class List
{
	struct Node
	{
		Node():next(nullptr), pre(nullptr) {}

		Node(const T &t) :next(nullptr), pre(nullptr), v(t) {

		}

		Node* next;
		Node* pre;
		T v;
	};

	int nodeSize;
	Node *head;
	Node *tail;
public:
	List() :nodeSize(0), head(nullptr), tail(nullptr) {

	}

	List(const List &L)
	{
		*this = L;
	}

	~List() {
		clear();
	}

	//back() 
	T &back() const
	{
		try
		{
			return tail->v;
		}
		catch (char *exception)
		{
			std::cout << exception;
		}
	}

	//empty()
	bool empty() const
	{
		return nodeSize == 0;
	}

	//front() 返回第一个元素
	T &front() const
	{
		try
		{
			return  head->v;
		}
		catch (char *exception)
		{
			std::cout << exception;
		}
	}

	//insert() 插入一个元素到list中

	//	Lst1.merge() 合并两个list
	List &merge(List &list1, List &list2)
	{

	}

	//	Lst1.pop_back() 删除最后一个元素
	void pop_back()
	{
		if (tail == nullptr)
			return;

		nodeSize--;
		if (tail->pre == nullptr)
		{
			delete tail;
			tail = nullptr;
			head = nullptr;
			return;
		}

		Node *pre = tail->pre;
		delete tail;
		pre->next = nullptr;
		tail = pre;
	}
	//	Lst1.pop_front() 删除第一个元素
	void pop_front()
	{
		if (head == nullptr)
			return;

		nodeSize--;
		if (head->next == nullptr)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			return;
		}

		Node *next = head->next;
		next->pre = nullptr;
		delete head;
		head = next;
	}

	//	Lst1.push_back() 在list的末尾添加一个元素
	void push_back(const T &t)
	{
		nodeSize++;
		Node *node = new Node(t);
		if (tail == nullptr)
		{
			head = node;
			tail = node;
		}
		else {
			tail->next = node;
			node->pre = tail;
			tail = node;
		}
	}
	//	Lst1.push_front() 在list的头部添加一个元素
	void  push_front(const T&t)
	{
		nodeSize++;
		Node *node = new Node(t);
		if (head == nullptr) {
			head = node;
			tail = node;
		}
		else {
			node->next = head;
			head->pre = node;
			head = node;
		}
	}

	//	Lst1.remove() 从list删除元素
	void remove(const T& t)
	{
		Node *node = head;
		Node *next;
		Node *pre;
		while (node != nullptr)
		{
			if (node->v != t) {
				node = node->next;
				continue;
			}

			nodeSize--;
			if (node == head && node == tail)
			{
				delete node;
				head = nullptr;
				tail = nullptr;
				break;
			}
			else if (node == head) {
				next = node->next;
				if (next)
					next->pre = nullptr;
				delete node;
				head = next;
				node = next;
			}
			else if (node == tail) {
				pre = node->pre;
				if (pre)
					pre->next = nullptr;
				delete node;
				tail = pre;
				node = nullptr;
			}
			else {
				next = node->next;
				pre = node->pre;
				next->pre = pre;
				pre->next = next;

				delete node;
				node = next;
			}
		}
	}
	//	aremove_if() 按指定条件删除元素
	void remove_if() {

	}

	void clear()
	{
		Node *p = head;
		while (p != nullptr)
		{
			Node *node = p;
			p = p->next;
			delete node;
		}
		head = nullptr;
		tail = nullptr;
	}

	//	Lst1.size() 返回list中的元素个数
	int size() const
	{
		return nodeSize;
	}

	//重写赋值=
	List& operator=(const List &right) {
		if (this == &right)
			return *this;

		clear();
		Node *node = right.head;
		Node *pre = nullptr;
		while (node)
		{
			Node *newNode = new Node(node->v);
			if (head == nullptr)
				head = newNode;
			newNode->pre = pre;
			if (pre)
				pre->next = newNode;
			pre = newNode;
			node = node->next;
		}
	}
};

