#include "util.h"

TEST_CASE("Paths can be copied") {
    Path path;
    Variable* var1 = path.addVariable("x", INT_TYPE);

    Path p2 = path;
    REQUIRE(var1 != p2.getVariableByName(var1->getName()));

    Path p3(path);
    REQUIRE(var1 != p3.getVariableByName(var1->getName()));
}

TEST_CASE("Paths can lookup their functions") {
    Path p;
    Variable* var1 = p.addVariable("x", INT_TYPE);
    Variable* var2 = p.addVariable("y", INT_TYPE);

    REQUIRE(p.getVariableByName(var1->getName()) == var1);
    REQUIRE(p.getVariableByName(var2->getName()) == var2);
}
