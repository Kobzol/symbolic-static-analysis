#include "util.h"

#include "util/types.h"

const std::string p1 = R"(
int f(int par1, bool par2)
{
    return 0;
}
)";

TEST_CASE("Functions are correctly registered") {
    std::unique_ptr<Context> ctx = testCode(p1);
    Function* f = ctx->getFunctionByName("f");

    REQUIRE(f != nullptr);
    REQUIRE(f->getName() == "f");
    REQUIRE(Types::is<int>(f->getReturnType()));

    std::vector<Declaration>& params = f->getParameters();
    REQUIRE(params.size() == 2);
    REQUIRE(params[0].getName() == "par1");
    REQUIRE(Types::is<int>(params[0].getType()));
    REQUIRE(params[1].getName() == "par2");
    REQUIRE(Types::is<bool>(params[1].getType()));
}
