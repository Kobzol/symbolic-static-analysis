#include "driver.h"

ContextConsumer::ContextConsumer(Context* context, ASTContext* astContext): context(context), astContext(astContext)
{
    this->visitor = std::unique_ptr<MyASTVisitor>(new MyASTVisitor(context, astContext));
}

bool ContextConsumer::HandleTopLevelDecl(DeclGroupRef DR)
{
    for (DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b)
    {
        this->visitor->TraverseDecl(*b);
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
    return llvm::make_unique<ContextConsumer>(this->context, &compiler.getASTContext());
}

ASTFactory::ASTFactory(Context* context): context(context)
{

}

clang::ASTFrontendAction* ASTFactory::create()
{
    return new ContextFrontendAction(this->context);
}

Context* runOnString(std::string code)
{
    Context* ctx = new Context();
    clang::tooling::runToolOnCode(new ContextFrontendAction(ctx), code);
    return ctx;
}

Context* runFromCmd(int argc, const char **argv)
{
    llvm::cl::OptionCategory ToolingSampleCategory("Symbolic tool");
    clang::tooling::CommonOptionsParser op(argc, argv, ToolingSampleCategory);
    clang::tooling::ClangTool Tool(op.getCompilations(), op.getSourcePathList());

    Context* ctx = new Context();
    Tool.run(std::unique_ptr<ASTFactory>(new ASTFactory(ctx)).get());
    return ctx;
}
