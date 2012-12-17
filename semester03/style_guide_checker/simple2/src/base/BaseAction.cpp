#include "BaseAction.h"

template <>
clang::ASTConsumer *sgc::BaseAction<void>::CreateASTConsumer(
        clang::CompilerInstance &ci, llvm::StringRef filename)
{
    return new clang::ASTConsumer;
}

