#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <array>

/*
ѕрототип Ч это порождающий паттерн проектировани€, который позвол€ет копировать объекты, 
не вдава€сь в подробности их реализации.

*/

using std::string;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::make_unique;



class Stooge
{
public:
	virtual void slap_stick() = 0;
	virtual unique_ptr<Stooge> clone() = 0;
	virtual ~Stooge() = default;
};


class Larry : public Stooge
{
public:
	virtual void slap_stick() override
	{
		cout << "class Larry " << endl;
	}
	[[nodiscard]] virtual unique_ptr<Stooge> clone() override
	{
		return make_unique<Larry>();
	}
};


class Moe final : public Stooge
{
public:
	virtual void slap_stick() override
	{
		cout << "class Moe " << endl;
	}
	[[nodiscard]] virtual unique_ptr<Stooge> clone() override
	{
		return make_unique<Moe>();
	}
};

//фабрика 
class Factory
{
public:
	static inline unique_ptr<Stooge> make_stooge(int choice)
	{
		return s_prototypes[choice]->clone();
	}
protected:
	static inline const size_t amountPtrDerivedClass = 3;			//сумма указателей производных классов Larry, Moe
	static inline std::array<unique_ptr<Stooge>, amountPtrDerivedClass> s_prototypes = {		//using std::array<> !!!с вектором при завершении удал€ютс€ ссылки
		nullptr, make_unique<Larry>(), make_unique<Moe>()
	};

};


/*
	int main()
	{

		vector<unique_ptr<Stooge>> vecProt;

		auto objLarry = Factory::make_stooge(1);
		auto objMoe = Factory::make_stooge(2);
		vecProt.emplace_back(move(objMoe));						<--об€зательный std::move(), при добавлении указател€ в вектор указателей
		vecProt.emplace_back(move(Factory::make_stooge(2)));	// при добавлении похожего объекта лучше вызвать метов напр€мую
		vecProt.emplace_back(move(objLarry));

		for (const auto &it : vecProt)
			it->slap_stick();

		return 0;
	}

*/
