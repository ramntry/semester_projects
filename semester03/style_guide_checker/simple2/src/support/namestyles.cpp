#include <llvm/ADT/StringRef.h>
#include "namestyles.h"

using namespace sgc;

bool namestyles::matchCamel(std::string const &name)
{
    return llvm::Regex("^[a-z]+([A-Z][0-9a-z]*)*$").match(name);
}

bool namestyles::matchCapitalizeCamel(std::string const &name)
{
    return llvm::Regex("^([A-Z][0-9a-z]*)+$").match(name);
}
