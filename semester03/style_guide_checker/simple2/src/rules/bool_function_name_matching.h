#pragma once
#include "../base/BaseConsumerWithVisitor.h"

namespace sgc {
namespace bool_function_name_matching {

class Visitor : public BaseVisitor<Visitor>
{
public:
    Visitor(BaseConsumer *consumer = NULL);
    virtual ~Visitor() {}

    virtual bool VisitFunctionDecl(clang::FunctionDecl *decl);

private:
    bool match(std::string const &name) const;
};

typedef BaseConsumerWithVisitor<Visitor> Consumer;

}}  // namespace sgc::bool_function_name_matching
