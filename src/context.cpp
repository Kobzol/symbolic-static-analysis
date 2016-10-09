#include "context.h"

void Context::createFunction(Function* f)
{
    this->functions.push_back(f);
    this->activeFunction = f;
}

Function* Context::getFunctionByName(std::string name)
{
    auto fn = std::find_if(this->functions.begin(), this->functions.end(), [&](Function* &function) {
        return function->getName() == name;
    });

    if (fn != this->functions.end())
    {
        return *fn;
    }
    else return nullptr;
}
