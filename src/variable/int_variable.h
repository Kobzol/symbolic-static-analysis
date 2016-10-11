#pragma once

#include "variable.h"

class IntVariable : public Variable
{
public:
    static std::unique_ptr<IntVariable> createConstant(int value, ExprBuilder* builder);

    IntVariable(const Declaration &dec, ExprBuilder *builder);

    virtual std::unique_ptr<Variable> clone() override;

    IntVariable& operator=(int rhs);

protected:
    virtual z3::expr createDefaultExpr() override;
};
