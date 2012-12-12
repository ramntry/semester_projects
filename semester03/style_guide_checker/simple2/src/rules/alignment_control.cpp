#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/Lexer.h>
#include "../support/namestyles.h"
#include "alignment_control.h"

using namespace sgc::alignment_control;

Visitor::Visitor(BaseConsumer *consumer)
    : BaseVisitor(consumer)
{
}

bool Visitor::VisitStmt(clang::Stmt *stmt)
{
    using namespace clang;

    SourceLocation loc = stmt->getLocStart();
    SourceManager &sm = sourceManager();
    llvm::MemoryBuffer const *fromHere = sm.getBuffer(sm.getMainFileID(), loc);
    Lexer lexer(sm.getMainFileID(), fromHere, sm, preprocessor().getLangOpts());

    Token firstToken;
    lexer.LexFromRawLexer(firstToken);
    llvm::errs() << loc.printToString(sm) << " "
                 << preprocessor().getSpelling(firstToken) << "\n";

    return true;
}

