#include <assert.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include "top_level_decl_order_checking.h"

using namespace top_level_decl_order_checking;

Consumer::Consumer()
    : sourceManager_(NULL)
    , freeFunctionHasBeenDeclared_(false)
{
}

bool Consumer::HandleTopLevelDecl(clang::DeclGroupRef declRef)
{
    using namespace clang;

    assert(sourceManager_ != NULL && "Source manager must be set before using");

    // function or record (class/struct/union) declaration
    // is single always
    if (declRef.isDeclGroup()) {
        return true;  // true for continue, otherwise break
    }
    Decl *decl = declRef.getSingleDecl();

    if (isa<FunctionDecl>(decl) && !isa<CXXMethodDecl>(decl)) {
        freeFunctionHasBeenDeclared_ = true;
        return true;
    }

    if (freeFunctionHasBeenDeclared_ && isa<CXXRecordDecl>(decl)) {
        llvm::errs() << "This record declared after function or method: \""
                << cast<CXXRecordDecl>(decl)->getNameAsString() << "\" (";
        decl->getLocation().dump(*sourceManager_);
        llvm::errs() << ")\n";
    }

    return true;
}
