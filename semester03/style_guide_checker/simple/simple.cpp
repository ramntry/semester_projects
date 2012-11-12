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

#include "top_level_decl_order_checking.h"
#include "private_data_members_matching.h"

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

// task switcher
class Task
{
public:
    static sgc::BaseConsumer *createConsumer();
};

sgc::BaseConsumer *Task::createConsumer()
{
    return new sgc::private_data_members_matching::Consumer;
}

int main(int argc, char **argv)
{
    using namespace clang;
    using namespace sgc;

    typedef llvm::IntrusiveRefCntPtr<TargetInfo> TargetInfoPtr;

    if (argc < 2) {
        llvm::errs() << "Usage: tut4 <source-file-name>\n";
        return EXIT_FAILURE;
    }

    CompilerInstance ci;
    BaseConsumer *consumer = Task::createConsumer();
    TargetInfoPtr tiOwner = initializeCompilerInstance(ci, consumer);
    consumer->setSourceManager(ci.getSourceManager());

    ci.getSourceManager().createMainFileID(ci.getFileManager().getFile(argv[1]));

    ci.getDiagnosticClient().BeginSourceFile(ci.getLangOpts(), &ci.getPreprocessor());
    ParseAST(ci.getPreprocessor(), &ci.getASTConsumer(), ci.getASTContext());
    ci.getDiagnosticClient().EndSourceFile();
}

