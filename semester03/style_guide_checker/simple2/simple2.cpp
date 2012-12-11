#include "src/base/ASTUnitWrapper.h"
#include "src/rules/name_matching.h"
#include "src/rules/private_data_members_matching.h"
#include "src/rules/bool_function_name_matching.h"
#include "src/rules/macro_rules.h"
#include "src/rules/top_level_decl_order_checking.h"
#include "src/rules/position_of_comma_control.h"
#include "src/rules/line_lengths_control.h"

/*
#include <clang/Frontend/FrontendActions.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/Lexer.h>

class MyDumpRawTokensAction : public sgc::BaseAction<void>
{
protected:
    virtual void ExecuteAction()
    {
        using namespace clang;

        Preprocessor &PP = getCompilerInstance().getPreprocessor();
        SourceManager &SM = PP.getSourceManager();

        const llvm::MemoryBuffer *FromFile = SM.getBuffer(SM.getMainFileID());
        Lexer RawLex(SM.getMainFileID(), FromFile, SM, PP.getLangOpts());
        RawLex.SetKeepWhitespaceMode(true);

        llvm::errs() << "\n\n=*= Tokens =*=\n\n";
        Token RawTok;
        RawLex.LexFromRawLexer(RawTok);
        int double_spaces_error_counter = 0;
        while (RawTok.isNot(tok::eof)) {
            PP.DumpToken(RawTok, true);
            llvm::errs() << "\n";
            RawLex.LexFromRawLexer(RawTok);

            if (RawTok.is(tok::unknown)) {
                llvm::StringRef spelling = PP.getSpelling(RawTok);
                if (spelling.size() > 1 && spelling[0] != '\n') {
                    ++double_spaces_error_counter;
                }
            }
        }

        Preprocessor::macro_iterator m_it = PP.macro_begin(false);
        Preprocessor::macro_iterator m_end = PP.macro_end(false);

        int counter = 0;
        llvm::errs() << "\n\n=*= Macro =*=\n\n";
        for (; m_it != m_end; ++m_it) {
            llvm::errs() << m_it->first->getName() << "\n";
            ++counter;
        }
        llvm::errs() << "\nmacro counter = " << counter << "\n";
        llvm::errs() << "\n\ndouble spaces error counter = " << double_spaces_error_counter << "\n";
    }
};
*/

int main(int argc, char const **argv)
{
    if (argc < 2) {
        llvm::errs() << "Usage: simple2 <compiler-like-command-line-options>\n";
        return EXIT_FAILURE;
    }

    using namespace sgc;

    ASTUnitWrapper unit(argc, argv);

    unit.runWithConsumer<name_matching::Consumer>();
    unit.runWithConsumer<private_data_members_matching::Consumer>();
    unit.runWithConsumer<bool_function_name_matching::Consumer>();
    unit.runWithConsumer<top_level_decl_order_checking::Consumer>();

    //unit.runWithAction<macro_rules::Action>();
    //unit.runWithAction<MyDumpRawTokensAction>();
    unit.runWithAction<position_of_comma_control::Action>();
    unit.runWithAction<line_lengths_control::Action>(70);
}

