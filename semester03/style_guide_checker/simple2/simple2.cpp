#include "src/base/ASTUnitWrapper.h"
#include "src/rules/name_matching.h"
#include "src/rules/private_data_members_matching.h"
#include "src/rules/bool_function_name_matching.h"
#include "src/rules/macro_rules.h"
#include "src/rules/top_level_decl_order_checking.h"

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
        while (RawTok.isNot(tok::eof)) {
            PP.DumpToken(RawTok, true);
            llvm::errs() << "\n";
            RawLex.LexFromRawLexer(RawTok);
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
    }
};

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
    unit.runWithAction<MyDumpRawTokensAction>();
}

