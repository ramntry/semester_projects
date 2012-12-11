#pragma once
#include <clang/Frontend/FrontendAction.h>

namespace sgc {
namespace macro_rules {

class Action : public clang::ASTFrontendAction
{
protected:
    virtual bool usesPreprocessorOnly() const { return true; }
    virtual bool BeginInvocation(clang::CompilerInstance &ci)
    { ci.getSourceManager().clearIDTables(); return true; }
    virtual clang::ASTConsumer *CreateASTConsumer(clang::CompilerInstance &ci
            , llvm::StringRef filename) { return NULL; }

    virtual void ExecuteAction();
};

}}  // namespace sgc::macro_rules;
