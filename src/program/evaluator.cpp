#include "evaluator.h"

#include "util.h"

Evaluator::Evaluator(Context* context): ctx(context)
{

}

Variable *Evaluator::getVarFromExpr(clang::Expr *e, Path *path)
{
    Variable* var = nullptr;

    if (clang::isa<clang::IntegerLiteral>(e))
    {
        //var = path->createConstant(); TODO
        //var->assignIntConstant(this->getAsInt(e));
    }
    else if (clang::isa<clang::DeclRefExpr>(e))
    {
        clang::DeclRefExpr* refExp = static_cast<clang::DeclRefExpr*>(e);
        var = path->getVariableByName(refExp->getDecl()->getNameAsString());
    }

    return var;
}

z3::expr Evaluator::evaluate(clang::Expr *e, Path *path)
{
    if (clang::isa<clang::BinaryOperator>(e))
    {
        clang::BinaryOperator* binOp = static_cast<clang::BinaryOperator*>(e);
        clang::BinaryOperator::Opcode opcode = binOp->getOpcode();
        clang::Expr* lhs = Util::stripExpr(binOp->getLHS());
        clang::Expr* rhs = Util::stripExpr(binOp->getRHS());

        z3::expr left = this->evaluate(lhs, path);
        z3::expr right = this->evaluate(rhs, path);

        switch (opcode)
        {
            case clang::BinaryOperator::Opcode::BO_LAnd:
                return left && right;
            case clang::BinaryOperator::Opcode::BO_LOr:
                return left || right;
            case clang::BinaryOperator::Opcode::BO_EQ:
                return left == right;
            case clang::BinaryOperator::Opcode::BO_LT:
                return left < right;
            case clang::BinaryOperator::Opcode::BO_GT:
                return left > right;
            default:
                assert(false);
        }
    }
    else
    {
        return this->getVarFromExpr(e, path)->getExpr();
    }
}

bool Evaluator::isConstant(clang::Expr *e)
{
    int64_t result;
    return this->getAsInt(e, result);
}

bool Evaluator::isInt(clang::Expr *e)
{
    return e->getType().getUnqualifiedType().getAsString() == "int";
}

int64_t Evaluator::getAsInt(clang::Expr *e)
{
    int64_t result;
    this->getAsInt(e, result);
    return result;
}

bool Evaluator::getAsInt(clang::Expr *e, int64_t &result)
{
    clang::Expr::EvalResult r;
    bool success = e->EvaluateAsRValue(r, *this->ctx->getASTContext());

    if (success)
    {
        result = r.Val.getInt().getExtValue();
    }

    return success;
}
