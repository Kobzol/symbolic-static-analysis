#include "solver.h"

z3::context* Solver::CTX = new z3::context();

z3::context* Solver::getContext()
{
    return Solver::CTX;
}

Solver::Solver(): exprBuilder(CTX), solver(*CTX)
{

}
Solver::Solver(const Solver& other)
        : exprBuilder(CTX), solver(z3::solver(*CTX, Z3_solver_translate(*CTX, other.solver, *CTX)))
{

}

ExprBuilder& Solver::getExprBuilder()
{
    return this->exprBuilder;
}

Solver& Solver::operator=(const Solver& other)
{
    this->solver = this->copySolver(other.solver);
    return *this;
}

z3::solver Solver::copySolver(const z3::solver& solver)
{
    return z3::solver(*CTX, Z3_solver_translate(*CTX, solver, *CTX));
}

void Solver::addConstraint(const z3::expr& e)
{
    this->solver.add(e);
}

bool Solver::isSatisfiable()
{
    return this->isSatisfiable(this->exprBuilder.makeBool(true));
}
bool Solver::isSatisfiable(const z3::expr& e)
{
    z3::solver s = this->copySolver(this->solver);
    s.add(e);
    return s.check() == z3::check_result::sat;
}

Solver Solver::substitute(std::string original, const z3::expr &substitution)
{
    Solver s = *this;
    s.addConstraint(substitution);
    return s;
}
