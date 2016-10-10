#include "visitor.h"
#include "util.h"

MyASTVisitor::MyASTVisitor(Context* context, ASTContext *astContext): ctx(context)
{
    this->ctx->setASTContext(astContext);
    this->evaluator = std::make_unique<Evaluator>(this->ctx);
}

bool MyASTVisitor::VisitFunctionDecl(FunctionDecl *f)
{
    if (f->hasBody())
    {
        std::vector<Declaration> parameters;

        for (unsigned int i = 0; i < f->getNumParams(); i++)
        {
            ParmVarDecl* par = f->getParamDecl(i);
            parameters.push_back(Declaration(par->getNameAsString(), par->getType()));
        }

        auto fn = std::make_unique<Function>(
                f->getNameInfo().getName().getAsString(),
                f->getReturnType(),
                parameters
        );
        this->ctx->addFunction(std::move(fn));
    }

    return true;
}

bool MyASTVisitor::VisitVarDecl(VarDecl *decl)
{
    if (isa<ParmVarDecl>(decl))
    {
        return true;
    }

    Variable* var = this->getActivePath()->addVariable(decl->getNameAsString(), decl->getType());
    Expr* e = decl->getInit();

    if (var != nullptr && e != nullptr)
    {
        var->assignVariable(this->evaluator->getVarFromExpr(e, this->getActivePath()));
    }

    return true;
}

bool MyASTVisitor::TraverseIfStmt(IfStmt *stmt)
{
    Expr* e = Util::stripExpr(stmt->getCond());
    Path* path = this->getActivePath();
    z3::expr condition = this->evaluator->evaluate(e, path);
    condition = path->getSolver().getExprBuilder().makeCondition(condition);

    if (path->getSolver().isSatisfiable(condition))
    {
        //Path* sat = path->clone();
        RecursiveASTVisitor<MyASTVisitor>::TraverseStmt(stmt->getThen());
    }
    if (path->getSolver().isSatisfiable(condition == path->getSolver().getExprBuilder().makeBool(false)))
    {
        RecursiveASTVisitor<MyASTVisitor>::TraverseStmt(stmt->getElse());
    }

    return true;
}

Path *MyASTVisitor::getActivePath()
{
    return this->ctx->getActiveFunction()->getActivePath();
}
