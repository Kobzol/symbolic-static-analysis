#include "variable.h"

Variable::Variable(const Declaration &dec, ExprBuilder *builder) :
        builder(builder), expr(builder->makeExpr()), name(dec.getName()), type(dec.getType())
{
}

z3::expr &Variable::getExpr()
{
    return this->expr;
}
std::string Variable::getName()
{
    return this->name;
}
clang::QualType Variable::getType()
{
    return this->type;
}

void Variable::assignVariable(Variable *var)
{
    this->setExpr(var->getExpr());
}

ExprBuilder* Variable::getBuilder()
{
    return this->builder;
}

void Variable::setExpr(const z3::expr& e)
{
    this->expr = e;
}
