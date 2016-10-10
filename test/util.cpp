#include "util.h"

#include "ast/driver.h"

clang::BuiltinType IntBuiltin(clang::BuiltinType::Kind::Int);

clang::QualType INT_TYPE = clang::QualType(&IntBuiltin, 0);

std::unique_ptr<Context> testCode(std::string code)
{
    return runOnString(code);
}

std::string typeToStr(const clang::QualType &type)
{
    return type.getAsString();
}
