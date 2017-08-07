#pragma once

#include <clang/AST/Type.h>

class Types
{
public:
    static clang::QualType Int();

    template <typename T>
    static bool is(const clang::QualType& type);

    static bool isInt(const clang::QualType& type);
    static bool isBool(const clang::QualType& type);
};