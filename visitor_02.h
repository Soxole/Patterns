#pragma once
#include <memory>
#include <iostream>

//TITLE: Visitor 2(!memory leak)


struct token;

struct visitor;

struct token
{
	virtual ~token() = default;
    virtual void accept(visitor &v) = 0;
};

struct text_token;
struct open_token;

struct visitor
{
	virtual ~visitor() = default;
    virtual void accept(std::shared_ptr<text_token> p) = 0;
    virtual void accept(std::shared_ptr<open_token> p) = 0;
};

struct text_token : public token, public std::enable_shared_from_this<text_token>
{
    void accept(visitor &v) override {
        std::shared_ptr<text_token> p{shared_from_this()};
        v.accept(p);
    }   
};

struct open_token : public token, public std::enable_shared_from_this<open_token>
{
    void accept(visitor &v) override {
        std::shared_ptr<open_token> p{shared_from_this()};
        v.accept(p);
    }   
};

struct scan : public visitor
{
    void accept(std::shared_ptr<text_token>) override {
        std::cout << "accepting text" << std::endl;
    }
    void accept(std::shared_ptr<open_token>) override {
        std::cout << "accepting open" << std::endl;
    }   
};


/*
int main() {
	std::vector<std::shared_ptr<token>> toks;
	toks.emplace_back(std::make_shared<text_token>());
	toks.emplace_back(std::make_shared<open_token>());

	scan s;
	for (auto p : toks)
		p->accept(s);
}
 */