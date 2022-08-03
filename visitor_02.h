#pragma once
#include <memory>
#include <iostream>

namespace visitor2
{
    struct Token;
    struct Visitor;

    struct Token
    {
        Token() = default;
        Token(Token const &) = default;
        Token &operator=(Token const &) = default;
        Token(Token &&) noexcept = default;
        Token &operator=(Token &&) noexcept = default;
        virtual ~Token() = default;
        virtual void accept(Visitor &v) = 0;
    };

    struct text_token;
    struct open_token;

    struct Visitor
    {
        Visitor() = default;
        Visitor(Visitor const &) = default;
        Visitor &operator=(Visitor const &) = default;
        Visitor(Visitor &&) noexcept = default;
        Visitor &operator=(Visitor &&) noexcept = default;
        virtual ~Visitor() = default;
        virtual void accept(std::shared_ptr<text_token> p) = 0;
        virtual void accept(std::shared_ptr<open_token> p) = 0;
    };

    struct text_token final : public Token, public std::enable_shared_from_this<text_token>
    {
        void accept(Visitor &v) override {
            std::shared_ptr<text_token> p{ shared_from_this() };
            v.accept(p);
        }
    };

    struct open_token final : public Token, public std::enable_shared_from_this<open_token>
    {
        void accept(Visitor &v) override {
            std::shared_ptr<open_token> p{ shared_from_this() };
            v.accept(p);
        }
    };

    struct scan final : public Visitor
    {
        void accept(std::shared_ptr<text_token>) override {
            std::cout << "accepting text" << std::endl;
        }
        void accept(std::shared_ptr<open_token>) override {
            std::cout << "accepting open" << std::endl;
        }
    };
}

//main()
#if 0
int main() {
	std::vector<std::shared_ptr<token>> toks;
	toks.emplace_back(std::make_shared<text_token>());
	toks.emplace_back(std::make_shared<open_token>());

	scan s;
	for (auto p : toks)
		p->accept(s);
}
#endif
