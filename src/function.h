#pragma once

#include <clang/AST/AST.h>

#include "declaration.h"
#include "path.h"

class Function
{
public:
    Function(std::string name, clang::QualType returnType, std::vector<Declaration> parameters);

    std::string getName()
    {
        return this->name;
    }
    clang::QualType getReturnType()
    {
        return this->returnType;
    }
    std::vector<Declaration>& getParameters()
    {
        return this->parameters;
    }
    Path* getActivePath()
    {
        return this->activePath;
    }
    std::vector<Path*>& getPaths()
    {
        return this->paths;
    }

    Path* clonePath();

private:
    std::string name;
    clang::QualType returnType;
    std::vector<Declaration> parameters;

    std::vector<Path*> paths;
    Path* activePath = nullptr;
};