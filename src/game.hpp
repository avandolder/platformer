#ifndef GAME_H
#define GAME_H

#include "common.hpp"

class Game
{
    public:
        /** Default constructor */
        Game() {}
        /** Default destructor */
        ~Game() { delete [] m_activeObject; }
        /** Create the game window
         * \param width Width of the game window
         * \param height Height of the game window
         * \param title Title of the game window
         */
        void create(int width, int height, std::string title);
        /** Access m_currentMap
         * \return The current value of m_currentMap
         */
        unsigned int getCurrentMap() { return m_currentMap; }
        /** Set m_currentMap, and active objects
         * \param val Map to set to
         */
        void setCurrentMap(unsigned int val);
        /** Access m_activeObject
         * \return A pointer to m_activeObject
         */
        gameObject **getActiveObjects() { return &m_activeObject; }
        /** Set m_activeObject
         * \param val New value to set
         */
        void setActiveObjects(gameObject *val) { m_activeObject = val; }
        /** Access m_numberOfActiveObjects
         * \return The current value of m_numberOfActiveObjects
         */
        int getNumberOfActiveObjects() { return m_numberOfActiveObjects; }
        /** Set m_numberOfActiveObjects
         * \param val New value to set
         */
        void setNumberOfActiveObjects(int val) { m_numberOfActiveObjects = val; }
        /** Add a new active game object to the map
         * \param obj Object to add
         * \return Number of the object
         */
        int addActiveObject(gameObject obj);
        /** Get rid of an active game object
         * \param objNum Number of the object to destroy
         */
        void destroyActiveObject(int objNum);
        /** Get an active object
         * \param objNum Number of the object to get
         * \return Pointer to the object
         */
        gameObject *getActiveObject(int objNum) { return &m_activeObject[objNum]; }
        /** Set an object to be inactive
         * \param objNum Number of the object to be made inactive
         */
        void setInactive(int objNum) { m_activeObject[objNum].setInactive(); }

        /** Return a pointer to the object currently being used
         * \return gameObject pointer to the current object
         */
        int getCurrentObject() { return m_currentObject; }

        /** Run the main game loop
         * \return An error code, or 0 for success
         */
        int run();
        /** Load game save state
         * \param fileName Name of the save file
         * \return Whether or not the load was successful (0 or 1)
         */
        int load(std::string fileName);
        /** Save game state
         * \param fileName Name of the file to save to
         * \return Whether or not the save was successful (0 or 1)
         */
        int save(std::string fileName);
        /** Draw to the window
         * \param Drawable object to draw on the window
         */
        void draw(const sf::Drawable& drawable) { m_window.draw(drawable); }

        /** Run the menu
         */
        void runMenu();

    private:

        enum gameState
        {
            startMenu = 0,
            playing,
            menu,
            event,
            exiting,
            total
        };

        gameState m_currentState; //!< Member variable "m_currentState"

        unsigned int m_currentMap; //!< Member variable "m_currentMap"
        sf::RenderWindow m_window; //!< Member variable "m_window"
        gameObject *m_activeObject; //!< Member variable "m_activeObject"
        int m_numberOfActiveObjects; //!< Member variable "m_numberOfActiveObjects"
        int m_windowWidth; //!< Member variable "m_windowWidth"
        int m_windowHeight; //!< Member variable "m_windowHeight"
        std::string m_windowTitle; //!< Member variable "m_windowTitle"

        int m_currentObject; //!< Member variable "m_currentObject"

        sf::Sprite m_currentFG; //!< Member variable "m_currentFG"
        sf::Sprite m_currentBG; //!< Member variable "m_currentBG"
        sf::Sprite m_currentOver; //!< Member variable "m_currentOver"
};

#endif // GAME_H
