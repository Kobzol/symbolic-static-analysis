#pragma once

#include <clang/AST/AST.h>

class Util
{
public:
    static clang::Expr* stripExpr(clang::Expr* e);
    static clang::QualType stripType(const clang::QualType& type);
};