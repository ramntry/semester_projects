#pragma once
#include <clang/Frontend/FrontendAction.h>

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

    virtual clang::ASTConsumer *CreateASTConsumer(
            clang::CompilerInstance &ci, llvm::StringRef filename)
    {
        return new Consumer(&ci, filename);
    }

};

}  // namespace sgc
