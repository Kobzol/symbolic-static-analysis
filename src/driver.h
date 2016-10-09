#pragma once

#include <memory>

#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>

#include "context.h"
#include "visitor.h"

class ContextConsumer : public clang::ASTConsumer {
public:
    ContextConsumer(Context* context, clang::ASTContext* astContext);

    bool HandleTopLevelDecl(clang::DeclGroupRef DR) override;

private:
    Context* context;
    clang::ASTContext* astContext;
    std::unique_ptr<MyASTVisitor> visitor;
};

class ContextFrontendAction : public ASTFrontendAction {
public:
    ContextFrontendAction(Context* context);
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(CompilerInstance &compiler,
                                                   StringRef file) override;

private:
    Context* context;
};

class ASTFactory: public clang::tooling::FrontendActionFactory {
public:
    ASTFactory(Context* context);

    clang::ASTFrontendAction *create() override;

private:
    Context* context;
};

Context* runOnString(std::string code);
Context* runFromCmd(int argc, const char** argv);