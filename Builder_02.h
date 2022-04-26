#pragma once
#include <iostream>
#include <vector>
#include <memory>

//Строитель — это порождающий паттерн проектирования, который позволяет создавать сложные объекты пошагово.
//Строитель даёт возможность использовать один и тот же код строительства для получения разных представлений объектов.

struct Infantryman final
{
	void info() {
		std::cout << "Infantryman" << '\n';
	}
};

struct Archer final
{
	void info() {
		std::cout << "Archer" << '\n';
	}
};

struct Horseman final
{
	void info() {
		std::cout << "Horseman" << '\n';
	}
};

struct Catapult final
{
	void info() {
		std::cout << "Catapult" << '\n';
	}
};

struct Elephant final
{
	void info() {
		std::cout << "Elephant" << '\n';
	}
};

class Army final
{
public:
	void info() {
		for (auto &&infantryman : vi) infantryman->info();
		for (auto &&archer : va) archer->info();
		for (auto &&horseman : vh) horseman->info();
		for (auto &&catapult : vc) catapult->info();
		for (auto &&elephant : ve) elephant->info();
	}
	void infoSizeArmy() const {
		std::cout << vi.size() << '\n';
		std::cout << va.size() << '\n';
		std::cout << vh.size() << '\n';
		std::cout << vc.size() << '\n';
		std::cout << ve.size() << '\n';
	}

	//seters
	void setInfantryman(std::unique_ptr<Infantryman> infantrymen) {
		vi.emplace_back(std::move(infantrymen));
	}
	void setArcher(std::unique_ptr<Archer> archer) {
		va.emplace_back(std::move(archer));
	}
	void setHorseman(std::unique_ptr<Horseman> horseman) {
		vh.emplace_back(std::move(horseman));
	}
	void setCatapult(std::unique_ptr<Catapult> catapult) {
		vc.emplace_back(std::move(catapult));
	}
	void setElephant(std::unique_ptr<Elephant> elephant) {
		ve.emplace_back(std::move(elephant));
	}


private:
	std::vector<std::unique_ptr<Infantryman>> vi;
	std::vector<std::unique_ptr<Archer>> va;
	std::vector<std::unique_ptr<Horseman>> vh;
	std::vector<std::unique_ptr<Catapult>> vc;
	std::vector<std::unique_ptr<Elephant>> ve;
};


//Builder
class ArmyBuilder
{
public:
	virtual ~ArmyBuilder() = default;

	void createArmy() { m_army = std::make_unique<Army>(); }
	[[nodiscard]] std::unique_ptr<Army> getArmy() { return std::move(m_army); }

	virtual void buildInfantryman() = 0;
	virtual void buildArcher() = 0;
	virtual void buildHorseman() = 0;
	virtual void buildCatapult() = 0;
	virtual void buildElephant() = 0;
protected:
	std::unique_ptr<Army> m_army;
};

//concrete builder
class RomanArmyBuilder final : public ArmyBuilder
{
public:
	void buildInfantryman() override { m_army->setInfantryman(std::unique_ptr<Infantryman>{}); }
	void buildArcher() override { m_army->setArcher(std::unique_ptr<Archer>{}); }
	void buildHorseman() override { m_army->setHorseman(std::unique_ptr<Horseman>{}); }
	void buildCatapult() override { m_army->setCatapult(std::unique_ptr<Catapult>{}); }
	void buildElephant() override {}	//not included
};

//concrete builder
class CarthaginianArmyBuilder final : public ArmyBuilder
{
public:
	void buildInfantryman() override { m_army->setInfantryman(std::unique_ptr<Infantryman>{}); }
	void buildArcher() override { m_army->setArcher(std::unique_ptr<Archer>{}); }
	void buildHorseman() override { m_army->setHorseman(std::unique_ptr<Horseman>{}); }
	void buildElephant() override { m_army->setElephant(std::unique_ptr<Elephant>{}); }
	void buildCatapult() override {}	//not included
};

class Director final
{
public:
	void createArmy(std::unique_ptr<ArmyBuilder> builder) {
		m_army_builder = std::move(builder);
		m_army_builder->createArmy();
		m_army_builder->buildInfantryman();
		m_army_builder->buildArcher();
		m_army_builder->buildHorseman();
		m_army_builder->buildCatapult();
		m_army_builder->buildElephant();
	}
	//for custom army
	void createInfArchHors(std::unique_ptr<ArmyBuilder> army_builder) {
		m_army_builder = std::move(army_builder);
		m_army_builder->createArmy();
		m_army_builder->buildInfantryman();
		m_army_builder->buildArcher();
		m_army_builder->buildHorseman();
	}
	void printArmy() { m_army_builder->getArmy()->info(); }
private:
	std::unique_ptr<ArmyBuilder> m_army_builder;
};


#if 0
int main() {
	auto dir = std::make_unique<Director>();
	auto ra_builder = std::make_unique<RomanArmyBuilder>();
	auto ca_builder = std::make_unique<CarthaginianArmyBuilder>();

	dir->createArmy(std::move(ra_builder));
	std::cout << "Roman army:" << '\n';
	dir->printArmy();
	std::cout << "\nCarthaginian army:" << '\n';
	dir->createArmy(std::move(ca_builder));
	dir->printArmy();
}
#endif
