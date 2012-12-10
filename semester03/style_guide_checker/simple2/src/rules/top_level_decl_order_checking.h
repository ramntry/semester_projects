#pragma once
#include "../base/BaseConsumer.h"
#include "../base/BaseVisitor.h"

namespace sgc {
namespace top_level_decl_order_checking {

class Consumer : public BaseConsumer
{
public:
    Consumer(clang::CompilerInstance *ci = nullptr
            , llvm::StringRef filename = llvm::StringRef());
    virtual ~Consumer() {}

    virtual bool HandleTopLevelDecl(clang::DeclGroupRef declRef);

private:
    bool freeFunctionHasBeenDeclared_;
};

}}  // namespace sgc::top_level_decl_order_checking
