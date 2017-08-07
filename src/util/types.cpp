#include "types.h"

typedef clang::BuiltinType::Kind Kind;

Kind IntKind = Kind::Int;
Kind BoolKind = Kind::Bool;

clang::QualType Types::Int()
{
    clang::BuiltinType IntType(IntKind);
    return clang::QualType(&IntType, 0);
}

bool Types::isInt(const clang::QualType& type)
{
    return type->isBuiltinType() && (type->castAs<clang::BuiltinType>()->getKind() == IntKind);
}

bool Types::isBool(const clang::QualType &type)
{
    return type->isBuiltinType() && (type->castAs<clang::BuiltinType>()->getKind() == BoolKind);
}

template<>
bool Types::is<int>(const clang::QualType& type)
{
    return Types::isInt(type);
}
template<>
bool Types::is<bool>(const clang::QualType& type)
{
    return Types::isBool(type);
}

template bool Types::is<int>(const clang::QualType&);
template bool Types::is<bool>(const clang::QualType&);
