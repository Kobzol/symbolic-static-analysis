#include "context.h"

void Context::addFunction(std::unique_ptr<Function> f)
{
    this->functions.push_back(std::move(f));
    this->activeFunction = this->functions.size() - 1;
}

Function* Context::getFunctionByName(std::string name)
{
    for (auto& fn : this->functions)
    {
        if (fn->getName() == name) return fn.get();
    }

    return nullptr;
}

clang::ASTContext* Context::getASTContext()
{
    return this->astContext;
}
void Context::setASTContext(clang::ASTContext *ctx)
{
    this->astContext = ctx;
}

Function* Context::getActiveFunction()
{
    return this->functions.at(this->activeFunction).get();
}
