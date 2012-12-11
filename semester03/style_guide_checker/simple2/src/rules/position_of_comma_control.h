#pragma once
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/Lexer.h>
#include "../base/BaseAction.h"

namespace sgc {
namespace position_of_comma_control {

class Action : public BaseAction<void>
{
protected:
    virtual void ExecuteAction();
};

void Action::ExecuteAction()
{
    using namespace clang;

    Preprocessor &pp = getCompilerInstance().getPreprocessor();
    SourceManager &sm = pp.getSourceManager();

    llvm::MemoryBuffer const *fromFile = sm.getBuffer(sm.getMainFileID());
    Lexer lexer(sm.getMainFileID(), fromFile, sm, pp.getLangOpts());
    lexer.SetKeepWhitespaceMode(true);

    Token prevToken;
    lexer.LexFromRawLexer(prevToken);
    if (prevToken.is(tok::eof)) {
        return;
    }
    Token token;
    lexer.LexFromRawLexer(token);
    while (token.isNot(tok::eof)) {
        if (token.isAtStartOfLine() && prevToken.is(tok::comma)) {
            llvm::errs() << prettyLocation(prevToken)
                << "Comma should be moved to the next line\n";
        }
        prevToken = token;
        lexer.LexFromRawLexer(token);
    }
}

}}  // namespace sgc::position_of_comma_control
