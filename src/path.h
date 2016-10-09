#pragma once

#include <clang/AST/Type.h>

#include <z3++.h>
#include "variable/variable.h"

class Path
{
public:
    Variable* addVariable(std::string name, clang::QualType type)
    {
        Variable* var = new Variable(name, type, &this->solver);
        return this->addVariable(var);
    }
    Variable* addVariable(Variable* var)
    {
        this->variables.push_back(var);
        return var;
    }

    Variable* getVariableByName(std::string name)
    {
        for (Variable* var : this->variables)
        {
            if (var->name == name) return var;
        }

        return nullptr;
    }
    Variable* createConstant()
    {
        return new Variable("", clang::QualType(), &this->solver);
    }

    Path* clone()
    {
        Path* newPath = new Path();
        for (Variable* var : this->variables)
        {
            newPath->addVariable(new Variable(*var));
        }
        newPath->solver = this->solver;
        return newPath;
    }

    std::vector<Variable*> variables;
    Solver solver;
};
