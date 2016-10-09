#include "util.h"

TEST_CASE("Variables can be copied") {
    const int val = 5;

    Solver s;
    Variable v1("", clang::QualType(), &s);
    v1.assignIntConstant(val);

    REQUIRE(s.isSatisfiable(v1.get_expr() == s.makeInt(val)));

    Variable v2 = v1;
    v2.assignIntConstant(val + 1);

    REQUIRE_FALSE(s.isSatisfiable(v2.get_expr() == s.makeInt(val)));
    REQUIRE(s.isSatisfiable(v1.get_expr() == s.makeInt(val)));
}
