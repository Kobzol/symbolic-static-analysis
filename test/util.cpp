#include "util.h"

Context* testCode(std::string code)
{
    return runOnString(code);
}

std::string typeToStr(const clang::QualType &type)
{
    return type.getAsString();
}
