#pragma once

#include <clang/AST/Type.h>

class Declaration
{
public:
    Declaration(std::string name, clang::QualType type);

    std::string getName() const;
    clang::QualType getType() const;

private:
    std::string name;
    clang::QualType type;
};