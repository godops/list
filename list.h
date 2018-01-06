#pragma once
#ifndef LIST_H
#define LIST_H
#include<assert.h>
#include<iostream>
template<class T>
class list {
	friend class Myiterator;
protected:
	struct list_node
	{
		list_node *prev;
		list_node *next;
		T data;
	};
private:
	list_node* head;
	list_node* last;
	int size;
public:
	list() :head(NULL), last(NULL), size(0) {}
	list(const list&);
	list(T, int);
	list(T);
	~list() { this->clear(); }

	
	class Myiterator {
		friend class list<T>;
	protected:
		list_node *snode;
		Myiterator() {}
		Myiterator(list_node* x) :snode(x) {}
	public:
		bool operator==(const Myiterator& x) const { return snode == x.snode; }
		bool operator!=(const  Myiterator& x) const { return snode != x.snode; }
		T operator*() const { return snode->data; }
		Myiterator& operator++() {
			snode = snode->next;
			return *this;
		}
		Myiterator& operator--() {
			snode = snode->prev;
			return *this;
		}
		Myiterator& operator =(Myiterator& it) {
			snode = it.snode;
			return *this;
		}
	};


	void push_back(const T&x);
	void pop_back();
	void clear();
	void insert(Myiterator &it,const T& x);
	void push_front(const T&x);
	void pop_front();
	void reserve();
	void swap(list<T>&lst);
	friend void swap(Myiterator& it1, Myiterator& it2) {
		int tmp = (it1.snode)->data;
		(it1.snode)->data = (it2.snode)->data;
		(it2.snode)->data = tmp;
	}
	Myiterator erase(Myiterator& it) {
		assert(0 != size);
		size--;
		if (size == 0) {
			head = NULL;
			end = NULL;
			delete(it.snode);
			return iterator(NULL);
		}
		if (it.Iter == head)
		{
			list_node *tp = head;
			head = head->next;
			head->prev = NULL;
			delete(tp);
			return MyIterator(head);
		}
		if (it.Iter == last)
		{
			list_node *tp = last;
			last = last->prev;
			last->next = NULL;
			delete(tp);
			return MyIterator(NULL);
		}
		(it.snode)->prev->next = (it.snode)->next;
		(it.snode)->next->prev = (it.snode)->prev;
		list_node *ans = it.snode->next;
		delete(it.snode);
		return MyIterator(ans);
	}
	Myiterator find(T& x) {
		list_node *node = head;
		for (; node != NULL; node = node->next)
		{
			if (node->data == x)return Myiterator(node);
		}
		return Myiterator(NULL);
	}
	T& operator[](int n) {
		list_node* tp = head;
		while (n--)
			tp = tp->next;
		return tp->data;
	}
	void reset(Myiterator& it, int val) {
		list_node *tmp = head;
		while (tmp!=it)
		{
			tmp = tmp->next;
		}
		tmp->data = val;
	}
	Myiterator operator=(list<T> &ist) {
		if ((*this).head == ist.head)
			return *this;
		(*this).clear();
		if (ist.head == NULL) {
			this->head = NULL;
			this->last = NULL;
			return *this;
		}
		head = ist.head;
		last = this->last;
		return *this;
	}
	Myiterator begin() { return  Myiterator(head); }
	Myiterator end() { return  Myiterator(last); }
	Myiterator front() { return head->data; }
	Myiterator back() { return last->data; }
	int Mysize() { return size; }
	bool empty() { return size == 0; }
};


