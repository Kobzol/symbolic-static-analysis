#include "function.h"

Function::Function(std::string name, clang::QualType returnType, std::vector<Declaration> parameters)
        : name(name), returnType(returnType), parameters(parameters)
{
    auto path = std::make_unique<Path>();
    for (const Declaration& par : parameters)
    {
        path->addVariable(par.getName(), par.getType());
    }

    this->paths.push_back(std::move(path));
}

std::string Function::getName()
{
    return this->name;
}
clang::QualType Function::getReturnType()
{
    return this->returnType;
}
std::vector<Declaration>& Function::getParameters()
{
    return this->parameters;
}
Path* Function::getActivePath()
{
    return this->paths.at(this->activePath).get();
}
