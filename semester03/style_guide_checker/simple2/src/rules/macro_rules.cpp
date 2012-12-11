#include <clang/Frontend/CompilerInstance.h>
#include <clang/Lex/Preprocessor.h>
#include "macro_rules.h"

using namespace sgc::macro_rules;

void Action::ExecuteAction()
{
    using namespace clang;

    CompilerInstance &ci = getCompilerInstance();
    Preprocessor &pp = ci.getPreprocessor();

    llvm::errs() << "`bool macro_rules::Action::ExecuteAction()` was runned\n";
}

