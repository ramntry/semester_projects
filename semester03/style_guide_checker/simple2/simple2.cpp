#include <assert.h>
#include <llvm/Support/Host.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Lex/Token.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/HeaderSearch.h>
#include <clang/Frontend/Utils.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Parse/ParseAST.h>

#include <clang/Frontend/ASTUnit.h>
#include <clang/Frontend/FrontendAction.h>

#include "src/rules/private_data_members_matching.h"
#include "src/rules/top_level_decl_order_checking.h"

namespace sgc {

template <typename Consumer>
class BaseAction : public clang::ASTFrontendAction
{
protected:
    virtual bool BeginInvocation(clang::CompilerInstance &ci)
    {
        ci.getSourceManager().clearIDTables();
        return true;
    }

    virtual clang::ASTConsumer *CreateASTConsumer(clang::CompilerInstance &ci, llvm::StringRef filename)
    {
        return new Consumer(&ci, filename);
    }

};

}  // namespace sgc

namespace sgc {

class ASTUnitWrapper
{
public:
    ASTUnitWrapper(int argc, char const **argv);
    ~ASTUnitWrapper() { delete unit_; }

    template <typename Consumer>
    void run();

private:
    llvm::IntrusiveRefCntPtr<clang::DiagnosticsEngine> diags_;
    clang::CompilerInvocation *invoc_;
    clang::ASTUnit *unit_;
};

ASTUnitWrapper::ASTUnitWrapper(int argc, char const **argv)
    : diags_(clang::CompilerInstance::createDiagnostics(new clang::DiagnosticOptions, argc, argv))
    , invoc_(new clang::CompilerInvocation)
{
    using namespace clang;
    using namespace llvm;

    CompilerInvocation::CreateFromArgs(*invoc_, argv + 1, argv + argc, *diags_);
    unit_ = ASTUnit::LoadFromCompilerInvocation(invoc_, diags_);
}

template <typename Consumer>
void ASTUnitWrapper::run()
{
    BaseAction<Consumer> action;
    clang::ASTUnit::LoadFromCompilerInvocationAction(invoc_, diags_, &action, unit_);
}

}  // namespace sgc

int main(int argc, char const **argv)
{
    if (argc < 2) {
        llvm::errs() << "Usage: simple2 <compiler-like-command-line-options>\n";
        return EXIT_FAILURE;
    }

    using namespace sgc;

    ASTUnitWrapper unit(argc, argv);
    unit.run<private_data_members_matching::Consumer>();
    unit.run<top_level_decl_order_checking::Consumer>();
}

