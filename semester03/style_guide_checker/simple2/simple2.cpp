#include <assert.h>
#include <llvm/Support/Host.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Lex/Token.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/HeaderSearch.h>
#include <clang/Frontend/Utils.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Parse/ParseAST.h>

#include <clang/Frontend/ASTUnit.h>
#include "../simple/private_data_members_matching.h"

void tryWorkWithASTUnit(int argc, char const **argv)
{
    using namespace clang;
    using namespace llvm;
    using namespace sgc;

    IntrusiveRefCntPtr<DiagnosticsEngine> diags(
            CompilerInstance::createDiagnostics(new DiagnosticOptions, argc, argv));
    ASTUnit *unit = ASTUnit::LoadFromCommandLine(
            argv + 1
            , argv + argc
            , diags
            , "./");
}

int main(int argc, char const **argv)
{
    if (argc < 2) {
        llvm::errs() << "Usage: simple2 <compiler-like-command-line-options>\n";
        return EXIT_FAILURE;
    }

    tryWorkWithASTUnit(argc, argv);
}

