#pragma once

#include "variable.h"

class IntVariable : public Variable
{
public:
    IntVariable(const Declaration &dec, ExprBuilder *builder);

    virtual std::unique_ptr<Variable> clone() override;

    IntVariable& operator=(int rhs);

protected:
    virtual z3::expr createDefaultExpr() override;
};
