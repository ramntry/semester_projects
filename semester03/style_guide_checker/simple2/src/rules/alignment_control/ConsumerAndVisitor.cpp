#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/Lexer.h>
#include "../../support/namestyles.h"
#include "ConsumerAndVisitor.h"

using namespace sgc::alignment_control;

Visitor::Visitor(BaseConsumer *consumer)
    : BaseVisitor(consumer)
    , depthCounter(0)
{
}

bool Visitor::VisitStmt(clang::Stmt *stmt)
{
    using namespace clang;

    SourceLocation loc = stmt->getLocStart();
    SourceManager &sm = sourceManager();
    llvm::errs() << loc.printToString(sm) << "\n";

    return true;
}

