#pragma once
#include <llvm/Support/Regex.h>

namespace sgc {
namespace namestyles {

bool matchCamel(std::string const &name);
bool matchCapitalizeCamel(std::string const &name);

}}  // namespace scg::namestyles

