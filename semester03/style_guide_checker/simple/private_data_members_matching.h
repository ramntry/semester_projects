#pragma once
#include "BaseConsumer.h"
#include "BaseVisitor.h"

/*
namespace clang {
class Decl;
class DeclGroupRef;
class FieldDecl;
}
*/

namespace sgc {
namespace private_data_members_matching {

class Visitor : public BaseVisitor<Visitor>
{
public:
    virtual bool VisitFieldDecl(clang::FieldDecl *decl);

private:
    bool match(std::string const &name) const;
    std::string prettyLocation(clang::FieldDecl *decl) const;
};

class Consumer : public BaseConsumer
{
public:
    virtual void setSourceManager(clang::SourceManager &sm);

    bool HandleTopLevelDecl(clang::DeclGroupRef declGroup);

private:
    Visitor visitor_;
};

}}  // namespace sgc::private_data_members_matching
