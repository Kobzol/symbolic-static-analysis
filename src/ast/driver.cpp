#include "driver.h"
#include <clang/CodeGen/ModuleBuilder.h>

ContextConsumer::ContextConsumer(Context* context, ASTContext* astContext)
{
    this->visitor = std::make_unique<MyASTVisitor>(context, astContext);
}

bool ContextConsumer::HandleTopLevelDecl(DeclGroupRef DR)
{
    for (auto decl : DR)
    {
        this->visitor->TraverseDecl(decl);
        //(*b)->dump();
    }

    return true;
}


ContextFrontendAction::ContextFrontendAction(Context* context) : context(context)
{

}
std::unique_ptr<clang::ASTConsumer> ContextFrontendAction::CreateASTConsumer(clang::CompilerInstance &compiler,
                                                                      clang::StringRef file)
{
    clang::ASTContext& ctx = compiler.getASTContext();

    return std::make_unique<ContextConsumer>(this->context, &compiler.getASTContext());
}

ASTFactory::ASTFactory(Context* context): context(context)
{

}

clang::ASTFrontendAction* ASTFactory::create()
{
    return new ContextFrontendAction(this->context);
}

std::unique_ptr<Context> runOnString(const std::string& code)
{
    auto ctx = std::make_unique<Context>();
    clang::tooling::runToolOnCode(new ContextFrontendAction(ctx.get()), code);
    return ctx;
}

std::unique_ptr<Context> runFromCmd(int argc, const char** argv)
{
    llvm::cl::OptionCategory toolingSampleCategory("Symbolic tool");
    clang::tooling::CommonOptionsParser op(argc, argv, toolingSampleCategory);
    clang::tooling::ClangTool tool(op.getCompilations(), op.getSourcePathList());

    auto ctx = std::make_unique<Context>();
    tool.run(std::make_unique<ASTFactory>(ctx.get()).get());
    return ctx;
}
