#pragma once
#include <clang/AST/ASTConsumer.h>

namespace top_level_decl_order_checking {

class Consumer : public clang::ASTConsumer
{
public:
    Consumer();
    void setSourceManager(clang::SourceManager &sm) { sourceManager_ = &sm; }
    virtual bool HandleTopLevelDecl(clang::DeclGroupRef declRef);

private:
    clang::SourceManager *sourceManager_;
    bool freeFunctionHasBeenDeclared_;
};

}  // namespace top_level_decl_order_checking
