#include "int_variable.h"

IntVariable::IntVariable(const Declaration &dec, ExprBuilder *builder): Variable(dec, builder)
{
    this->setExpr(this->createDefaultExpr());
}

z3::expr IntVariable::createDefaultExpr()
{
    return this->getBuilder()->makeInt(this->getName());
}

Variable* IntVariable::clone()
{
    return new IntVariable(Declaration(this->getName(), this->getType()), this->getBuilder());
}

IntVariable& IntVariable::operator=(int rhs)
{
    this->setExpr(this->getBuilder()->makeInt(this->getName()) == this->getBuilder()->makeInt(rhs));
    return *this;
}
