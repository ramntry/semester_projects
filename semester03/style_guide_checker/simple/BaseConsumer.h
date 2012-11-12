#pragma once
#include <clang/AST/ASTConsumer.h>

// forward declarations
namespace clang {
class SourceManager;
}

namespace sgc {  // Style Guide Checker

class BaseConsumer : public clang::ASTConsumer
{
public:
    BaseConsumer() : sourceManager_(nullptr) {}
    virtual ~BaseConsumer() {}

    virtual void setSourceManager(clang::SourceManager &sm) { sourceManager_ = &sm; }
    clang::SourceManager *sourceManager() const { return sourceManager_; }

private:
    clang::SourceManager *sourceManager_;
};

}  // namespace sgc
