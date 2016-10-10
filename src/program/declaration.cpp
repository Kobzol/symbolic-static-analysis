#include "declaration.h"

Declaration::Declaration(std::string name, clang::QualType type): name(name), type(type)
{

}

std::string Declaration::getName() const
{
    return this->name;
}

clang::QualType Declaration::getType() const
{
    return this->type;
}
