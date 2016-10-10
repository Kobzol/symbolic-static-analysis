#pragma once

#include <z3++.h>

class ExprBuilder
{
public:
    ExprBuilder(z3::context* ctx);

    z3::expr makeExpr();
    z3::expr makeBool(bool value);
    z3::expr makeInt(int value);
    z3::expr makeInt(std::string name);
    z3::expr makeCondition(const z3::expr& e);

private:
    z3::context* ctx;
};