#pragma once
#include <iostream>
#include <vector>
#include <memory>

//TITLE: Memento
/*
 Паттерн Снимок позволяет создавать любое количество снимков объекта и хранить их,
 независимо от объекта, с которого делают снимок. Снимки часто используют не только
 для реализации операции отмены, но и для транзакций, когда состояние объекта нужно
 «откатить», если операция не удалась.

 Паттерн предлагает изготовить снимок самому исходному объекту, поскольку ему
 доступны все поля, даже приватные.
 */


class Memento
{
public:	
	friend class Originator;
	explicit Memento(const int32_t &state) : m_state_(state)
	{
	}

	void set_state(const int32_t state)
	{
		m_state_ = state;
	}

	[[nodiscard]] int32_t get_state() const
	{
		return m_state_;
	}

protected:
	int32_t m_state_{};
};


class Originator
{
public:
	void set_state(const int32_t &state)
	{
		std::cout << "Set state to " << state << "." << '\n';
		m_state_ = state;
	}
	
	[[nodiscard]] int32_t get_state() const
	{
		return m_state_;
	}

	void set_memento(const std::shared_ptr<Memento> &memento)
	{
		m_state_ = memento->get_state();
	}

	[[nodiscard]] std::shared_ptr<Memento> create_memento() const
	{
		return std::make_shared<Memento>(m_state_);
	}

protected:
	int32_t m_state_{};
};


class CareTaker
{
public:
	CareTaker(std::shared_ptr<Originator> originator = nullptr)
		: m_originator_(std::move(originator))
	{
	}
	~CareTaker() = default;

	void save()
	{
		std::cout << "Save state" << '\n';
		m_history_.emplace_back(m_originator_->create_memento());
	}

	void undo()
	{
		if (m_history_.empty())
		{
			std::cout << "Unable to undo state." << '\n';
			return;
		}
		std::shared_ptr<Memento> memento = std::move(m_history_.back());
		m_originator_->set_memento(std::move(memento));
		std::cout << "Undo state." << '\n';
		m_history_.pop_back();		
	}

protected:
	std::shared_ptr<Originator> m_originator_;
	std::vector<std::shared_ptr<Memento>> m_history_;
};


/*
 	auto originator{make_shared<Originator>()};
	auto caretaker{make_shared<CareTaker>(originator)};

	originator->set_state(1);
	caretaker->save();

	originator->set_state(2);
	caretaker->save();

	originator->set_state(3);
	caretaker->undo();


	std::cout << "Actual state is " << originator->get_state() << '\n';
  
 */