#pragma once
#include "../base/BaseConsumerWithVisitor.h"

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

typedef BaseConsumerWithVisitor<Visitor> Consumer;

}}  // namespace sgc::name_matching
