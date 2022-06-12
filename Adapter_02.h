#pragma once
#include <string>
#include <memory>

class Target
{
public:
	virtual~Target() = default;
	[[nodiscard]] virtual std::string request() const {
		return "Target: the default target's behavior.";
	}
};

class Adaptee final
{
public:
	[[nodiscard]] std::string specificRequest() const {
		return ".eetpadA eht fo roivaheb laicepS";
	}
};


class Adapter : public Target
{
public:
	Adapter() = default;
	Adapter(std::unique_ptr<Adaptee> ptrAdapt) : m_ptrAdaptee(std::move(ptrAdapt)) { }

	[[nodiscard]] std::string request() const override {
		std::string to_reverse = m_ptrAdaptee->specificRequest();
		std::reverse(to_reverse.begin(), to_reverse.end());

		return "Adapter: (tranclated) " + to_reverse;
	}
private:
	std::unique_ptr<Adaptee> m_ptrAdaptee;
};


//main()
#if 0

void clientCode(const Target &target)
{
	std::cout << target.request();
}

std::cout << "Client: I can work just fine with the Target objects:\n";
auto target = std::make_unique<Target>();
clientCode(*target);
std::cout << "\n\n";
auto adaptee = std::make_unique<Adaptee>();
std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
std::cout << "Adaptee: " << adaptee->specificRequest();
std::cout << "\n\n";
std::cout << "Client: But I can work with it via the Adapter:\n";
auto adapter = std::make_unique<Adapter>(move(adaptee));
clientCode(*adapter);
std::cout << "\n";

#endif
