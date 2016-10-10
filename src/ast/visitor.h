#pragma once

#include <iostream>

#include <clang/AST/RecursiveASTVisitor.h>

#include "context.h"
#include "program/evaluator.h"

using namespace clang;

class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor>
{
public:
    MyASTVisitor(Context* context, ASTContext* astContext);

    bool VisitFunctionDecl(FunctionDecl *f);
    bool VisitVarDecl(VarDecl* decl);
    bool TraverseIfStmt(IfStmt* stmt);

private:
    Path* getActivePath();

    Context* ctx;
    std::unique_ptr<Evaluator> evaluator;
};
