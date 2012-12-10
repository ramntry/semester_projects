#pragma once
#include "../base/BaseConsumer.h"
#include "../base/BaseVisitor.h"

namespace sgc {

template <typename Visitor>
class BaseConsumerWithVisitor : public BaseConsumer
{
public:
    BaseConsumerWithVisitor(clang::CompilerInstance *ci = NULL
                          , llvm::StringRef filename = llvm::StringRef());
    virtual ~BaseConsumerWithVisitor() {}

    bool HandleTopLevelDecl(clang::DeclGroupRef declGroup);

private:
    Visitor visitor_;
};

template <typename Visitor>
BaseConsumerWithVisitor<Visitor>::BaseConsumerWithVisitor(
        clang::CompilerInstance *ci, llvm::StringRef filename)
    : BaseConsumer(ci, filename)
    , visitor_(this)
{
}

template <typename Visitor>
bool BaseConsumerWithVisitor<Visitor>::HandleTopLevelDecl(clang::DeclGroupRef declGroup)
{
    using namespace clang;

    DeclGroupRef::iterator it = declGroup.begin();
    DeclGroupRef::iterator end = declGroup.end();
    for (; it != end; ++it)
    {
        visitor_.TraverseDecl(*it);
    }
    return true;
}

}  // namespace sgc
