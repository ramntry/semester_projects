#pragma once
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/Lexer.h>
#include "../base/BaseAction.h"

namespace sgc {
namespace line_lengths_control {

class Action : public BaseAction<void>
{
public:
    Action(unsigned max_line_length = 80);

protected:
    virtual void ExecuteAction();

private:
    unsigned max_line_length_;
};

Action::Action(unsigned max_line_length)
    : max_line_length_(max_line_length)
{
}

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
        if (token.isAtStartOfLine()) {
            unsigned column = sm.getSpellingColumnNumber(token.getLocation());
            if (column > max_line_length_) {
                llvm::errs() << prettyLocation(prevToken)
                    << "This line is too long\n";
            }
        }
        prevToken = token;
        lexer.LexFromRawLexer(token);
    }
}

}}  // namespace sgc::line_lengths_control
