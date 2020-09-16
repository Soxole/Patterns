#pragma once

#include <iostream>
#include <string>
#include <memory>

class Target
{
public:
	virtual~Target() = default;
	virtual std::string requesT() const {
		return "Target: the default target's behavior.";
	}
};

//класс, который нужно адаптировать
class Adaptee
{
public:
	std::string specificRequest() const {
		return ".eetpadA eht fo roivaheb laicepS";
	}
};


//сам адаптер, который наследуется от public Target
class Adapter : public Target
{
public:
	Adapter() = default;
	Adapter(std::unique_ptr<Adaptee> ptrAdapt) : ptrAdaptee(std::move(ptrAdapt)) 
	{
	}
	~Adapter() = default;
	virtual std::string requesT() const override {
		std::string to_reverse = this->ptrAdaptee->specificRequest();
		std::reverse(to_reverse.begin(), to_reverse.end());
		return "Adapter: (tranclated) " + to_reverse;
	}
private:
	std::unique_ptr<Adaptee> ptrAdaptee;
};

/*
	unique_ptr<Target> pTarget = make_unique<Adapter>(make_unique<Adaptee>());
	cout << pTarget->requesT() << endl;
	unique_ptr<Target> pTargetTwo( make_unique<Target>() );
	cout << pTargetTwo->requesT() << endl;
	unique_ptr<Adaptee> pTargetThree( make_unique<Adaptee>() );
	cout << pTargetThree->specificRequest() << endl;
*/