#include <llvm/Support/Regex.h>
#include <clang/Basic/SourceManager.h>
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
    return llvm::Regex("m[A-Za-z][A-Za-z0-9]*").match(name);
}

std::string Visitor::classAndFieldNames(clang::FieldDecl *decl) const
{
    using namespace clang;

    CXXRecordDecl *classDecl = cast<CXXRecordDecl>(decl->getDeclContext());
    return classDecl->getNameAsString() + "::" + decl->getNameAsString();
}

// Consumer
Consumer::Consumer(clang::CompilerInstance *ci, llvm::StringRef filename)
    : BaseConsumer(ci, filename)
    , visitor_(this)
{
}

bool Consumer::HandleTopLevelDecl(clang::DeclGroupRef declGroup)
{
    using namespace clang;

    DeclGroupRef::iterator it = declGroup.begin();
    DeclGroupRef::iterator end = declGroup.end();
    for (; it != end; ++it)
    {
        visitor_.TraverseDecl(*it);
    }
    return true;
}

