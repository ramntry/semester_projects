#pragma once
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTConsumer.h>

// forward declarations
namespace clang {
class SourceManager;
}

namespace sgc {  // Style Guide Checker

class BaseConsumer : public clang::ASTConsumer
{
public:
    BaseConsumer(clang::CompilerInstance *ci = nullptr
               , llvm::StringRef filename = llvm::StringRef());
    virtual ~BaseConsumer() {}

    clang::SourceManager &sourceManager() const { return ci_->getSourceManager(); }

    std::string prettyLocation(clang::Decl *decl) const;
    void printFilenameIfItWasChanged(clang::Decl *decl);

private:
    clang::CompilerInstance *ci_;
    llvm::StringRef filename_;
    std::string lastFileName_;
};

}  // namespace sgc
