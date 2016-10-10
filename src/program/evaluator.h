#pragma once

#include <clang/AST/AST.h>

#include "context.h"
#include "variable/variable.h"
#include "path.h"

class Evaluator
{
public:
    Evaluator(Context* context);

    Variable* getVarFromExpr(clang::Expr* e, Path* path);
    z3::expr evaluate(clang::Expr* e, Path* path);

    bool isConstant(clang::Expr* e);
    bool isInt(clang::Expr* e);
    int64_t getAsInt(clang::Expr* e);

private:
    bool getAsInt(clang::Expr* e, int64_t& result);

    Context* ctx;
};