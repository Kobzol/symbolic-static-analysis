#include "util.h"

#include "solver/solver.h"
#include "variable/int_variable.h"

TEST_CASE("Solvers can be copied") {
    Solver s1;
    Solver s2 = s1;

    REQUIRE(s1.isSatisfiable());

    s2.addConstraint(s2.getExprBuilder().makeBool(false));

    REQUIRE_FALSE(s2.isSatisfiable());
    REQUIRE(s1.isSatisfiable());
}

TEST_CASE("Solvers can substitute variables") {
    Solver s;
    ExprBuilder e(s.getContext());

    IntVariable v(Declaration("x", INT_TYPE), &e);
    s.addConstraint(v.getExpr() > 5);

    REQUIRE(s.isSatisfiable());

    IntVariable sub(Declaration("x", INT_TYPE), &e);
    sub = 6;
    Solver s1 = s.substitute(v.getName(), sub.getExpr());
    REQUIRE(s1.isSatisfiable());

    sub = 4;
    Solver s2 = s.substitute(v.getName(), sub.getExpr());
    REQUIRE_FALSE(s2.isSatisfiable());
}