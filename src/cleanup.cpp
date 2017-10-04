#include "common.hpp"

void cleanup()
{
    delete [] map;
    std::cout << "deleted maps.. " << std::flush;

    delete [] object;
    std::cout << "deleted objects.. " << std::flush;

    lua_close(pfLuaState);
    std::cout << "closed lua.. " << std::flush;
}
