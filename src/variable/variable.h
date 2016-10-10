#pragma once

#include <clang/AST/AST.h>
#include <z3++.h>

#include "solver/expr_builder.h"
#include "program/declaration.h"

class Variable
{
public:
    Variable(const Declaration& dec, ExprBuilder* builder);

    z3::expr& getExpr();
    std::string getName();
    clang::QualType getType();

    virtual void assignVariable(Variable* var);
    virtual Variable* clone() = 0;

protected:
    virtual z3::expr createDefaultExpr() = 0;

    ExprBuilder* getBuilder();
    void setExpr(const z3::expr& e);

private:
    ExprBuilder* builder;
    z3::expr expr;
    std::string name;
    clang::QualType type;
};