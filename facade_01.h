#pragma once
#include <iostream>
#include <memory>
#include <string>


/*
 ‘асад Ч это структурный паттерн проектировани€, который предоставл€ет простой интерфейс к сложной системе классов,
 библиотеке или фреймворку.
 ‘асад Ч это простой интерфейс дл€ работы со сложной подсистемой, содержащей множество классов.
 ‘асад может иметь урезанный интерфейс, не имеющий 100% функциональности, которой можно достичь,
 использу€ сложную подсистему напр€мую. Ќо он предоставл€ет именно те фичи, которые нужны клиенту,
 и скрывает все остальные.
 ‘асад полезен, если вы используете какую-то сложную библиотеку со множеством подвижных частей,
 но вам нужна только часть еЄ возможностей.

 ѕаттерн Facade "обертывает" сложную подсистему более простым интерфейсом.
 */

class Musician
{
public:
	Musician(std::string_view name) : m_name(name) { }
	virtual ~Musician() = default;

protected:
	void output(const std::string_view text) const
	{
		std::cout << m_name << " " << text << "." << "\n";
	}
private:
	std::string m_name;
};


//concrete musicians
class Vocalist : public Musician
{
public:
	explicit Vocalist(const std::string_view name) : Musician(name) { }

	void singCouplet(const int coupletNubmer) const
	{
		std::string text{ "sang couplet #" };
		text += std::to_string(coupletNubmer);
		output(text);
	}
	void sangChorus() const
	{
		output("sang chorus");
	}
};

class Guitarist : public Musician
{
public:
	explicit Guitarist(const std::string_view name) : Musician(name) { }

	void playCoolOpening() const
	{
		output("start with a cool opening");
	}
	void playCoolRiffs() const
	{
		output("play cool riffs");
	}
	void playOtherCoolRiffs() const
	{
		output("play other cool riffs");
	}
	void playIncrediblyCoolSolo() const
	{
		output("play a incredibly cool solo");
	}
	void playFinalAccord() const
	{
		output("finish the song a powerfull accord");
	}
};

class Bassist : public Musician
{
public:
	explicit Bassist(const std::string_view name) : Musician(name) { }

	void followTheDrums() const
	{
		output("follow the drums");
	}
	void changeRhythm(const std::string_view type) const
	{
		std::string text = ("change the rhythm");
		text += type;
		text += "a";
		output(text);
	}
	void stopPlaying() const
	{
		output("stop playing");
	}
};

class Drummer : public Musician
{
public:
	explicit Drummer(const std::string_view name) : Musician(name) { }

	void startPlaying() const
	{
		output("start playing");
	}

	void stopPlaying() const
	{
		output("stopPlaying");
	}
};

//Facade - in this case a famous group
class BlackSabbath
{
public:
	BlackSabbath() :
		vocalist(std::make_unique<Vocalist>("Ozzi Ozborn")),
		guitarist(std::make_unique<Guitarist>("Tony Aismy")),
		bassist(std::make_unique<Bassist>("Gizer Batler")),
		drummer(std::make_unique<Drummer>("Bill Wourd"))
	{ }

	void playSong() const
	{
		guitarist->playCoolOpening();
		drummer->startPlaying();
		bassist->followTheDrums();
		guitarist->playCoolRiffs();
		vocalist->singCouplet(1);
		bassist->changeRhythm("chorus");
		guitarist->playOtherCoolRiffs();
		vocalist->sangChorus();
		bassist->changeRhythm("couplet");
		guitarist->playCoolRiffs();
		vocalist->singCouplet(2);
		bassist->changeRhythm("chorus");
		guitarist->playOtherCoolRiffs();
		vocalist->sangChorus();
		bassist->changeRhythm("couplet");
		guitarist->playIncrediblyCoolSolo();
		guitarist->playCoolRiffs();
		vocalist->singCouplet(3);
		bassist->changeRhythm("chorus");
		guitarist->playOtherCoolRiffs();
		vocalist->sangChorus();
		bassist->changeRhythm("couplet");
		guitarist->playCoolRiffs();
		bassist->stopPlaying();
		drummer->stopPlaying();
		guitarist->playFinalAccord();
	}

private:
	std::unique_ptr<Vocalist> vocalist;
	std::unique_ptr<Guitarist> guitarist;
	std::unique_ptr<Bassist> bassist;
	std::unique_ptr<Drummer> drummer;
};

/*
BlackSabbath band;
band.playSong();
*/
