#include "common.hpp"

// Access the lua C++ api, allowing the program to run the lua logic scripts
#include <lua.hpp>

logic::logic()
{
    m_hasCondition = new logicCondition[1];
    m_luaCode = new std::string[1];
}

logic::~logic()
{
    //dtor
    delete[] m_hasCondition;
    delete[] m_luaCode;
}

void logic::addCondition(logicCondition cond)
{
    logicCondition *temp = new logicCondition[m_numberOfConditions + 1];
    std::string *tempCode = new std::string[m_numberOfConditions + 1];

    int i;
    for(i = 0; i < m_numberOfConditions; i++)
    {
        temp[i] = m_hasCondition[i];
        tempCode[i] = m_luaCode[i];
    }

    temp[i] = cond;
    m_luaCode = tempCode;

    delete[] m_hasCondition;
    m_hasCondition = temp;
    m_numberOfConditions++;
}

int logic::getConditionNumber(logicCondition cond)
{
    int condNumber = -1;

    for(int i = 0; i < m_numberOfConditions; i++)
        if(cond.condType == m_hasCondition[i].condType
           && cond.argument == m_hasCondition[i].argument)
           condNumber = i;

    return condNumber;
}

