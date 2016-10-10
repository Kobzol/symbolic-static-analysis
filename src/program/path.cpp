#include "path.h"

#include "util.h"
#include "variable/int_variable.h"

Solver& Path::getSolver()
{
    return this->solver;
}

Variable* Path::addVariable(std::string name, clang::QualType type)
{
    std::string typeName = Util::stripType(type).getAsString();
    Variable* var = nullptr;

    if (typeName == "int")
    {
        var = new IntVariable(Declaration(name, type), &this->solver.getExprBuilder());
    }

    if (var != nullptr)
    {
        return this->addVariable(var);
    }

    return nullptr;
}
Variable* Path::addVariable(Variable* var)
{
    this->variables.push_back(var);
    return var;
}

Variable* Path::getVariableByName(std::string name)
{
    for (Variable* var : this->variables)
    {
        if (var->getName() == name) return var;
    }

    return nullptr;
}
Variable* Path::createConstant()
{
    return new IntVariable(Declaration("", clang::QualType()), &this->solver.getExprBuilder());
}

Path* Path::clone()
{
    Path* newPath = new Path();
    for (Variable* var : this->variables)
    {
        newPath->addVariable(var->clone());
    }
    newPath->solver = this->solver;
    return newPath;
}
