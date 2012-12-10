#include <llvm/Support/Regex.h>
#include <clang/Basic/SourceManager.h>
#include "bool_function_name_matching.h"

using namespace sgc::bool_function_name_matching;

// Visitor
Visitor::Visitor(BaseConsumer *consumer)
    : BaseVisitor(consumer)
{
}

bool Visitor::VisitFunctionDecl(clang::FunctionDecl *decl)
{
    using namespace clang;

    if ((decl->getResultType().getUnqualifiedType().getAsString() == "_Bool")
            && !match(decl->getNameAsString()))
    {
        printFilenameIfItWasChanged(decl);

        llvm::errs() << prettyLocation(decl)
            << "Function returns bool must have name starts with `is` or `has`: "
            << decl->getResultType().getAsString() << ' '
            << decl->getNameAsString() << "\n";
    }

    return true;
}

bool Visitor::match(std::string const &name) const
{
    return name.empty() || llvm::Regex("^(is|has).+").match(name);
}

