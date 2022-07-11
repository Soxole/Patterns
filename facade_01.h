#pragma once
#include <iostream>
#include <memory>
#include <string>


/*
 Фасад - это структурный паттерн проектирования, который предоставляет простой интерфейс к сложной системе классов,
 библиотеке или фреймворку.
 Фасад - это простой интерфейс для работы со сложной подсистемой, содержащей множество классов.
 Фасад может иметь урезанный интерфейс, не имеющий 100% функциональности, которой можно достичь,
 используя сложную подсистему напрямую. Ќо он предоставляет именно те фичи, которые нужны клиенту,
 и скрывает все остальные.
 Фасад полезен, если вы используете какую-то сложную библиотеку со множеством подвижных частей,
 но вам нужна только часть её возможностей.

 паттерн Facade "обертывает" сложную подсистему более простым интерфейсом.
 */

class Musician
{
public:
	Musician(std::string_view name) : m_name(name) { }
	virtual ~Musician() = default;

protected:
	void print(const std::string_view text) const
	{
		std::cout << m_name << " " << text << "." << "\n";
	}
private:
	std::string m_name;
};


//concrete musicians
class Vocalist final : public Musician
{
public:
	explicit Vocalist(const std::string_view name) : Musician(name) { }

	void singCouplet(const int coupletNumber) const
	{
		std::string text{ "sang couplet #" };
		text += std::to_string(coupletNumber);
		print(text);
	}
	void sangChorus() const
	{
		print("sang chorus");
	}
};

class Guitarist final : public Musician
{
public:
	explicit Guitarist(const std::string_view name) : Musician(name) { }

	void playCoolOpening() const
	{
		print("start with a cool opening");
	}
	void playCoolRiffs() const
	{
		print("play cool riffs");
	}
	void playOtherCoolRiffs() const
	{
		print("play other cool riffs");
	}
	void playIncrediblyCoolSolo() const
	{
		print("play a incredibly cool solo");
	}
	void playFinalAccord() const
	{
		print("finish the song a powerful accord");
	}
};

class Bassist final : public Musician
{
public:
	explicit Bassist(const std::string_view name) : Musician(name) { }

	void followTheDrums() const
	{
		print("follow the drums");
	}
	void changeRhythm(const std::string_view type) const
	{
		std::string text = ("change the rhythm");
		text += type;
		text += "a";
		print(text);
	}
	void stopPlaying() const
	{
		print("stop playing");
	}
};

class Drummer final : public Musician
{
public:
	explicit Drummer(const std::string_view name) : Musician(name) { }

	void startPlaying() const
	{
		print("start playing");
	}
	void stopPlaying() const
	{
		print("stopPlaying");
	}
};

//Facade - in this case a famous group
class BlackSabbath final
{
public:
	BlackSabbath() :
		m_vocalist(std::make_unique<Vocalist>("Ozzi Ozborn")),
		m_guitarist(std::make_unique<Guitarist>("Tony Aismy")),
		m_bassist(std::make_unique<Bassist>("Gizer Batler")),
		m_drummer(std::make_unique<Drummer>("Bill Wourd"))
	{ }

	void playSong() const
	{
		m_guitarist->playCoolOpening();
		m_drummer->startPlaying();
		m_bassist->followTheDrums();
		m_guitarist->playCoolRiffs();
		m_vocalist->singCouplet(1);
		m_bassist->changeRhythm("chorus");
		m_guitarist->playOtherCoolRiffs();
		m_vocalist->sangChorus();
		m_bassist->changeRhythm("couplet");
		m_guitarist->playCoolRiffs();
		m_vocalist->singCouplet(2);
		m_bassist->changeRhythm("chorus");
		m_guitarist->playOtherCoolRiffs();
		m_vocalist->sangChorus();
		m_bassist->changeRhythm("couplet");
		m_guitarist->playIncrediblyCoolSolo();
		m_guitarist->playCoolRiffs();
		m_vocalist->singCouplet(3);
		m_bassist->changeRhythm("chorus");
		m_guitarist->playOtherCoolRiffs();
		m_vocalist->sangChorus();
		m_bassist->changeRhythm("couplet");
		m_guitarist->playCoolRiffs();
		m_bassist->stopPlaying();
		m_drummer->stopPlaying();
		m_guitarist->playFinalAccord();
	}

private:
	std::unique_ptr<Vocalist> m_vocalist;
	std::unique_ptr<Guitarist> m_guitarist;
	std::unique_ptr<Bassist> m_bassist;
	std::unique_ptr<Drummer> m_drummer;
};


//main()
#if 0
BlackSabbath band;
band.playSong();
#endif

