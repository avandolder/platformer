#ifndef COMMON_H
#define COMMON_H

/* Include std headers */
#include <iostream>
#include <cstdlib>
#include <mutex>
#include <thread>

/* Include library headers */
#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>
#include <SFML/System.hpp>
#include <lua.hpp>

/* Include project headers */
#include "logic.hpp"
#include "gameObject.hpp"
#include "enums.hpp"
#include "map.hpp"
#include "game.hpp"

const int winWidth  = 320;
const int winHeight = 240;

extern sf::Font consolas;
extern gameObject *object;
extern gameObject player;
extern map_t *map;
extern Game game;
extern lua_State *pfLuaState;

extern std::string windowTitle;

void cleanup();
//void handleKeyPress(sf::Event::KeyEvent key);
int loadGameFile(std::string fileName);
int loadFiles();
int startLua();

#endif // COMMON_H
