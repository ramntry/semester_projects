#include <llvm/Support/Regex.h>
#include <clang/Basic/SourceManager.h>
#include "../support/namestyles.h"
#include "name_matching.h"

using namespace sgc::name_matching;

// Visitor
Visitor::Visitor(BaseConsumer *consumer)
    : BaseVisitor(consumer)
{
}

bool Visitor::VisitNamedDecl(clang::NamedDecl *decl)
{
    using namespace clang;

    if (isa<CXXConstructorDecl>(decl) || isa<CXXDestructorDecl>(decl)) {
        return true;
    }
    bool isTypeName = isa<TypeDecl>(decl);

    if ((isTypeName && !matchTypename(decl->getNameAsString()))
            || (!isTypeName && !match(decl->getNameAsString())))
    {
        printFilenameIfItWasChanged(decl);

        llvm::errs() << prettyLocation(decl)
            << (isTypeName ? "Typename" : "Name") << " doesn't match: "
            << decl->getNameAsString() << "\n";
    }

    return true;
}

bool Visitor::match(std::string const &name) const
{
    return name.empty() || sgc::namestyles::matchCamel(name);
}

bool Visitor::matchTypename(std::string const &name) const
{
    return sgc::namestyles::matchCapitalizeCamel(name);
}

