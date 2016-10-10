#pragma once

#include <clang/AST/Type.h>

#include "variable/variable.h"
#include "solver/solver.h"

class Path
{
public:
    Solver& getSolver();

    Variable* addVariable(std::string name, clang::QualType type);
    Variable* addVariable(Variable* var);

    Variable* getVariableByName(std::string name);
    Variable* createConstant();

    Path* clone();

private:
    std::vector<Variable*> variables;
    Solver solver;
};
