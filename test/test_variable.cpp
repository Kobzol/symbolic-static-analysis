#include "util.h"

#include "variable/int_variable.h"
#include "util/types.h"

TEST_CASE("Variables can be copied") {
    const int val = 5;

    Solver s;
    ExprBuilder& exp = s.getExprBuilder();
    IntVariable v1(Declaration("x", Types::Int()), &exp);
    v1 = 5;

    s.addConstraint(v1.getExpr());

    REQUIRE(s.isSatisfiable(exp.makeInt(v1.getName()) == exp.makeInt(val)));

    IntVariable v2(Declaration("y", Types::Int()), &exp);
    v2 = val + 1;
    s.addConstraint(v2.getExpr());

    REQUIRE_FALSE(s.isSatisfiable(exp.makeInt(v2.getName()) == exp.makeInt(val)));
    REQUIRE(s.isSatisfiable(exp.makeInt(v2.getName()) == exp.makeInt(val + 1)));
}

TEST_CASE("Variables can create constants") {
    const int val = 127;

    Solver s;
    ExprBuilder& exp = s.getExprBuilder();
    std::unique_ptr<IntVariable> var = IntVariable::createConstant(val, &exp);
    s.addConstraint(exp.makeInt(var->getName()) == exp.makeInt(val));
    REQUIRE(s.isSatisfiable());
}