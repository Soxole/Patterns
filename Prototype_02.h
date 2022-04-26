#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <array>

/*


*/

using std::string;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::make_unique;



class Stooge
{
public:
	virtual void slap_stick() const = 0;
	virtual unique_ptr<Stooge> clone() const = 0;
	virtual ~Stooge() = default;
};


class Larry : public Stooge
{
public:
	void slap_stick() const override
	{
		cout << "class Larry " << endl;
	}
	[[nodiscard]] unique_ptr<Stooge> clone() const noexcept override
	{
		return make_unique<Larry>();
	}
};


class Moe final : public Stooge
{
public:
	void slap_stick() const override
	{
		cout << "class Moe " << endl;
	}
	[[nodiscard]] unique_ptr<Stooge> clone() const noexcept override
	{
		return make_unique<Moe>();
	}
};

//������� 
class Factory
{
public:
	[[nodiscard]] static unique_ptr<Stooge> make_stooge(int choice)
	{
		return s_prototypes[choice]->clone();
	}
protected:
	static inline const size_t amountPtrDerivedClass = 3;			//сумма указателей производных классов Larry, Moe
	static inline std::array<unique_ptr<Stooge>, amountPtrDerivedClass> s_prototypes = {		//using std::array<> !!!
		nullptr, make_unique<Larry>(), make_unique<Moe>()
	};
};


/*
	int main()
	{

		vector<unique_ptr<Stooge>> vecProt;

		auto objLarry = Factory::make_stooge(1);
		auto objMoe = Factory::make_stooge(2);
		vecProt.emplace_back(move(objMoe));						<--������������ std::move(), ��� ���������� ��������� � ������ ����������
		vecProt.emplace_back(move(Factory::make_stooge(2)));	// ��� ���������� �������� ������� ����� ������� ����� ��������
		vecProt.emplace_back(move(objLarry));

		for (const auto &it : vecProt)
			it->slap_stick();

		return 0;
	}

*/
