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

void initializePreprocessor(clang::CompilerInstance &ci)
{
    using namespace clang;

    ci.createPreprocessor();
    ci.getPreprocessorOpts().UsePredefines = true;
    Preprocessor &pp = ci.getPreprocessor();

    HeaderSearchOptions headerSearchOptions;
    const char *headerSearchPaths[] = {
        "/usr/include"
        , "/usr/include/x86_64-linux-gnu"
        , "/usr/include/c++/4.7"
        , "/usr/include/c++/4.7/x86_64-linux-gnu"
        , "/usr/lib/gcc/x86_64-linux-gnu/4.7/include"
    };

    for (size_t i = 0; i < sizeof(headerSearchPaths)/sizeof(const char *); ++i) {
        headerSearchOptions.AddPath(headerSearchPaths[i], frontend::Angled, false, false, false);
    }

    InitializePreprocessor(pp, ci.getPreprocessorOpts(), headerSearchOptions, ci.getFrontendOpts());
    pp.getBuiltinInfo().InitializeBuiltins(pp.getIdentifierTable(), pp.getLangOpts());
}

clang::TargetInfo *initializeCompilerInstance(clang::CompilerInstance &ci, clang::ASTConsumer *astConsumer)
{
    using namespace clang;

    ci.createDiagnostics(0, NULL);
    CompilerInvocation::setLangDefaults(ci.getLangOpts(), IK_CXX, LangStandard::lang_gnucxx11);

    TargetOptions targetOptions;
    targetOptions.Triple = llvm::sys::getDefaultTargetTriple();
    TargetInfo *targetInfo = TargetInfo::CreateTargetInfo(ci.getDiagnostics(), targetOptions);
    ci.setTarget(targetInfo);

    ci.createFileManager();
    ci.createSourceManager(ci.getFileManager());
    initializePreprocessor(ci);

    ci.setASTConsumer(astConsumer);

    ci.createASTContext();
    ci.createSema(clang::TU_Complete, NULL);

    return targetInfo;
}

void run(char *filename, clang::ASTConsumer *consumer)
{
    using namespace clang;

    typedef llvm::IntrusiveRefCntPtr<TargetInfo> TargetInfoPtr;

    CompilerInstance ci;
    TargetInfoPtr tiOwner = initializeCompilerInstance(ci, consumer);
    //consumer->setSourceManager(ci.getSourceManager());

    ci.getSourceManager().createMainFileID(ci.getFileManager().getFile(filename));

    ci.getDiagnosticClient().BeginSourceFile(ci.getLangOpts(), &ci.getPreprocessor());
    ParseAST(ci.getPreprocessor(), &ci.getASTConsumer(), ci.getASTContext());
    ci.getDiagnosticClient().EndSourceFile();
}

void tryWorkWithASTUnit(int argc, char const **argv)
{
    using namespace clang;
    using namespace llvm;


    IntrusiveRefCntPtr<DiagnosticsEngine> diags(
            CompilerInstance::createDiagnostics(new DiagnosticOptions, argc, argv));
    ASTUnit *unit = ASTUnit::LoadFromCommandLine(
            argv + 1
            , argv + argc
            , diags
            , "./");
    unit->getSema().Consumer = ASTConsumer();
    unit->Reparse();
}

int main(int argc, char const **argv)
{
    if (argc < 2) {
        llvm::errs() << "Usage: simple2 <compiler-like-command-line-options>\n";
        return EXIT_FAILURE;
    }

    tryWorkWithASTUnit(argc, argv);
}

