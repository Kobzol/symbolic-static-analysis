#pragma once

#include <clang/AST/Type.h>

#include "variable/variable.h"
#include "solver/solver.h"

class Path
{
public:
    Path();

    Path(const Path& rhs);
    Path& operator=(const Path& rhs);

    Solver& getSolver();

    Variable* addVariable(std::string name, clang::QualType type);
    void addVariable(std::unique_ptr<Variable> var);

    Variable* getVariableByName(std::string name);

private:
    std::vector<std::unique_ptr<Variable>> variables;
    Solver solver;
};
