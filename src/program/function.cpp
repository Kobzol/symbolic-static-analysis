#include "function.h"

Function::Function(std::string name, clang::QualType returnType, std::vector<Declaration> parameters)
        : name(name), returnType(returnType), parameters(parameters)
{
    this->activePath = new Path();
    for (const Declaration& par : parameters)
    {
        this->activePath->addVariable(par.getName(), par.getType());
    }
    this->paths.push_back(this->activePath);
}

Path* Function::clonePath()
{
    Path* newPath = this->activePath->clone();
    this->paths.push_back(newPath);
    this->activePath = newPath;
    return newPath;
}
