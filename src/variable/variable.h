#pragma once

#include <clang/AST/AST.h>
#include <z3++.h>
#include <cstdint>

#include "../declaration.h"
#include "../solver.h"

class Variable
{
public:
    Variable(std::string name, clang::QualType type, Solver* solver):
            name(name), type(type), solver(solver), expr(solver->makeExpr())
    {

    }

    Variable(const Declaration& dec, Solver* solver):
            name(dec.getName()), type(dec.getType()), solver(solver), expr(solver->makeExpr())
    {

    }

    void assignIntConstant(int value)
    {
        this->expr = this->solver->makeInt(value);
    }
    void assignIntVariable(Variable* var)
    {
        this->expr = var->expr;
    }

    z3::expr& get_expr()
    {
        return this->expr;
    }

    z3::expr expr;
    Solver* solver;
    std::string name;
    clang::QualType type;
};