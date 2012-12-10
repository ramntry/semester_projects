#pragma once
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/ASTConsumer.h>

// forward declarations
namespace clang {
class SourceManager;
}

namespace sgc {  // Style Guide Checker

class BaseConsumer : public clang::ASTConsumer
{
public:
    BaseConsumer(clang::CompilerInstance *ci = nullptr) : ci_(ci) {}
    virtual ~BaseConsumer() {}

    clang::SourceManager &sourceManager() const { return ci_->getSourceManager(); }

private:
    clang::CompilerInstance *ci_;
};

}  // namespace sgc
