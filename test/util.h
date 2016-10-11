#pragma once

#include "catch.hpp"

#include <clang/AST/Type.h>

#include "context.h"

std::unique_ptr<Context> testCode(std::string code);
std::string typeToStr(const clang::QualType& type);