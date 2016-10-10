#pragma once

#include "catch.hpp"

#include <clang/AST/Type.h>

#include "context.h"

extern clang::QualType INT_TYPE;

std::unique_ptr<Context> testCode(std::string code);
std::string typeToStr(const clang::QualType& type);