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
    void run();

private:
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

template <typename Consumer>
void ASTUnitWrapper::run()
{
    BaseAction<Consumer> action;
    clang::ASTUnit::LoadFromCompilerInvocationAction(invoc_, diags_, &action, unit_);
}

}  // namespace sgc

