#ifndef LOGIC_H
#define LOGIC_H

typedef struct
{
    enum cond
    {
        idle = 0,
        created,
        destroyed,
        hitByPlayer,
        hitByItem,
        hitByObject,
        hitWall,
        total
    };

    cond condType;
    int argument;
    /* int objHitBy;
    int itemHitBy;
    int directionOfWall; */
} logicCondition;

class logic
{
    public:
        /** Default constructor */
        logic();
        /** Default destructor */
        virtual ~logic();

        /** Load up a logic file
         * \param fileName Name of the logic file to load
         * \return If there was an error or not
         */
        int load(std::string fileName);

        /** Set the lua code for a condition
         * \param cond Condition to set the code for
         * \param code Lua code to set in the condition
         */
        void setLuaCode(int cond, std::string code) { m_luaCode[cond] = code; }

        /** Get the lua code for a condition
         * \param cond Condition to set the code for
         */
        std::string getLuaCode(int cond) { return m_luaCode[cond]; }

        /** Add a new condition
         * \param cond Condition to add
         */
        void addCondition(logicCondition cond);

        /** Get lua code number of condition
         * \param cond Condition to find the code of
         * \return Number of the condition (-1 if it doesn't have that condition)
         */
        int getConditionNumber(logicCondition cond);

    private:

        int m_numberOfConditions = 0;

        logicCondition *m_hasCondition;

        std::string *m_luaCode;

};

#endif // LOGIC_H
