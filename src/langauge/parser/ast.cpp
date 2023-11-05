#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <sstream>
#include "../lexer/token.h"
#include "ast.h"

struct Node {
    virtual std::string TokenLiteral() = 0;
    virtual std::string String() = 0;
};

struct Statement : Node {
    virtual void statementNode() = 0;
};

struct Expression : Node {
    virtual void expressionNode() = 0;
};

struct Identifier : Expression {
    Token tok;
    std::string Value;

    void expressionNode() override {}
    std::string TokenLiteral() override {
        return tok.Literal;
    }

    std::string String() {
        return Value;
    }
};

struct Program {
    std::vector<Statement*> Statements;

    std::string TokenLiteral() {
        if (!Statements.empty()) {
            return Statements[0]->TokenLiteral();
        }
        return "";
    }

    std::string String() {
        std::stringstream out;
        for (const auto s : Statements) {
            out << s->String();
        }
        return out.str();
    }
};

struct LetStatement : Statement {
    Token tok;
    Identifier* Name;
    Expression* Value;

    void statementNode() override {}
    std::string TokenLiteral() override {
        return tok.Literal;
    }

    std::string String() {
        std::stringstream out;
        out << TokenLiteral() << " " << Name->String() << " = ";
        if (Value != nullptr) {
            out << Value->String();
        }
        out << ";";
        return out.str();
    }
};

struct ReturnStatement : Statement {
    Token tok;
    Expression* ReturnValue;

    void statementNode() override {}
    std::string TokenLiteral() override {
        return tok.Literal;
    }

    std::string String() {
        std::stringstream out;
        out << TokenLiteral() << " ";
        if (ReturnValue != nullptr) {
            out << ReturnValue->String();
        }
        out << ";";
        return out.str();
    }
};

struct ExpressionStatement : Statement {
    Token tok;
    Expression* expr;

    void statementNode() override {}
    std::string TokenLiteral() override {
        return tok.Literal;
    }

    std::string String() {
        if (expr != nullptr) {
            return expr->String();
        }
        return "";
    }
};

struct BlockStatement : Statement {
    Token tok;
    std::vector<Statement*> Statements;

    void statementNode() override {}
    std::string TokenLiteral() override {
        return tok.Literal;
    }

    std::string String() {
        std::stringstream out;
        for (const auto s : Statements) {
            out << s->String();
        }
        return out.str();
    }
};


struct Boolean : Expression {
    Token tok;
    bool Value;

    void expressionNode() override {}
    std::string TokenLiteral() override {
        return tok.Literal;
    }

    std::string String() {
        return tok.Literal;
    }
};

struct IntegerLiteral : Expression {
    Token tok;
    int64_t Value;

    void expressionNode() override {}
    std::string TokenLiteral() override {
        return tok.Literal;
    }

    std::string String() {
        return tok.Literal;
    }
};

struct PrefixExpression : Expression {
    Token tok;
    std::string Operator;
    Expression* Right;

    void expressionNode() override {}
    std::string TokenLiteral() override {
        return tok.Literal;
    }

    std::string String() {
        std::stringstream out;
        out << "(" << Operator << Right->String() << ")";
        return out.str();
    }
};

struct InfixExpression : Expression {
    Token tok;
    Expression* Left;
    std::string Operator;
    Expression* Right;

    void expressionNode() override {}
    std::string TokenLiteral() override {
        return tok.Literal;
    }

    std::string String() {
        std::stringstream out;
        out << "(" << Left->String() << " " << Operator << " " << Right->String() << ")";
        return out.str();
    }
};

struct IfExpression : Expression {
    Token tok;
    Expression* Condition;
    BlockStatement* Consequence;
    BlockStatement* Alternative;

    void expressionNode() override {}
    std::string TokenLiteral() override {
        return tok.Literal;
    }

    std::string String() {
        std::stringstream out;
        out << "if" << Condition->String() << " " << Consequence->String();
        if (Alternative != nullptr) {
            out << "else " << Alternative->String();
        }
        return out.str();
    }
};

struct FunctionLiteral : Expression {
    Token tok;
    std::vector<Identifier*> Parameters;
    BlockStatement* Body;

    void expressionNode() override {}
    std::string TokenLiteral() override {
        return tok.Literal;
    }

    std::string String() {
        std::stringstream out;
        std::vector<std::string> params;
        for (const auto p : Parameters) {
            params.push_back(p->String());
        }
        out << TokenLiteral() << "(" << StringJoin(params, ", ") << ") " << Body->String();
        return out.str();
    }

private:
    std::string StringJoin(const std::vector<std::string>& strings, const std::string& delimiter) {
        std::stringstream result;
        for (size_t i = 0; i < strings.size(); ++i) {
            if (i > 0) {
                result << delimiter;
            }
            result << strings[i];
        }
        return result.str();
    }
};

struct CallExpression : Expression {
    Token tok;
    Expression* Function;
    std::vector<Expression*> Arguments;

    void expressionNode() override {}
    std::string TokenLiteral() override {
        return tok.Literal;
    }

    std::string String() {
        std::stringstream out;
        std::vector<std::string> args;

        for (const auto a : Arguments) {
            args.push_back(a->String());
        }
        out << Function->String() << "(" << StringJoin(args, ", ") << ")";
        return out.str();
    }

private:
    std::string StringJoin(const std::vector<std::string>& strings, const std::string& delimiter) {
        std::stringstream result;
        for (size_t i = 0; i < strings.size(); ++i) {
            if (i > 0) {
                result << delimiter;
            }
            result << strings[i];
        }
        return result.str();
    }
};

