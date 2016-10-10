#include "util.h"

#include "variable/int_variable.h"
#include "solver/solver.h"

TEST_CASE("Variables can be copied") {
    const int val = 5;

    Solver s;
    ExprBuilder& exp = s.getExprBuilder();
    IntVariable v1(Declaration("x", INT_TYPE), &exp);
    v1 = 5;

    s.addConstraint(v1.getExpr());

    REQUIRE(s.isSatisfiable(exp.makeInt(v1.getName()) == exp.makeInt(val)));

    IntVariable v2(Declaration("y", INT_TYPE), &exp);
    v2 = val + 1;
    s.addConstraint(v2.getExpr());

    REQUIRE_FALSE(s.isSatisfiable(exp.makeInt(v2.getName()) == exp.makeInt(val)));
    REQUIRE(s.isSatisfiable(exp.makeInt(v2.getName()) == exp.makeInt(val + 1)));
}
