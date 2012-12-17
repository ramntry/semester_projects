#pragma once
#include <llvm/Support/Regex.h>
#include "../../base/BaseConsumerWithVisitor.h"

namespace sgc {
namespace alignment_control {

class Visitor : public BaseVisitor<Visitor>
{
public:
    Visitor(BaseConsumer *consumer = NULL);
    virtual ~Visitor() {}

    virtual bool VisitStmt(clang::Stmt *stmt);

private:
    int depthCounter;
};

typedef BaseConsumerWithVisitor<Visitor> Consumer;

}}  // namespace sgc::private_data_members_matching
