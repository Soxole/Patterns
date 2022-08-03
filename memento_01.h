#pragma once
#include <iostream>
#include <vector>
#include <memory>

//TITLE: Memento
/*
Снимок — это поведенческий паттерн проектирования, который позволяет сохранять и
восстанавливать прошлые состояния объектов, не раскрывая подробностей их реализации.
 */


class Memento final
{
public:
	friend class Originator;
	explicit Memento(const int32_t &state) : m_state_(state) {}

	void set_state(const int32_t state) {
		m_state_ = state;
	}

	[[nodiscard]] int32_t get_state() const {
		return m_state_;
	}
protected:
	int32_t m_state_{};
};


class Originator final
{
public:
	void set_state(const int32_t state) {
		std::cout << "Set state to " << state << "." << '\n';
		m_state_ = state;
	}

	[[nodiscard]] int32_t get_state() const {
		return m_state_;
	}

	void set_memento(std::shared_ptr<Memento> &&memento) {
		m_state_ = memento->get_state();
	}

	[[nodiscard]] auto create_memento() const {
		return std::make_shared<Memento>(m_state_);
	}
protected:
	int32_t m_state_{};
};


class CareTaker final
{
public:
	explicit CareTaker(std::shared_ptr<Originator> originator = nullptr)
		: m_originator_(std::move(originator)) {}

	void save() {
		std::cout << "Save state" << '\n';
		m_history_.emplace_back(m_originator_->create_memento());
	}

	void undo() {
		if (m_history_.empty()) {
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

//main()
#if 0
	auto originator{std::make_shared<Originator>()};
	auto caretaker{std::make_shared<CareTaker>(originator)};

	originator->set_state(1);
	caretaker->save();

	originator->set_state(2);
	caretaker->save();

	originator->set_state(3);
	caretaker->undo();


	std::cout << "Actual state is " << originator->get_state() << '\n';

#endif