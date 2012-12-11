#pragma once
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/ASTUnit.h>
#include "BaseAction.h"

namespace sgc {

class ASTUnitWrapper
{
public:
    ASTUnitWrapper(int argc, char const **argv);
    ~ASTUnitWrapper() { delete unit_; }

    template <typename Consumer>
    void runWithConsumer();

    template <typename Action>
    void runWithAction();

    template <typename Action, typename ArgType>
    void runWithAction(ArgType arg);

private:
    void run(clang::ASTFrontendAction *action);

    llvm::IntrusiveRefCntPtr<clang::DiagnosticsEngine> diags_;
    clang::CompilerInvocation *invoc_;
    clang::ASTUnit *unit_;
};

ASTUnitWrapper::ASTUnitWrapper(int argc, char const **argv)
    : diags_(clang::CompilerInstance::createDiagnostics(
             new clang::DiagnosticOptions, argc, argv))
    , invoc_(new clang::CompilerInvocation)
{
    using namespace clang;
    using namespace llvm;

    CompilerInvocation::CreateFromArgs(*invoc_, argv + 1, argv + argc, *diags_);
    unit_ = ASTUnit::LoadFromCompilerInvocation(invoc_, diags_);
}

void ASTUnitWrapper::run(clang::ASTFrontendAction *action)
{
    clang::ASTUnit::LoadFromCompilerInvocationAction(invoc_, diags_, action, unit_);
}

template <typename Consumer>
void ASTUnitWrapper::runWithConsumer()
{
    BaseAction<Consumer> action;
    run(&action);
}

template <typename Action>
void ASTUnitWrapper::runWithAction()
{
    Action action;
    run(&action);
}

template <typename Action, typename ArgType>
void ASTUnitWrapper::runWithAction(ArgType arg)
{
    Action action(arg);
    run(&action);
}

}  // namespace sgc

