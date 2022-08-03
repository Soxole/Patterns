#pragma once
#include <vector>
#include <memory>


//TITLE: Iterator
/*
Итератор — это поведенческий паттерн проектирования, который даёт возможность
последовательно обходить элементы составных объектов, не раскрывая их внутреннего
представления.
this code gives off a smell
 */

template<typename C>
class Container;

template<typename T, typename U>
class Iterator final
{
public:
	using iter_type = typename std::vector<T>::iterator;
	Iterator(U *data, bool reverse = false)
		: m_ptr_data(data), m_iter(m_ptr_data->m_vec_data.begin())
	{ }

	void first() { m_iter = m_ptr_data->m_vec_data.begin(); }
	void next() { ++m_iter; }
	bool isDone(){
		return m_iter == m_ptr_data->m_vec_data.end();
	}
	iter_type current() { return m_iter; }
private:
	U *m_ptr_data;
	iter_type m_iter;
};

template<typename C>
class Container final
{
	friend class Iterator<C, Container>;
public:
	Container() = default;
	Container(size_t s) : m_vec_data(s) {}
	void add(C &&value) { m_vec_data.emplace_back(value); }
	[[nodiscard]] auto createIterator() {
		return std::make_unique<Iterator<C, Container>>(this);
	}
	auto &get() { return m_vec_data; }
private:
	std::vector<C> m_vec_data;
};

class Data final
{
public:
	Data(int data = 0) : m_data(data) {}
	void set_data(int data) { m_data = data; }
private:
	int m_data;
};

//main()
#if 0
	Container<int> cont(10);
	std::iota(cont.get().begin(), cont.get().end(), 1);
	std::copy(cont.get().begin(), cont.get().end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << '\n';
	auto it = cont.createIterator();
	for (it->first(); !it->isDone(); it->next()) {
		std::cout << *it->current() << std::endl;
	}
#endif
