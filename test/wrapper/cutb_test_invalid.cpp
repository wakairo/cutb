#include "cutb_config.h"

namespace {

::cutb::Parser::TestGrp
    group_with_invalid_path("GroupWithInvalidPath",
                            "end_with_slash_and_no_file_name/", 5);
::cutb::Parser::TestGrpEnd
    group_end_with_invalid_path("end_with_slash_and_no_file_name/", 7);
}
