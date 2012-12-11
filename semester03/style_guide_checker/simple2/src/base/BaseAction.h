#pragma once
#include <clang/AST/ASTConsumer.h>
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
            clang::CompilerInstance &ci, llvm::StringRef filename);

    std::string prettyLocation(clang::Token const &token) const
    {
        return token.getLocation().printToString(
                getCompilerInstance().getSourceManager()) + ": ";
    }
};

template <>
clang::ASTConsumer *BaseAction<void>::CreateASTConsumer(
        clang::CompilerInstance &ci, llvm::StringRef filename)
{
    return new clang::ASTConsumer;
}

template <typename Consumer>
clang::ASTConsumer *BaseAction<Consumer>::CreateASTConsumer(
        clang::CompilerInstance &ci, llvm::StringRef filename)
{
    return new Consumer(&ci, filename);
}

}  // namespace sgc
