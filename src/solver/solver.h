#pragma once

#include <z3++.h>
#include "expr_builder.h"

class Solver
{
public:
    static z3::context* getContext();

    Solver();
    Solver(const Solver& other);

    Solver& operator=(const Solver& other);

    ExprBuilder& getExprBuilder();

    z3::solver copySolver(const z3::solver& solver);

    void addConstraint(const z3::expr& e);

    bool isSatisfiable();
    bool isSatisfiable(const z3::expr& e);

    Solver substitute(std::string original, const z3::expr& substitution);

private:
    static z3::context* CTX;

    ExprBuilder exprBuilder;
    z3::solver solver;
};