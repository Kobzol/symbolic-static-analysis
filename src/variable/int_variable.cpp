#include <util/types.h>
#include "int_variable.h"

IntVariable::IntVariable(const Declaration &dec, ExprBuilder *builder): Variable(dec, builder)
{
    this->setExpr(this->createDefaultExpr());
}

z3::expr IntVariable::createDefaultExpr()
{
    return this->getBuilder()->makeInt(this->getName());
}

std::unique_ptr<Variable> IntVariable::clone()
{
    return std::make_unique<IntVariable>(Declaration(this->getName(), this->getType()), this->getBuilder());
}

IntVariable& IntVariable::operator=(int rhs)
{
    this->setExpr(this->getBuilder()->makeInt(this->getName()) == this->getBuilder()->makeInt(rhs));
    return *this;
}

std::unique_ptr<IntVariable> IntVariable::createConstant(int value, ExprBuilder* builder)
{
    std::unique_ptr<IntVariable> var = std::make_unique<IntVariable>(Declaration("IntConstant_" + std::to_string(value), Types::Int()), builder);
    *var = value;
    return var;
}
