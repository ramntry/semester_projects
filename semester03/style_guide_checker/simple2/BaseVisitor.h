#pragma once
#include <clang/AST/RecursiveASTVisitor.h>

namespace sgc {  // Style Guide Checker

// forward declarations
class BaseConsumer;

template <typename Self>
class BaseVisitor : public clang::RecursiveASTVisitor<Self>
{
public:
    BaseVisitor(BaseConsumer *consumer = nullptr) : consumer_(consumer) {}
    virtual ~BaseVisitor() {}

    clang::SourceManager &sourceManager() const
    { return consumer_->sourceManager(); }

    std::string prettyLocation(clang::Decl *decl) const
    { return consumer_->prettyLocation(decl); }

    void printFilenameIfItWasChanged(clang::Decl *decl)
    { consumer_->printFilenameIfItWasChanged(decl); }


private:
    BaseConsumer *consumer_;
};

}  // namespace sgc

