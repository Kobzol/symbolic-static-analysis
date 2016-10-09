#include "util.h"

TEST_CASE("Solvers can be copied") {
    Solver s1;
    Solver s2 = s1;

    REQUIRE(s1.isSatisfiable());

    s2.addConstraint(s2.makeBool(false));

    REQUIRE_FALSE(s2.isSatisfiable());
    REQUIRE(s1.isSatisfiable());
}
