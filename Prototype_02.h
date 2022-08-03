#pragma once
#include <iostream>
#include <memory>
#include <array>

/*
Prototype is a creational design pattern that allows cloning objects, even complex ones, without coupling to
their specific classes.

All prototype classes should have a common interface that makes it possible to copy objects even if their
concrete classes are unknown. Prototype objects can produce full copies since objects of the same class
can access each other’s private fields.
*/


class Stooge
{
public:
	virtual void slapStick() const = 0;
	[[nodiscard]] virtual std::unique_ptr<Stooge> clone() const = 0;
	virtual ~Stooge() = default;
};


class Larry final : public Stooge
{
public:
	void slapStick() const override {
		std::cout << "class Larry " << '\n';
	}
	[[nodiscard]] std::unique_ptr<Stooge> clone() const override {
		return std::make_unique<Larry>();
	}
};


class Moe final : public Stooge
{
public:
	void slapStick() const override {
		std::cout << "class Moe " << '\n';
	}
	[[nodiscard]] std::unique_ptr<Stooge> clone() const override {
		return std::make_unique<Moe>();
	}
};


class FactoryPrototype final
{
public:
	[[nodiscard]] static std::unique_ptr<Stooge> makeStooge(int choice) {
		return s_prototypes_[choice]->clone();
	}
protected:
	static constexpr size_t amount_ptr_derived_class = 3;										//сумма указателей производных классов Larry, Moe
	static inline std::array<std::unique_ptr<Stooge>, amount_ptr_derived_class> s_prototypes_ = //using std::array<> !!!
	{ nullptr, std::make_unique<Larry>(), std::make_unique<Moe>() };
};


//main()
#if 0
int main() {
	std::vector<std::unique_ptr<Stooge>> vecProt;

	auto objLarry = FactoryPrototype::makeStooge(1);
	auto objMoe = FactoryPrototype::makeStooge(2);
	vecProt.emplace_back(move(objMoe));
	vecProt.emplace_back(move(FactoryPrototype::makeStooge(2)));
	vecProt.emplace_back(move(objLarry));

	for (const auto &it : vecProt)
		it->slapStick();

}
#endif


