#pragma once
#include "../base/BaseConsumerWithVisitor.h"

namespace sgc {
namespace private_data_members_matching {

class Visitor : public BaseVisitor<Visitor>
{
public:
    Visitor(BaseConsumer *consumer = NULL);
    virtual ~Visitor() {}

    virtual bool VisitFieldDecl(clang::FieldDecl *decl);

private:
    bool match(std::string const &name) const;
    std::string classAndFieldNames(clang::FieldDecl *decl) const;
};

typedef BaseConsumerWithVisitor<Visitor> Consumer;

}}  // namespace sgc::private_data_members_matching
