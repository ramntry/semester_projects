#pragma once
#include "../base/BaseConsumer.h"
#include "../base/BaseVisitor.h"

namespace sgc {
namespace name_matching {

class Visitor : public BaseVisitor<Visitor>
{
public:
    Visitor(BaseConsumer *consumer = NULL);
    virtual ~Visitor() {}

    virtual bool VisitNamedDecl(clang::NamedDecl *decl);

private:
    bool match(std::string const &name) const;
    bool matchTypename(std::string const &name) const;
};

class Consumer : public BaseConsumer
{
public:
    Consumer(clang::CompilerInstance *ci = NULL
            , llvm::StringRef filename = llvm::StringRef());
    virtual ~Consumer() {}

    bool HandleTopLevelDecl(clang::DeclGroupRef declGroup);

private:
    Visitor visitor_;
};

}}  // namespace sgc::name_matching
