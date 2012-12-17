#include "src/base/ASTUnitWrapper.h"
#include "src/rules/name_matching.h"
#include "src/rules/private_data_members_matching.h"
#include "src/rules/bool_function_name_matching.h"
#include "src/rules/macro_rules.h"
#include "src/rules/top_level_decl_order_checking.h"
#include "src/rules/position_of_comma_control.h"
#include "src/rules/line_lengths_control.h"
#include "src/rules/alignment_control.h"

int main(int argc, char const **argv)
{
    if (argc < 2) {
        llvm::errs() << "Usage: simple2 <compiler-like-command-line-options>\n";
        return EXIT_FAILURE;
    }

    using namespace sgc;

    ASTUnitWrapper unit(argc, argv);

    unit.runWithConsumer<name_matching::Consumer>();
    unit.runWithConsumer<private_data_members_matching::Consumer>();
    unit.runWithConsumer<bool_function_name_matching::Consumer>();
    unit.runWithConsumer<top_level_decl_order_checking::Consumer>();

    unit.runWithAction<position_of_comma_control::Action>();
    unit.runWithAction<line_lengths_control::Action>(70);
}

