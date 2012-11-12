#pragma once
#include <clang/AST/RecursiveASTVisitor.h>

// forward declarations
namespace clang {
class SourceManager;
}

namespace sgc {  // Style Guide Checker

template <typename Self>
class BaseVisitor : public clang::RecursiveASTVisitor<Self>
{
public:
    BaseVisitor() : sourceManager_(nullptr) {}

    void setSourceManager(clang::SourceManager &sm) { sourceManager_ = &sm; }
    clang::SourceManager *sourceManager() const { return sourceManager_; }

private:
    clang::SourceManager *sourceManager_;
};

}  // namespace sgc

