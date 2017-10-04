#include "common.hpp"

#include <fstream>

std::string *objectFileName;
int numberOfObjectFiles;
std::string *mapFileName;
int numberOfMapFiles;

int loadGameFile(std::string fileName)
{
    std::ifstream gameFile;

    gameFile.open(fileName, std::ios::in);

        if(!gameFile.is_open())
            return 1;

        std::getline(gameFile, windowTitle);

        gameFile >> numberOfObjectFiles;
        object = new gameObject[numberOfObjectFiles];
        objectFileName = new std::string[numberOfObjectFiles];

        for(int i = 0; i < numberOfObjectFiles; i++)
            gameFile >> objectFileName [i];

        gameFile >> numberOfMapFiles;
        map = new map_t[numberOfMapFiles];
        mapFileName = new std::string[numberOfMapFiles];

        for(int i = 0; i < numberOfMapFiles; i++)
            gameFile >> mapFileName [i];

    gameFile.close();

    return 0;
}

int loadFiles()
{
    int error = 0;

    // Load Consolas font
    if(!consolas.loadFromFile("consola.ttf"))
        error = 1;

    // Loop and load all objects listed in the game file
    for(int i = 0; i < numberOfObjectFiles; i++)
        if(object[i].load(objectFileName[i]))
            error += 1;

    std::cout << "loaded sprites.. " << std::flush;

    // Loop and load all maps listed in the game file
    for(int i = 0; i < numberOfMapFiles; i++)
        if(map[i].load(mapFileName[i]))
            error += 1;

    std::cout << "loaded maps.. " << std::flush;

    return error;
}

int Game::load(std::string fileName)
{
    return 0;
}

int gameObject::load(std::string fileName)
{
    int error = 0;

    std::string imageFile, logicFile;
    std::string moveOrNot, jumpOrNot, flyOrNot;
    std::string startingDirection;
    int totalFrames, startingFrame;
    int width, height;
    std::string appearOnce;
    int objectNum;

    this->speed = 0.5;

    std::ifstream objectFile;
    objectFile.open(fileName, std::ios::in);
        if(!objectFile.is_open())
            return 1;

        objectFile >> imageFile;
        loadSpriteSheet(imageFile);

        objectFile >> logicFile;
        if(logicFile.compare("player") != 0)
        {
            if(m_logic.load(logicFile))
                return 2;
        }
        else
            this->m_currentObjectNumber = -1;

        objectFile >> objectNum;
        m_objectTypeNumber = objectNum;

        objectFile >> moveOrNot;
        if(moveOrNot.compare("canMove") == 0)
            canMove = true;
        else
            canMove = false;

        objectFile >> startingDirection;
        if(startingDirection.compare("left") == 0)
            direction = direction::left;
        else if(startingDirection.compare("right") == 0)
            direction = direction::right;
        else if(startingDirection.compare("up") == 0)
            direction = direction::up;
        else if(startingDirection.compare("down") == 0)
            direction = direction::down;
        else
            direction = 0;

        objectFile >> totalFrames;
        this->totalFrames = totalFrames;

        objectFile >> startingFrame;
        frame = startingFrame;

        objectFile >> width;
        this->width = width;

        objectFile >> height;
        this->height = height;

        objectFile >> jumpOrNot;
        if(jumpOrNot.compare("canJump") == 0)
            canJump = true;
        else
            canJump = false;

        objectFile >> flyOrNot;
        if(flyOrNot.compare("canJump") == 0)
            canFly = true;
        else
            canFly = false;

        objectFile >> appearOnce;
        if(appearOnce.compare("appearOnce") == 0)
            m_appearsOnlyOnce = true;
        else
            m_appearsOnlyOnce = false;

    objectFile.close();

    return error;
}

int gameObject::loadSpriteSheet(std::string fileName)
{
    // Load a sprite to display
    if (!texture.loadFromFile(fileName))
        return 1;
    spr.setTexture(texture);
    return 0;
}

int logic::load(std::string fileName)
{
    int error = 0;

    std::string luaCode;
    std::string condition;
    int argument;
    int condNumber = 0;
    std::string currentLine;

    logicCondition temp;

    std::ifstream logicFile;
    logicFile.open(fileName, std::ios::in);
        if(!logicFile.is_open())
            return 1;

        std::cout << "opened logic file " << fileName << ".. ";

        logicFile >> condition;
        while(!logicFile.eof())
        {
            std::cout << condition << std::endl;
            if(condition.compare("idle") == 0)
                temp.condType = logicCondition::idle;
            else if(condition.compare("hitbyplayer") == 0)
                temp.condType = logicCondition::hitByPlayer;
            else if(condition.compare("hitbyitem") == 0)
            {
                temp.condType = logicCondition::hitByItem;
                logicFile >> argument;
                temp.argument = argument;
            }
            else if(condition.compare("hitbyobject") == 0)
            {
                temp.condType = logicCondition::hitByObject;
                logicFile >> argument;
                temp.argument = argument;
            }
            else if(condition.compare("hitwall") == 0)
            {
                temp.condType = logicCondition::hitWall;
                logicFile >> argument;
                temp.argument = argument;
            }

            std::getline(logicFile, currentLine);
            while(currentLine.compare("endcondition") != 0)
            {
                luaCode.append("\n");
                luaCode.append(currentLine);
                std::getline(logicFile, currentLine);
            }

            addCondition(temp);
            setLuaCode(condNumber, luaCode);

            std::cout << luaCode << std::endl;

            luaCode = std::string("");

            logicFile >> condition;
            condNumber++;
        }

    logicFile.close();

    return error;
}

