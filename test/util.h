#pragma once

#include "catch.hpp"

#include <clang/AST/Type.h>

#include <context.h>
#include <ast/driver.h>
#include <solver/solver.h>
#include <program/function.h>
#include <variable/variable.h>
#include <variable/int_variable.h>

const clang::QualType NO_TYPE;

Context* testCode(std::string code);
std::string typeToStr(const clang::QualType& type);