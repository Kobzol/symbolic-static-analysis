#include "expr_builder.h"

ExprBuilder::ExprBuilder(z3::context* ctx): ctx(ctx)
{

}

z3::expr ExprBuilder::makeExpr()
{
    return z3::expr(*this->ctx);
}
z3::expr ExprBuilder::makeBool(bool value)
{
    return this->ctx->bool_val(value);
}
z3::expr ExprBuilder::makeInt(int value)
{
    return this->ctx->int_val(value);
}
z3::expr ExprBuilder::makeInt(std::string name)
{
    return this->ctx->int_const(name.c_str());
}
z3::expr ExprBuilder::makeCondition(const z3::expr& e)
{
    if (!e.is_bool())
    {
        return e != this->makeInt(0);
    }
    else return e;
}
