#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

//TITLE: Strategy
/*
 Стратегия — это поведенческий паттерн проектирования, который определяет семейство схожих алгоритмов и
 помещает каждый из них в собственный класс, после чего алгоритмы можно взаимозаменять прямо во время
 исполнения программы.

 Когда вам нужно использовать разные вариации какого-то алгоритма внутри одного объекта.
 */

class Strategy
{
public:
	virtual ~Strategy() = default;
	[[nodiscard]] virtual std::string do_algorithm(const std::vector<std::string> &data) const = 0;
};

//class Context is stored pointer to the class Strategy
class Context
{
	std::unique_ptr<Strategy> strategy_;

public:
	Context(std::unique_ptr<Strategy> strategy = nullptr) : strategy_(std::move(strategy))
	{
	}
	~Context() = default;

	void set_strategy(std::unique_ptr<Strategy> strategy)
	{
		strategy_ = std::move(strategy);
	}

	void do_some_business_logic() const
	{
		std::cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
		std::cout << strategy_->do_algorithm(std::vector<std::string>{"a", "e", "c", "b", "d"});
		//std::cout << result << '\n';
	}
};

//strategy A
class ConcreteStrategy_A : public Strategy
{
public:
	[[nodiscard]] std::string do_algorithm(const std::vector<std::string>& data) const override
	{
		std::string result;
		std::for_each(std::begin(data), std::end(data), 
			[&result](const auto &letter){result.append(letter);});
		std::sort(std::begin(result), std::end(result));
		
		return result;
	}
};

//strategy B
class ConcreteStrategy_B : public Strategy
{
public:
	[[nodiscard]] std::string do_algorithm(const std::vector<std::string>& data) const override
	{
		std::string result;
		std::for_each(std::begin(data), std::end(data), 
			[&result](const auto &letter){result.append(letter);});
		
		std::sort(std::begin(result), std::end(result));
		std::reverse(result.begin(), result.end());		
		//for (size_t i = 0; i < result.length() / 2; ++i)
		//{
		//	std::swap(result[i], result[result.length() - i - 1]);
		//}
		return result;
	}
};

/*
 *
void clientCode()
{
	auto m_context = make_unique<Context>(make_unique<ConcreteStrategy_A>());
	std::cout << "Client: Strategy is set to normal sorting.\n";
	m_context->do_some_business_logic();
	std::cout << "\n";
    std::cout << "Client: Strategy is set to reverse sorting.\n";
	m_context->set_strategy(make_unique<ConcreteStrategy_B>());
	m_context->do_some_business_logic();
}

 * 
 */