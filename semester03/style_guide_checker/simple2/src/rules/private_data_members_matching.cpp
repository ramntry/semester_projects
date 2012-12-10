#include <clang/Basic/SourceManager.h>
#include "../support/namestyles.h"
#include "private_data_members_matching.h"

using namespace sgc::private_data_members_matching;

// Visitor
Visitor::Visitor(BaseConsumer *consumer)
    : BaseVisitor(consumer)
{
}

bool Visitor::VisitFieldDecl(clang::FieldDecl *decl)
{
    if (decl->isCXXClassMember()
            && decl->getAccess() == clang::AS_private
            && !match(decl->getNameAsString()))
    {
        printFilenameIfItWasChanged(decl);

        llvm::errs() << prettyLocation(decl)
            << "Name of private data member doesn't match: "
            << classAndFieldNames(decl) << "\n";
    }

    return true;
}

bool Visitor::match(std::string const &name) const
{
    return name.empty() || (
        (name[0] == 'm') && sgc::namestyles::matchCapitalizeCamel(name.substr(1)));
}

std::string Visitor::classAndFieldNames(clang::FieldDecl *decl) const
{
    using namespace clang;

    CXXRecordDecl *classDecl = cast<CXXRecordDecl>(decl->getDeclContext());
    return classDecl->getNameAsString() + "::" + decl->getNameAsString();
}