template<class T>
list<T>::list(T val)
{
	list_node *tp = new list_node;
	tp->data = val;
	size = 1;
	head = tp;
	last = tp;
	last->prev = NULL;
	head->next = NULL;
}
// 对否 待定？  
template<class T>
list<T>::list(T val, int n)
{
	size = n;
	if (size != 0)
	{
		list_node *tp = new list_node;
		tp->data = val;
		head = tp;
		last = tp;
		head->prev = NULL;
		for (int i = 1; i<n; i++)
		{
			list_node *tp = new list_node;
			tp->data = val;
			tp->prev = last;
			last->next = tp;
			last = tp;
		}
		last->next = NULL;
	}
}
template<class T>
list<T>::list(const list<T>& list0)
{
	size = list0.size;
	list_node *cur0 = list0.head;
	list_node *tp = new list_node;
	tp->data = cur0->data;
	head = tp;
	last = tp;
	head->prev = NULL;
	while (cur0->next != NULL)
	{
		cur0 = cur0->next;
		list_node *tp = new list_node;
		tp->data = cur0->data;
		tp->prev = last;
		last->next = tp;
		last = tp;
	}
	last->next = NULL;

}
template<class T>
void list<T>::clear()
{
	list_node *tp;
	for (; size != 0; size--)
	{
		tp = head;
		head = head->next;
		delete tp;
	}
	tp = NULL;
}
template<class T>
void list<T>::push_back(const T& val)
{
	list_node *tp = new list_node;
	tp->data = val;
	size++;
	if (1 == size)
	{
		head = tp;
		last = tp;
		head->prev = NULL;
		last->next = NULL;
	}
	else
	{
		last->next = tp;
		tp->prev = last;
		last = tp;
		last->next = NULL;
	}
}

// push_front  
template<class T>
void list<T>::push_front(const T& val)
{
	list_node *tp = new list_node;
	tp->data = val;
	size++;
	if (1 == size)
	{
		head = tp;
		last = tp;
		head->prev = NULL;
		last->next = NULL;
	}
	else
	{
		tp->next = head;
		head->prev = tp;
		head = tp;
		head->prev = NULL;
	}
}
// pop_back  
template<class T>
void list<T>::pop_back()
{
	assert(last != NULL);
	size--;
	list_node *tp = last;
	last = last->prev;
	last->next = NULL;
	delete tp;
	tp = NULL;
}

// pop_front  
template<class T>
void list<T>::pop_front()
{
	assert(head != NULL);
	size--;
	list_node *tp = head;
	head = head->next;
	head->prev = NULL;
	delete tp;
	tp = NULL;
}
// reverse  
template<class T>
void list<T>::reserve()
{
	list_node *le = head;
	list_node *ri = last;
	for (int c = size; c>1; c -= 2)
	{
		// 值交换，指针交换？？  
		le->data ^= ri->data;
		ri->data ^= le->data;
		le->data ^= ri->data;
		le = le->next;
		ri = ri->prev;
	}
}
template<class T>
void list<T>::swap(list<T>& list0)
{
	// 交换head  
	list_node *tp = head->next;
	head->next = (list0.head)->next;
	(list0.head)->next->prev = head;
	(list0.head)->next = tp;
	tp->prev = list0.head;
	// 交换size  
	size ^= list0.size;
	list0.size ^= size;
	size ^= list0.size;
	// 交换head->data  
	head->data ^= (list0.head)->data;
	(list0.head)->data ^= head->data;
	head->data ^= (list0.head)->data;
	// 交换rear  
	tp = last->prev;
	last->prev = (list0.last)->prev;
	(list0.last)->prev->next = last;
	(list0.last)->prev = tp;
	tp->next = list0.last;
	//交换rear->data  
	last->data ^= (list0.last)->data;
	(list0.last)->data ^= last->data;
	last->data ^= (list0.last)->data;
}
template<class T>
void list<T>::insert(Myiterator& it, const T& val)
{
	list_node *tp = new list_node;
	tp->data = val;
	if (NULL == it.node->next)
	{// 尾的后面  
		last->next = tp;
		tp->prev = last;
		last = tp;
		size++;
	}
	else
	{
		tp->next = (it.node)->next;
		(it.node)->next->prev = tp;
		(it.node)->next = tp;
		tp->prev = (it.node);
		size++;
	}
}
#endif // !LIST_H
