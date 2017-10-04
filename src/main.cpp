#include "common.hpp"

sf::Font consolas;
gameObject *object;
map_t *map;
Game game;
gameObject player;

std::string windowTitle;

int main(int argc, char **argv)
{
    std::string gameFileName;

    if(argc < 2)
        gameFileName = "default.game";
    else
        gameFileName = argv[1];

    if(loadGameFile(gameFileName))
        return EXIT_FAILURE;
    std::cout << "Platformer: Loaded game file " << gameFileName << ".. " << std::flush;

    // Create the game
    game.create(winWidth, winHeight, windowTitle);
    std::cout << "created game.. ";

    // Start up Lua for event and AI handling
    startLua();
    std::cout << "started Lua.. " << std::endl;

    std::cout << "Running script... ";

    luaL_dofile (pfLuaState, "event/script.lua");

    std::cout << "Platformer: Loading files... " << std::flush;

    int error = loadFiles();
    if(error)
    {
        std::cout << "Error loading files " << error << std::endl;
        return EXIT_FAILURE;
    }
    player = object[objects::player];
    player.setPosition(65, 32);

    std::cout << "Done loading." << std::endl;

    // Set the current map -- always the first map file read
    game.setCurrentMap(0);

/* DEBUG
    int x = player.getX(), y = player.getY();
    int x2 = (x + 32) / 16, y2 = (y + 32) / 16;
    x /= 16; y /= 16;
    int coord = (y * (map[0].getWidth() * 2)) + x;
    int coord2 = (y2 * (map[0].getWidth() * 2)) + x2;
    std::cout << map[0].checkProperty(coord) << " " << coord << " " << x << "," << y << std::endl;
    std::cout << map[0].checkProperty(coord2) << " " << coord2 << " " << x2 << "," << y2 << std::endl;

    int i;
    for(i = 0; i < ((10 * 2) * (6 * 2)); i++)
    {
        if((i % 20) == 0)
            std::cout << "\n";
        std::cout << " " << map[maps::sample].checkProperty(i);
    }
DEBUG */

    if(game.run())
        return EXIT_FAILURE;

    std::cout << "Cleaning up... " << std::flush;

    cleanup();

    std::cout << "done." << std::flush;

    std::exit(EXIT_SUCCESS);
}
