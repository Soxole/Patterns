#pragma once
#include <iostream>
#include <memory>

class Game
{
public:
	Game() = default;
	void create() const {
		std::cout << "Create game " << "\n";
	}
	void open(std::string_view file) {
		std::cout << "Open game from -> " << file << "\n";
	}
	void save(std::string_view file) {
		std::cout << "Save game in -> " << file << "\n";
	}
	void make_move(std::string_view move) {
		std::cout << "Make move -> " << move << "\n";
	}
};
//inline func opens files
inline std::string get_player_input(const std::string_view promt) {
	std::string input;
	std::cout << promt;
	std::cin >> input;
	return input;
}

//The base class
class Command
{
public:
	Command() = default;
	Command(Command const &) = default;
	Command &operator=(Command const &) = default;
	Command(Command &&) noexcept = default;
	Command &operator=(Command &&) noexcept = default;
	virtual ~Command() = default;

	virtual void execute() = 0;
protected:
	explicit Command(std::shared_ptr<Game> ptr) : m_ptr_game_(std::move(ptr)) {}
	std::shared_ptr<Game> m_ptr_game_;
};
//command #1 create game
class CreateGameCommand final : public Command
{
public:
	explicit CreateGameCommand(std::shared_ptr<Game> const ptr) : Command(ptr) {}
	void execute() override {
		m_ptr_game_->create();
	}
};
//command #2
class OpenGameCommand final : public Command
{
public:
	explicit OpenGameCommand(std::shared_ptr<Game> ptr) : Command(std::move(ptr)) {}
	void execute() override {
		const auto file_name{ get_player_input("Enter file name: ") };
		m_ptr_game_->open(file_name);
	}
};
//command #3
class SaveGameCommand final : public Command
{
public:
	explicit SaveGameCommand(std::shared_ptr<Game> ptr) : Command(std::move(ptr)) {}
	void execute() override {
		const std::string file_name{ get_player_input("Enter file name: ") };
		m_ptr_game_->save(file_name);
	}
};
//command #4
class MakeMoveCommand final : public Command
{
public:
	explicit MakeMoveCommand(std::shared_ptr<Game> ptr) : Command(std::move(ptr)) {}
	void execute() override {
		m_ptr_game_->save("TEMP_FILE");
		const std::string move{ get_player_input("Enter your move: ") };
		m_ptr_game_->make_move(move);
	}
};
//command #5
class UndoCommand final : public Command
{
public:
	explicit UndoCommand(std::shared_ptr<Game> ptr) : Command(std::move(ptr)) {}
	void execute() override {
		m_ptr_game_->open("TEMP_FILE");
	}
};

//main()
#if 0
auto game = std::make_shared<Game>();
std::vector<std::unique_ptr<Command> > v;

v.emplace_back(std::make_unique<CreateGameCommand>(game));
v.emplace_back(std::make_unique<MakeMoveCommand>(game));
v.emplace_back(std::make_unique<MakeMoveCommand>(game));
v.emplace_back(std::make_unique<UndoCommand>(game));
v.emplace_back(std::make_unique<SaveGameCommand>(game));
for (const auto &it : v) {
	it->execute();
}
#endif