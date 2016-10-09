#pragma once

#include "catch.hpp"

#include <clang/AST/Type.h>

#include <context.h>
#include <driver.h>
#include <solver.h>
#include <function.h>
#include <variable/variable.h>

const clang::QualType NO_TYPE;

Context* testCode(std::string code);
std::string typeToStr(const clang::QualType& type);