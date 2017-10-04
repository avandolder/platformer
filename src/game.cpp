#include "common.hpp"

void Game::create(int width, int height, std::string title)
{
    m_window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
    m_windowHeight = height;
    m_windowWidth = width;
    m_windowTitle = title;

    m_currentState = playing;

    // Make so multiple events aren't generated if a key is held down
    m_window.setKeyRepeatEnabled(false);

    m_activeObject = nullptr;
    m_numberOfActiveObjects = 0;
    m_currentMap = 0;
}

int Game::addActiveObject(gameObject obj)
{
    gameObject *temp;
    temp = new gameObject[m_numberOfActiveObjects + 1];
    for(int i = 0; i < m_numberOfActiveObjects; i++)
        temp[i] = m_activeObject[i];
    temp[m_numberOfActiveObjects] = obj;
    m_activeObject = temp;
    m_numberOfActiveObjects++;

    delete [] temp;

    return m_numberOfActiveObjects - 1;
}

void Game::destroyActiveObject(int objNum)
{
    gameObject *temp;
    temp = new gameObject[m_numberOfActiveObjects - 1];

    int i = 0;
    for(i = 0; i < objNum; i++)
        temp[i] = m_activeObject[i];

    std::cout << "destroyed " << objNum << " " << std::flush;

    for(i = objNum; i < m_numberOfActiveObjects; i++ )
        temp[i-1] = m_activeObject[i];

    m_activeObject = temp;
    m_numberOfActiveObjects--;

    delete [] temp;
}

int Game::run()
{
    sf::Text text("Platformer", consolas, 20);
    text.setPosition(0, 32*6);
    text.setColor(sf::Color::Green);

    // Start the game loop
    while (m_window.isOpen())
    {
        // Process events
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            // Figure out which event it was
            switch (event.type)
            {
                // User closed the window, causing the game to exit
                case sf::Event::Closed:
                    m_currentState = exiting;
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape:
                            m_currentState = exiting;
                            break;

                        case sf::Keyboard::Space:
                            if(!player.isJumping() && m_currentState == playing)
                                player.jump();
                            break;

                        case sf::Keyboard::Return:
                            if(m_currentState != menu)
                                m_currentState = menu;
                            break;

                        default:
                            break;
                    }
                    break;

                case sf::Event::KeyReleased:
                    break;

                // Don't process other events
                default:
                    break;
            }
        }

        switch(m_currentState)
        {
        case menu:
            runMenu();
            break;

        case playing:
            // Move the player's sprite
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                player.walk(direction::left);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player.walk(direction::right);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                player.walk(direction::up);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                player.walk(direction::down);
            else
                player.stopWalking();

            // Update the active objects
            for(int i = 0; i < m_numberOfActiveObjects; i++)
                if(!m_activeObject[i].checkInactive())
                {
                    m_currentObject = i;
                    m_activeObject[i].update();
                }

            // Update the player's sprite
            m_currentObject = -1;
            player.update();

            // Clear screen
            m_window.clear();

            // Draw the map
            m_window.draw(m_currentBG);
            m_window.draw(m_currentFG);

            // Draw the player
            m_window.draw(player.getSprite());

            // Draw the active objects
            for(int i = 0; i < m_numberOfActiveObjects; i++)
                if(!m_activeObject[i].checkInactive())
                    m_window.draw(m_activeObject[i].getSprite());

            if(map[m_currentMap].hasOverLayer())
                m_window.draw(m_currentOver);

            m_window.draw(text);

            // Update the window
            m_window.display();
            break;

        case exiting:
            m_window.close();
            //cleanup();
            //exit(EXIT_SUCCESS);
            break;

        default:
            break;
        }
    }

    return 0;
}

void Game::runMenu()
{
    // Text for the pause menu
    sf::Text arrow(">", consolas, 16);
    arrow.setPosition(16, 16);
    arrow.setColor(sf::Color::Blue);

    sf::Text resumeGame("Resume Game", consolas, 16);
    resumeGame.setPosition(32, 16);
    resumeGame.setColor(sf::Color::Green);

    sf::Text exitGame("Exit Game", consolas, 16);
    exitGame.setPosition(32, 32);
    exitGame.setColor(sf::Color::Green);

    // variables for the pause menu
    static int currentArrowPos = 1;
    int choice = 0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && currentArrowPos > 1)
        currentArrowPos--;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && currentArrowPos < 2)
        currentArrowPos++;
    arrow.setPosition(16, 16 * currentArrowPos);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        choice = currentArrowPos;

    m_window.clear();
    m_window.draw(resumeGame);
    m_window.draw(exitGame);
    m_window.draw(arrow);

    m_window.display();

    if(choice != 0)
    {
        switch(choice)
        {
            case 1:
                m_currentState = playing;
                break;
            case 2:
                m_window.close();
                break;
            default:
                break;
        }
        currentArrowPos = 1;
    }
}

void Game::setCurrentMap(unsigned int val)
{
    m_currentMap = val;
    m_numberOfActiveObjects = map[val].getNumberOfContainedObjects();
    m_activeObject = map[val].getContainedObjects();

    for(int i = 0; i < m_numberOfActiveObjects; i++)
        if(!m_activeObject[i].appearsOnlyOnce())
            m_activeObject[i].setActive();

    m_currentFG = map[val].getFGLayer();
    m_currentBG = map[val].getBGLayer();
    if(map[val].hasOverLayer())
        m_currentOver = map[val].getOverLayer();
}
