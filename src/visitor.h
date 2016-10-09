#pragma once

#include <iostream>

#include <clang/AST/AST.h>
#include <clang/AST/Expr.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include "context.h"
#include "evaluator.h"

using namespace clang;

class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor>
{
public:
    MyASTVisitor(Context* context, ASTContext* astContext): ctx(context), astCtx(astContext)
    {
        this->ctx->setASTContext(astContext);
        this->evaluator = new Evaluator(this->ctx);
    }

    bool VisitVarDecl(VarDecl* decl)
    {
        if (isa<ParmVarDecl>(decl))
        {
            return true;
        }

        Variable* var = this->getActivePath()->addVariable(decl->getNameAsString(), decl->getType());

        Expr* e = decl->getInit();
        if (e != nullptr && this->evaluator->isInt(e))
        {
            this->evaluator->assignInt(var, e, this->getActivePath());
        }

        return true;
    }

    bool TraverseIfStmt(IfStmt* stmt)
    {
        Expr* e = this->evaluator->strip(stmt->getCond());
        Path* path = this->getActivePath();
        z3::expr condition = this->evaluator->evaluate(e, path);
        condition = path->solver.makeCondition(condition);

        if (path->solver.isSatisfiable(condition))
        {
            Path* sat = path->clone();
            RecursiveASTVisitor<MyASTVisitor>::TraverseStmt(stmt->getThen());
        }
        if (path->solver.isSatisfiable(condition == path->solver.makeBool(false)))
        {
            RecursiveASTVisitor<MyASTVisitor>::TraverseStmt(stmt->getElse());
        }

        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *f)
    {
        if (f->hasBody())
        {
            std::vector<Declaration> parameters;

            for (int i = 0; i < f->getNumParams(); i++)
            {
                ParmVarDecl* par = f->getParamDecl(i);
                parameters.push_back(Declaration(par->getNameAsString(), par->getType()));
            }

            Function* fn = new Function(
                    f->getNameInfo().getName().getAsString(),
                    f->getReturnType(),
                    parameters
            );
            this->ctx->createFunction(fn);
        }

        return true;
    }

private:
    Path* getActivePath()
    {
        return this->ctx->getActiveFunction()->getActivePath();
    }

    Context* ctx;
    ASTContext* astCtx;
    Evaluator* evaluator;
};
