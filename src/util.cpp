#include "util.h"

clang::Expr* Util::stripExpr(clang::Expr* e)
{
    return e->IgnoreImpCasts()->IgnoreCasts();
}

clang::QualType Util::stripType(const clang::QualType& type)
{
    return type.getCanonicalType();
}
