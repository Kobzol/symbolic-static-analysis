#include "context.h"

void Context::createFunction(Function* f)
{
    this->functions.push_back(f);
    this->activeFunction = f;
}

Function* Context::getFunctionByName(std::string name)
{
    for (Function* fn : this->functions)
    {
        if (fn->getName() == name) return fn;
    }

    return nullptr;
}
