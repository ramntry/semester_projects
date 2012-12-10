#include "BaseConsumer.h"

using namespace sgc;

BaseConsumer::BaseConsumer(clang::CompilerInstance *ci , llvm::StringRef filename)
    : ci_(ci)
    , filename_(filename)
{
}

std::string BaseConsumer::prettyLocation(clang::Decl *decl) const
{
    return decl->getLocation().printToString(sourceManager()) + ": ";
}

void BaseConsumer::printFilenameIfItWasChanged(clang::Decl *decl)
{
    std::string currentFileName = sourceManager().getFilename(decl->getLocation());
    if (currentFileName != lastFileName_) {
        llvm::errs() << "\n=== In file \"" << currentFileName << "\" ===\n";
        lastFileName_ = currentFileName;
    }
}

