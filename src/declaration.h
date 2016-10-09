#pragma once

#include <clang/AST/AST.h>

class Declaration
{
public:
    Declaration(std::string name, clang::QualType type) : type(type), name(name)
    {

    }

    std::string getName() const
    {
        return this->name;
    }
    clang::QualType getType() const
    {
        return this->type;
    }

private:
    std::string name;
    clang::QualType type;
};