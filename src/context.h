#pragma once

#include <clang/AST/AST.h>

#include "function.h"

class Context
{
public:
    void createFunction(Function* f);

    clang::ASTContext* getASTContext()
    {
        return this->astContext;
    }
    void setASTContext(clang::ASTContext* ctx)
    {
        this->astContext = ctx;
    }

    Function* getActiveFunction()
    {
        return this->activeFunction;
    }

    Function* getFunctionByName(std::string name);

private:
    Function* activeFunction;
    std::vector<Function*> functions;
    clang::ASTContext* astContext;
};