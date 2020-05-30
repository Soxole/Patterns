#pragma once
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <deque>

using std::vector;
using std::deque;
using std::cout;
using std::endl;


//предварительное объявление шаблона класса
template<typename T> class Stack;
template<typename T>
inline std::ostream &operator<<(std::ostream &os, Stack<T> &st)
{
	for (auto it = st.elems.crbegin(); it != st.elems.crend(); it++)
		os << *it << " ";
	return os;
}



template<typename T>
class Stack
{
public:
	Stack() = default;
	Stack(const T &elem_) { push(elem_); }
	~Stack() {}

	void push(T const &elem);
	void pop();
	T const &top() const;
	bool empty() const { return elems.empty(); }
	void showStack() const;
	void showStack_on(std::ostream &os) const;

	//реализация оператора = для других типов; Присваивание стека с элементами типа Т2
	template<typename T2>
	Stack& operator= (Stack<T2> const&);

private:
	deque<T> elems;
	friend std::ostream &operator<< <T>(std::ostream &os, Stack &st);
};

template<typename T>
inline void Stack<T>::push(T const &elem)
{
	elems.emplace_back(elem);
}

template<typename T>
inline void Stack<T>::pop()
{
	assert(!elems.empty());
	elems.pop_back();
}

template<typename T>
inline T const &Stack<T>::top() const
{
	assert(!elems.empty());
	return elems.back();
}

template<typename T>
inline void Stack<T>::showStack() const
{
	std::copy(elems.crbegin(), elems.crend(), std::ostream_iterator<T>(cout, " "));
}

template<typename T>
inline void Stack<T>::showStack_on(std::ostream &os) const
{
	//st.showStack_on(cout); in main()
	for (auto it = elems.crbegin(); it != elems.crend(); it++)
		os << *it << " ";
}

template<typename T>
template<typename T2>
inline Stack<T> &Stack<T>::operator=(Stack<T2> const &op2)
{
	Stack<T2> tmp(op2);
	elems.clear();

	while (!tmp.empty())
	{
		elems.push_front(tmp.top());
		tmp.pop();
	}

	return *this;
}


//функция из примера (не main())
//shared_ptr<Person> initFamily(const string &name)
//{
//	shared_ptr<Person> mom(make_shared<Person>(name + "'s mom"));
//	shared_ptr<Person> dad(make_shared<Person>(name + "'s dad"));
//	shared_ptr<Person> kid(make_shared<Person>(name, mom, dad));
//	mom->kids.emplace_back(kid);
//	dad->kids.emplace_back(kid);
//
//	return kid;
//}