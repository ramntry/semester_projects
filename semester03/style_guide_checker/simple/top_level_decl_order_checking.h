#pragma once
#include "BaseConsumer.h"

namespace sgc {
namespace top_level_decl_order_checking {

class Consumer : public BaseConsumer
{
public:
    Consumer();
    virtual bool HandleTopLevelDecl(clang::DeclGroupRef declRef);

private:
    bool freeFunctionHasBeenDeclared_;
};

}}  // namespace sgc::top_level_decl_order_checking
