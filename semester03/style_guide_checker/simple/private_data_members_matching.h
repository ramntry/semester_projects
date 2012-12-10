#pragma once
#include "BaseConsumer.h"
#include "BaseVisitor.h"

namespace sgc {
namespace private_data_members_matching {

class Visitor : public BaseVisitor<Visitor>
{
public:
    virtual bool VisitFieldDecl(clang::FieldDecl *decl);

private:
    bool match(std::string const &name) const;
    std::string prettyLocation(clang::FieldDecl *decl) const;
    void printFilenameIfItWasChanged(clang::FieldDecl *decl);

    std::string lastFileName_;
};

class Consumer : public BaseConsumer
{
public:
    Consumer(clang::SourceManager *sm = nullptr);
    virtual void setSourceManager(clang::SourceManager &sm);

    bool HandleTopLevelDecl(clang::DeclGroupRef declGroup);

private:
    Visitor visitor_;
};

}}  // namespace sgc::private_data_members_matching
