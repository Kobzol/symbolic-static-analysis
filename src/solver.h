#pragma once

#include <z3++.h>

class Solver
{
public:
    static z3::context* getContext()
    {
        return Solver::CTX;
    }

    Solver(): solver(*CTX)
    {

    }

    Solver(const Solver& other): solver(z3::solver(*CTX, Z3_solver_translate(*CTX, other.solver, *CTX)))
    {

    }
    Solver& operator=(const Solver& other)
    {
        this->solver = this->copySolver(other.solver);
        return *this;
    }

    z3::solver copySolver(const z3::solver& solver)
    {
        return z3::solver(*CTX, Z3_solver_translate(*CTX, solver, *CTX));
    }

    z3::expr makeExpr()
    {
        return z3::expr(*CTX);
    }
    z3::expr makeBool(bool value)
    {
        return CTX->bool_val(value);
    }
    z3::expr makeInt(int value)
    {
        return CTX->int_val(value);
    }

    void addConstraint(const z3::expr& e)
    {
        this->solver.add(e);
    }

    bool isSatisfiable()
    {
        return this->isSatisfiable(this->makeBool(true));
    }
    bool isSatisfiable(const z3::expr& e)
    {
        z3::solver s = this->copySolver(this->solver);
        s.add(e);
        return s.check() == z3::check_result::sat;
    }
    z3::expr makeCondition(const z3::expr& e)
    {
        if (!e.is_bool())
        {
            return e != this->makeInt(0);
        }
        else return e;
    }

private:
    static z3::context* CTX;

    z3::solver solver;
};