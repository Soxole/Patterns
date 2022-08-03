#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

//TITLE: Strategy
/*
 Стратегия — это поведенческий паттерн проектирования, который определяет
 семейство схожих алгоритмов и помещает каждый из них в собственный класс,
 после чего алгоритмы можно взаимозаменять прямо во время
 исполнения программы.

 Когда вам нужно использовать разные вариации какого-то алгоритма внутри одного объекта.
 */

class Strategy
{
public:
	Strategy() = default;
	Strategy(Strategy const &) = default;
	Strategy &operator=(Strategy const &) = default;
	Strategy(Strategy &&) noexcept = default;
	Strategy &operator=(Strategy &&) noexcept = default;
	virtual ~Strategy() = default;

	[[nodiscard]]
	virtual std::string do_algorithm(const std::vector<std::string> &data) const = 0;
};

//class Context is stored pointer to the class Strategy
class Context
{
public:
	explicit Context(std::unique_ptr<Strategy> strategy = nullptr)
	: m_strategy(std::move(strategy)) {}

	void set_strategy(std::unique_ptr<Strategy> strategy) {
		m_strategy = std::move(strategy);
	}

	void do_some_business_logic() const {
		std::cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
		const std::vector<std::string> setStrings{"a", "e", "c", "b", "d"};
		std::cout << m_strategy->do_algorithm(setStrings) << '\n';
	}
private:
	std::unique_ptr<Strategy> m_strategy;
};

class ConcreteStrategy_A final : public Strategy
{
public:
	[[nodiscard]]
	std::string do_algorithm(const std::vector<std::string> &data) const override {
		std::string result;
		std::ranges::for_each(data,[&result](const auto &letter) {result.append(letter); });
		std::ranges::sort(result);

		return result;
	}
};

class ConcreteStrategy_B final : public Strategy
{
public:
	[[nodiscard]]
	std::string do_algorithm(const std::vector<std::string> &data) const override {
		std::string result;
		std::ranges::for_each(data,[&result](const auto &letter) {result.append(letter); });
		std::ranges::sort(result);
		std::ranges::reverse(result);

		return result;
	}
};

//main()
#if 0
void clientCode() {
	auto m_context = std::make_unique<Context>(std::make_unique<ConcreteStrategy_A>());
	std::cout << "Client: Strategy is set to normal sorting.\n";
	m_context->do_some_business_logic();
	std::cout << "\n";
	std::cout << "Client: Strategy is set to reverse sorting.\n";
	m_context->set_strategy(std::make_unique<ConcreteStrategy_B>());
	m_context->do_some_business_logic();
}
#endif
