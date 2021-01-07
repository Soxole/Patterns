#pragma once
#include <iostream>
#include <memory>

/*
���������� ���������� �������� Command �� ������� ���� ���������. ��������� ����������� ���������� ��������� ��������:

	������� ����� ����.
	������� ������������ ����.
	��������� ����.
	������� ��������� ���.
	�������� ��������� ���.
	
 */



using std::cout;
using std::cin;
using std::string_view;
using std::string;


class Game
{
public:
	Game() = default;
	void create() const
	{
		cout << "Create game " << "\n";
	}
	void open(string_view file)
	{
		cout << "Open game from -> " << file << "\n";
	}
	void save(string_view file)
	{
		cout << "Save game in -> " << file << "\n";
	}
	void make_move(string_view move)
	{
		cout << "Make move -> " << move << "\n";
	}
};
//inline func opens files
inline string get_player_input(const string_view promt)
{
	string input;
	cout << promt;
	cin >> input;
	return input;
}

//The base class
class Command
{
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
protected:
	explicit Command(std::shared_ptr<Game> ptr) : m_ptr_game_(std::move(ptr))
	{
	}
	std::shared_ptr<Game> m_ptr_game_;
};
//command #1 create game
class CreateGameCommand : public Command
{
public:
	explicit CreateGameCommand(std::shared_ptr<Game> ptr) : Command(ptr)
	{
	}
	void execute() override
	{
		m_ptr_game_->create();
	}
};
//command #2
class OpenGameCommand : public Command
{
public:
	explicit OpenGameCommand(std::shared_ptr<Game> ptr) : Command(std::move(ptr))
	{
	}
	void execute() override
	{
		const auto file_name{ get_player_input("Enter file name: ") };
		m_ptr_game_->open(file_name);
	}
};
//command #3
class SaveGameCommand : public Command
{
public:
	explicit SaveGameCommand(std::shared_ptr<Game> ptr) : Command(std::move(ptr))
	{
	}
	void execute() override
	{
		const string file_name{ get_player_input("Enter file name: ") };
		m_ptr_game_->save(file_name);
	}
};
//command #4
class MakeMoveCommand : public Command
{
public:
	explicit MakeMoveCommand(std::shared_ptr<Game> ptr) : Command(std::move(ptr))
	{
	}
	void execute() override
	{
		// �������� ���� ��� ���������� ������������ ������
		m_ptr_game_->save("TEMP_FILE");
		const string move{ get_player_input("Enter your move: ") };
		m_ptr_game_->make_move(move);
	}
};
//command #5
class UndoCommand : public Command
{
public:
	explicit UndoCommand(std::shared_ptr<Game> ptr) : Command(std::move(ptr))
	{
	}
	void execute() override
	{
		m_ptr_game_->open("TEMP_FILE");
	}
};

/*
	auto game = make_shared<Game>();
	vector<unique_ptr<Command> > v;
	// ������� ����� ����
	v.emplace_back(make_unique<CreateGameCommand>(game));
	// ������ ��������� �����
	v.emplace_back(make_unique<MakeMoveCommand>(game));
	v.emplace_back(make_unique<MakeMoveCommand>(game));
	// ��������� ��� ��������
	v.emplace_back(make_unique<UndoCommand>(game));
	// ��������� ����
	v.emplace_back(make_unique<SaveGameCommand>(game));
	for (const auto &it : v)
	{
		it->execute();
	}

 */