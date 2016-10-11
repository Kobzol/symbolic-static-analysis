#include "util.h"

#include "ast/driver.h"

std::unique_ptr<Context> testCode(std::string code)
{
    return runOnString(code);
}

std::string typeToStr(const clang::QualType &type)
{
    return type.getAsString();
}
