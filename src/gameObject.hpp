#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "enums.hpp"

typedef struct
{
    bool left;
    bool right;
    bool top;
    bool bottom;
    bool collided;
    int objectHit;
    int typeOfObjectHit;
} collisionType;

class gameObject
{
public:
    /* Constructor
        */
    gameObject();
    /* create
       Initializes animation (direction/frames),
       size (width/height), and object number */
    void create(int objNum, int direction, int totalFrames,
                int width, int height);

    /* getSprite
        Returns the appropriate sprite for drawing */
    sf::Sprite getSprite();
    /** Moves the object sprite
        \param x x-coordinate
        \param y y-coordinate
     */
    void move(float x, float y);
    /** setPosition
     * \param x X-coordinate
     * \param y Y-coordinate
     * Sets spr's position */
    void setPosition(float x, float y);
    /* getPosition
        Gets the position of spr */
    sf::Vector2f getPosition();
    /* changeDirection
        @arg newDirection
        Changes the sprite's direction
        Sets direction to newDirection */
    void changeDirection(int newDirection);
    /* flipFrame
        Flips to the next frame of animation */
    void flipFrame();

    float getX() {return x;}
    float getY() {return y;}

    /* walk
        */
    void walk(int newDirection);
    /* jump
        */
    void jump();
    /* isJumping
        */
    bool isJumping() { return jumping; }

    /* update
        Update the sprite */
    void update();

    void setCanMove(bool val) { canMove = val; }
    void stopWalking() { walking = false; }

    void setCanFall(bool val) { canFall = val; }

    collisionType didHit(int property, float x, float y);
    collisionType checkObjectCollisions();
    bool collided(gameObject *obj);

    bool getCanDoubleJump() { return canDoubleJump; }
    void setCanDoubleJump(bool val) { canDoubleJump = val; }

    int getWidth() { return width; }
    int getHeight() { return height; }

    /** getObjectTypeNumber
     * \return The objects::objectNumber enum value of this object
     */
    int getObjectTypeNumber() { return m_objectTypeNumber; }
    /** setObjectTypeNumber
     * \param val Value to set the objectTypeNumber to
     */
    void setObjectTypeNumber(int val) { m_objectTypeNumber = val; }

    /** getCurrentObjectNumber
     * \return The objects::objectNumber enum value of this object
     */
    int getCurrentObjectNumber() { return m_currentObjectNumber; }
    /** setCurrentObjectNumber
     * \param val Value to set the objectTypeNumber to
     */
    void setCurrentObjectNumber(int val) { m_currentObjectNumber = val; }

    /** Move the sprite until it is out of solid blocks
     */
    void moveObjectOutOfSolid();

    /** Set the object to inactive */
    void setInactive() { inactive = true; }
    /** Set the object to active */
    void setActive() { inactive = false; }
    /** Check if the object is inactive or not
     * \return If the object is inactive or not
     */
    bool checkInactive() { return inactive; }
    /** Check if the object appears only once
     * \return If the object appears only once
     */
    bool appearsOnlyOnce() { return m_appearsOnlyOnce; }
    /** Set if the object only appears once
     * \param val The value to set m_appearsOnlyOnce
     */
    void setAppearsOnlyOnce(bool val) { m_appearsOnlyOnce = val; }

    /** Create the object by loading it's '.obj' file
     * \param fileName Name of the file to load
     * \return Whether or not the file loaded properly
     */
    int load(std::string fileName);
    /** Loads the sprite sheet, initializing spr and texture
     * \param fileName Name of the sprite sheet to load
     * \return Whether the sprite sheet loaded or not
     */
    int loadSpriteSheet(std::string fileName);
    /** Loads the logic file, initializing logic
     * \param fileName Name of the logic file to load
     * \return Whether the logic file loaded or not
     */
    int loadLogicFile(std::string fileName);

    /** Changes the object's health
     * \param amount Amount to change the health by
     */
    void changeHealth(int amount) { health += amount; }
    /** Set the object's maximum health
     * \param val Value to set the maxHealth to
     */
    void setMaxHealth(int val) { maxHealth = val; }

    void setSpeed(float val) { speed = val; }
    float getSpeed() { return speed; }

private:

    logic m_logic; //!< Member variable "m_logic"

    sf::Texture texture;
    sf::Sprite spr;

    int m_objectTypeNumber; //!< Member variable "objectTypeNumber"
    int m_currentObjectNumber; //!< Member variable "currentObjectNumber"

    int direction = 0;
    int frame = 0;
    int totalFrames = 4;
    int width;
    int height;

    int health;
    int maxHealth;

    float speed;

    float x = 0.0;
    float y = 0.0;
    bool canMove = false;
    bool walking = false;

    bool canJump = true;
    bool jumping = false;
    bool fallAfterJump = false;
    float jumpStage = 0;
    bool canDoubleJump = false;
    bool isDoubleJumping = false;

    bool canFall = true;
    bool falling = false;
    float fallStage =  1;
    bool canFly = false;
    bool flying = false;

    bool inactive = false;
    bool m_appearsOnlyOnce = false; //!< Member variable "m_appearsOnlyOnce"
};

#endif /* GAMEOBJECT_H */