int map_t::load(std::string fileName)
{
    int error = 0, i = 0;

    int mapWidth, mapHeight;
    int *propertyArray;
    std::string imageFile;
    std::string checkParallax, checkOverLayer;
    int numberOfObjects;
    int *objectsOnMap;
    float *objX, *objY;
    int numberOfWarps = -1;
    mapLocation *warp = nullptr;

    std::ifstream mapFile;
    mapFile.open(fileName, std::ios::in);
    if(!mapFile.is_open())
        return 1;

    std::cout << "opened map.. " << std::flush;

    std::getline(mapFile, imageFile);

    mapFile >> checkParallax;
    if(checkParallax.compare("parallax") == 0)
        this->parallax = true;
    else
        this->parallax = false;

    std::cout << "got " << checkParallax << ".. " << std::flush;

    mapFile >> checkOverLayer;
    if(checkOverLayer.compare("overlayer") == 0)
        this->m_hasOverLayer = true;
    else
        this->m_hasOverLayer = false;

    mapFile >> numberOfObjects;
    m_numberOfContainedObject = numberOfObjects;

    std::cout << "got " << numberOfObjects << " objects.. " << std::flush;

    objectsOnMap = new int[numberOfObjects];
    objX = new float[numberOfObjects];
    objY = new float[numberOfObjects];
    for( i = 0; i < numberOfObjects; i++ )
    {
        mapFile >> objectsOnMap[i];
        mapFile >> objX[i];
        mapFile >> objY[i];
    }

    std::cout << "read " << i << " objects.. " << std::flush;

    mapFile >> mapWidth;
    mapFile >> mapHeight;

    propertyArray = new int[(mapWidth * 2) * (mapHeight * 2)];

    for( i = 0; i < ((mapWidth * 2) * (mapHeight * 2)); i++ )
    {
        mapFile >> propertyArray[i];
        if(propertyArray[i] >= tile::warp)
        {
            int warpNumber = propertyArray[i] - tile::warp;
            if(numberOfWarps < warpNumber)
            {
                numberOfWarps = warpNumber;
            }
        }
    }

    std::cout << "read " << i << " entry property array.. " << std::flush;

    if(numberOfWarps > -1)
    {
        // Load up the map warp spots.
        // numberOfWarps + 1 is nessecary because numberOfWarps starts from 0,
        // but array declarations start from 1
        warp = new mapLocation[numberOfWarps + 1];
        for( i = 0; i <= numberOfWarps; i++ )
        {
            mapFile >> warp[i].mapNumber;
            mapFile >> warp[i].x;
            mapFile >> warp[i].y;

            std::cout << "read warp location #" << warp[i].mapNumber
                      << " (" << warp[i].x << "," << warp[i].y << ").. " << std::flush;
        }
    }

    std::cout << "read " << numberOfWarps+1 << " warp location" <<
                 ((numberOfWarps+1) > 1 ? "s." : ".") << ". " << std::flush;

    mapFile.close();

    m_containedObject = new gameObject[numberOfObjects];
    for( i = 0; i < numberOfObjects; i++ )
    {
        m_containedObject[i] = object[objectsOnMap[i]];
        m_containedObject[i].setPosition(objX[i], objY[i]);
        m_containedObject[i].setCurrentObjectNumber(i);
        std::cout << "object " << i << ".. " << std::flush;
    }

    std::cout << "filled " << i << " objects.. " << std::flush;

    if(setTexture(imageFile))
        error += 2;
    setFGRect( sf::IntRect(0, mapHeight * 32, mapWidth * 32, mapHeight * 32) );
    setBGRect( sf::IntRect(0, 0, mapWidth * 32, mapHeight * 32) );
    setSize(mapWidth, mapHeight);

    tileProperty = propertyArray;

    this->numberOfWarps = numberOfWarps;
    this->warp = warp;

    std::cout << "loaded map " << fileName << error << ".. " << std::flush;

    delete [] objX;
    delete [] objY;
    delete [] objectsOnMap;

    return error;
}
