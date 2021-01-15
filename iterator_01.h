#pragma once
#include <cstdint>

/*
 Iterator предоставл€ет последовательный способ доступа к элементам коллекции, не раскрыва€ внутренней структуры.
 ѕапки с документами €вл€ютс€ коллекци€ми. ¬ офисных услови€х, когда доступ к документам осуществл€етс€ через
 администратора или секретар€, именно секретарь выступает в качестве Iterator.
 */

class Stack
{
public:
	friend class StackIter;		//дружественное объ€вление
	
	Stack() : m_sp(-1)
	{
	}
	explicit Stack(const Stack &st) = default;
	explicit Stack(Stack &&st) = default;
	
	
	void push(const int &in)
	{
		m_items[++m_sp] = in;
	}
	int pop()
	{
		return m_items[m_sp--];
	}
	[[nodiscard]] bool is_empty() const
	{
		return (m_sp == -1);
	}
	

private:
	inline static const int32_t size_stack = 10;
	int32_t m_items[size_stack] {};
	int32_t m_sp;
};


class StackIter
{
public:
	explicit StackIter(const Stack &st) : m_st_(st)
	{
		m_index_= 0;
	}
	void operator++()
	{
		m_index_++;
	}
	bool operator()() const
	{
		return (m_index_ != m_st_.m_sp + 1);
	}
	int operator*() const
	{
		return m_st_.m_items[m_index_];
	}

private:
	const Stack &m_st_;
	int32_t m_index_{};
};

/*
 bool operator == (const Stack &left_stack, const Stack &right_stack)
{
	StackIter it_l(left_stack), it_r(right_stack);
	for (; it_l(); ++it_l, ++it_r)
	{
		if (*it_l != *it_r)
			break;
	}
	return !it_l() && !it_r();
}

int main()
{
	Stack st1;
	for (int i = 1; i < 5; ++i)
	{
		st1.push(i);
	}
	Stack s2(st1), s3(st1), s4(st1), s5(st1);
	s3.pop();
	s5.pop();
	s4.push(2);
	s5.push(9);
	cout << "1 == 2 is " << (st1 == s2) << endl;
	cout << "1 == 3 is " << (st1 == s3) << endl;
	cout << "1 == 4 is " << (st1 == s4) << endl;
	cout << "1 == 5 is " << (st1 == s5) << endl;
 
 */