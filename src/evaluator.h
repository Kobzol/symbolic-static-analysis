#pragma once

#include <clang/AST/AST.h>
#include <clang/AST/Type.h>

#include "context.h"
#include "variable/variable.h"
#include "path.h"

class Evaluator
{
public:
    Evaluator(Context* context): ctx(context)
    {

    }

    void assignInt(Variable* var, clang::Expr* e, Path* path)
    {
        e = this->strip(e);
        Variable* assignment = this->getVarFromExpr(e, path);
        var->assignIntVariable(assignment);
    }

    Variable* getVarFromExpr(clang::Expr* e, Path* path)
    {
        Variable* var = nullptr;

        if (clang::isa<clang::IntegerLiteral>(e))
        {
            var = path->createConstant();
            var->assignIntConstant(this->getAsInt(e));
        }
        else if (clang::isa<clang::DeclRefExpr>(e))
        {
            clang::DeclRefExpr* refExp = static_cast<clang::DeclRefExpr*>(e);
            var = path->getVariableByName(refExp->getDecl()->getNameAsString());
        }

        return var;
    }
    z3::expr evaluate(clang::Expr* e, Path* path)
    {
        if (clang::isa<clang::BinaryOperator>(e))
        {
            clang::BinaryOperator* binOp = static_cast<clang::BinaryOperator*>(e);
            clang::BinaryOperator::Opcode opcode = binOp->getOpcode();
            clang::Expr* lhs = this->strip(binOp->getLHS());
            clang::Expr* rhs = this->strip(binOp->getRHS());

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
            return this->getVarFromExpr(e, path)->expr;
        }
    }

    clang::Expr* strip(clang::Expr* e)
    {
        return e->IgnoreImpCasts()->IgnoreCasts();
    }

    bool isConstant(clang::Expr* e)
    {
        int64_t result;
        return this->getAsInt(e, result);
    }
    bool isInt(clang::Expr* e)
    {
        return e->getType().getUnqualifiedType().getAsString() == "int";
    }
    int64_t getAsInt(clang::Expr* e)
    {
        int64_t result;
        this->getAsInt(e, result);
        return result;
    }

private:
    bool getAsInt(clang::Expr* e, int64_t& result)
    {
        clang::Expr::EvalResult r;
        bool success = e->EvaluateAsRValue(r, *this->ctx->getASTContext());

        if (success)
        {
            result = r.Val.getInt().getExtValue();
        }

        return success;
    }

    Context* ctx;
};