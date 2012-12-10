#include "src/base/ASTUnitWrapper.h"
#include "src/rules/name_matching.h"
#include "src/rules/private_data_members_matching.h"
#include "src/rules/bool_function_name_matching.h"
#include "src/rules/top_level_decl_order_checking.h"

int main(int argc, char const **argv)
{
    if (argc < 2) {
        llvm::errs() << "Usage: simple2 <compiler-like-command-line-options>\n";
        return EXIT_FAILURE;
    }

    using namespace sgc;

    ASTUnitWrapper unit(argc, argv);

    unit.run<name_matching::Consumer>();
    unit.run<private_data_members_matching::Consumer>();
    unit.run<bool_function_name_matching::Consumer>();
    unit.run<top_level_decl_order_checking::Consumer>();
}

