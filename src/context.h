#pragma once

#include <clang/AST/AST.h>

#include "program/function.h"

class Context
{
public:
    void addFunction(std::unique_ptr<Function> f);

    clang::ASTContext* getASTContext();
    void setASTContext(clang::ASTContext* ctx);

    Function* getActiveFunction();
    Function* getFunctionByName(std::string name);

private:
    size_t activeFunction = 0;
    std::vector<std::unique_ptr<Function>> functions;
    clang::ASTContext* astContext;
};