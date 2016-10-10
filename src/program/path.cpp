#include "path.h"

#include "util.h"
#include "variable/int_variable.h"

Path::Path()
{

}
Path::Path(const Path &rhs)
{
    for (auto& var : rhs.variables)
    {
        this->variables.push_back(std::unique_ptr<Variable>(var->clone()));
    }
    this->solver = rhs.solver;
}
Path& Path::operator=(const Path &rhs)
{
    for (auto& var : rhs.variables)
    {
        this->variables.push_back(std::unique_ptr<Variable>(var->clone()));
    }
    this->solver = rhs.solver;

    return *this;
}

Solver& Path::getSolver()
{
    return this->solver;
}

Variable* Path::addVariable(std::string name, clang::QualType type)
{
    std::string typeName = Util::stripType(type).getAsString();
    std::unique_ptr<Variable> var;

    if (typeName == "int")
    {
        var = std::make_unique<IntVariable>(Declaration(name, type), &this->solver.getExprBuilder());
    }

    Variable* ptr = nullptr;
    if (var.get() != nullptr)
    {
        ptr = var.get();
        this->addVariable(std::move(var));
    }

    return ptr;
}
void Path::addVariable(std::unique_ptr<Variable> var)
{
    this->variables.push_back(std::move(var));
}

Variable* Path::getVariableByName(std::string name)
{
    for (auto& var : this->variables)
    {
        if (var->getName() == name) return var.get();
    }

    return nullptr;
}
