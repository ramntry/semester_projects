#pragma once
#include <llvm/Support/Regex.h>
#include "../../base/BaseConsumerWithVisitor.h"
#include "../../base/BaseAction.h"

namespace sgc {
namespace alignment_control {

class Action : public BaseAction<void>
{
public:
    Action(std::string const &align_pattern = " ");

protected:
    virtual void ExecuteAction();

private:
    bool match(std::string const &startOfLine);

    llvm::Regex align_regex_;
};

Action::Action(std::string const &align_pattern)
    : align_regex_("^" + align_pattern + "*$")
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

    Token token;
    lexer.LexFromRawLexer(token);
    while (token.isNot(tok::eof)) {
        if (token.isAtStartOfLine() && !match(pp.getSpelling(token).substr(1))) {
            llvm::errs() << prettyLocation(token) << "bad alignment\n";
        }
        lexer.LexFromRawLexer(token);
    }
}

bool Action::match(std::string const &startOfLine)
{
    return align_regex_.match(startOfLine);
}

}}  // namespace sgc::private_data_members_matching
