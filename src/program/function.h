#pragma once

#include <clang/AST/AST.h>

#include "declaration.h"
#include "path.h"

class Function
{
public:
    Function(std::string name, clang::QualType returnType, std::vector<Declaration> parameters);

    std::string getName();
    clang::QualType getReturnType();
    std::vector<Declaration>& getParameters();
    Path* getActivePath();

private:
    std::string name;
    clang::QualType returnType;
    std::vector<Declaration> parameters;

    size_t activePath = 0;
    std::vector<std::unique_ptr<Path>> paths;
};