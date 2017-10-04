#include "common.hpp"

gameObject::gameObject()
{
}

void gameObject::create(int objNum, int direction, int totalFrames,
                        int width, int height)
{
    this->m_objectTypeNumber = objNum;
    this->direction = direction;
    this->frame = 0;
    this->totalFrames = totalFrames;
    this->width = width;
    this->height = height;
}

sf::Sprite gameObject::getSprite()
{
    spr.setTextureRect(sf::IntRect(width * frame, height * direction, width, height));
    return spr;
}

void gameObject::move(float x, float y)
{
    spr.move(x, y);
    this->x += x;
    this->y += y;
}

void gameObject::setPosition(float x, float y)
{
    spr.setPosition(x, y);
    this->x = x;
    this->y = y;
}

sf::Vector2f gameObject::getPosition()
{
    return sf::Vector2f(x, y);
}

void gameObject::changeDirection(int newDirection)
{
    direction = newDirection;
}

void gameObject::flipFrame()
{
    if(frame < (totalFrames - 1))
        frame++;
    else
        frame = 0;
}

void gameObject::walk(int newDirection)
{
    this->direction = newDirection;
    this->flipFrame();
    walking = true;
}

void gameObject::jump()
{
    if(jumpStage <= 0.0 || (canDoubleJump && !isDoubleJumping))
    {
        // If you can double jump, do so
        if(jumpStage <= 0.0)
            isDoubleJumping = true;
        jumping = true;
        jumpStage = 1.0;
    }
}

collisionType gameObject::didHit(int property, float x, float y)
{
    const int top = 0, center = 1, bottom = 2;
    const int left = 0, middle = 1, right = 2;

    collisionType returnVal;
    unsigned int currMap = game.getCurrentMap();

    int ys[3];
    for(int i = 0; i <= 2; i++)
        ys[i] = (this->y + ((this->height / 2) * i)) / 16;

    int xs[3];
    for(int i = 0; i <= 2; i++)
        xs[i] = (this->x + ((this->width / 2) * i)) / 16;

    int coord[3][3];
    for(int y2 = 0; y2 <= 2; y2++)
        for(int x2 = 0; x2 <= 2; x2++)
            coord[x2][y2] = (ys[y2] * (map[currMap].getWidth() * 2)) + xs[x2];

    returnVal.left = false;
    if(map[currMap].checkProperty(coord[left][center]) == property)
        returnVal.left = true;

    returnVal.right = false;
    if(map[currMap].checkProperty(coord[right][center]) == property)
        returnVal.right = true;

    returnVal.top = false;
    if(map[currMap].checkProperty(coord[middle][top]) == property)
        returnVal.top = true;

    returnVal.bottom = false;
    if( (map[currMap].checkProperty(coord[middle][bottom]) == property)
       && ( (map[currMap].checkProperty(coord[left][bottom]) == property)
          || (map[currMap].checkProperty(coord[right][bottom]) == property) ) )
        returnVal.bottom = true;

    if(returnVal.bottom || returnVal.top || returnVal.left || returnVal.right)
        returnVal.collided = true;
    else
        returnVal.collided = false;

    return returnVal;
}

bool gameObject::collided(gameObject *obj)
{
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    left1 = this->x;
    right1 = this->x + this->width;
    top1 = this->y;
    bottom1 = this->y + this->height;
    left2 = obj->x;
    right2 = obj->x + obj->width;
    top2 = obj->y;
    bottom2 = obj->y + obj->height;

	if (bottom1 < top2) return false;
	if (top1 > bottom2) return false;
	if (right1 < left2) return false;
	if (left1 > right2) return false;

	return true;
}

collisionType gameObject::checkObjectCollisions()
{
    collisionType returnValue = { false, false, false, false, false, -1, objects::last };

    int i;

    int numberOfObjects = game.getNumberOfActiveObjects();
    if(numberOfObjects == 0)
        return returnValue;
    if(getObjectTypeNumber() != objects::player)
        numberOfObjects++;

    for(i = 0; i < numberOfObjects; i++)
    {
        gameObject *currObj;
        currObj = game.getActiveObject(i);
        if((currObj != this) && (!currObj->inactive))
        {
            if(this->collided(currObj))
            {
                returnValue.collided = true;
                returnValue.objectHit = i;
                returnValue.typeOfObjectHit = currObj->getObjectTypeNumber();
            }
        }
    }

    return returnValue;
}

void gameObject::moveObjectOutOfSolid()
{
    collisionType hitSolidOffset;
    int intX = this->x;
    int intY = this->y;

    hitSolidOffset = didHit(tile::solid, intX - 1, intY);
    if(hitSolidOffset.left)
        while(hitSolidOffset.left)
        {
            spr.move(1, 0);
            this->x++;
            hitSolidOffset = didHit(tile::solid, intX - 1, intY);
        }

    hitSolidOffset = didHit(tile::solid, intX + 1, intY);
    if(hitSolidOffset.right)
        while(hitSolidOffset.right)
        {
            spr.move(-1, 0);
            this->x--;
            hitSolidOffset = didHit(tile::solid, intX + 1, intY);
        }

    hitSolidOffset = didHit(tile::solid, intX, intY - 1);
    if(hitSolidOffset.top)
        while(hitSolidOffset.top)
        {
            spr.move(0, 1);
            this->y++;
            hitSolidOffset = didHit(tile::solid, intX, intY - 1);
        }

    hitSolidOffset = didHit(tile::solid, intX, intY + 1);
    if(hitSolidOffset.bottom)
        while(hitSolidOffset.bottom)
        {
            spr.move(0, -1);
            this->y--;
            hitSolidOffset = didHit(tile::solid, intX, intY + 1);
        }

//    if(x < 0)
//        x = 0;
//    else if(x > (map[game.getCurrentMap()].getWidth() - 1) * 32)
//        x = (map[game.getCurrentMap()].getWidth() - 1) * 32;
//
//    if(y < 0)
//        y = 0;
//    else if(y > (map[game.getCurrentMap()].getHeight() - 1) * 32)
//        y = (map[game.getCurrentMap()].getHeight() - 1) * 32;
}

void gameObject::update()
{
    int currMap = game.getCurrentMap();

    collisionType hadCollision;
    hadCollision = checkObjectCollisions();
    if(hadCollision.collided)
        switch(hadCollision.typeOfObjectHit)
        {
        case objects::player:

            break;

        case objects::jumpBoot:
            if(getObjectTypeNumber() == objects::player)
            {
                game.setInactive(hadCollision.objectHit);
                player.setCanDoubleJump(true);
            }
            std::cout << game.getActiveObject(hadCollision.objectHit)->getCurrentObjectNumber() << " ";
            break;

        case objects::testObject:
            if(getObjectTypeNumber() == objects::player)
            {
                game.setInactive(hadCollision.objectHit);
                luaL_dofile(pfLuaState, "event/test.lua");
            }

            std::cout << game.getActiveObject(hadCollision.objectHit)->getCurrentObjectNumber() << " ";
            break;

        default:
            break;
        }

    collisionType hitSolid = didHit(tile::solid, this->x, this->y);
    collisionType hitLadder = didHit(tile::ladder, this->x, this->y);

    if( (!hitSolid.bottom) && canFall && (!flying) && (!jumping) )
    {
        falling = true;
        spr.move(0, 1);
        this->y += 1;
    }
    else
    {
        falling = false;
        fallStage = 1;
    }

    if(jumping && (jumpStage < (canDoubleJump ? 84 : 48)) && (!hitSolid.top))
    {
        spr.move(0, -0.5);
        this->y -= 0.5;
        jumpStage += 0.5;
    }
    else
    {
        if(jumpStage > 0)
            jumpStage -= 1.0;
        else
            isDoubleJumping = false;
        jumping = false;
    }

    if( canMove && walking )
    {
        if( (direction == direction::left) && (this->x > 0) && (!hitSolid.left) )
        {
            spr.move(-speed, 0);
            this->x -= speed;
        }
        else if( (direction == direction::right)
                && ((this->x + this->width) <= (map[currMap].getWidth() * 32))
                && (!hitSolid.right) )
        {
            spr.move(speed, 0);
            this->x += speed;
        }

        if( (direction == direction::up) && hitLadder.top && this->y > 0 )
        {
            spr.move(0, -speed);
            this->y -= speed;
        }
        else if( (direction == direction::down) && hitLadder.bottom
                && ((this->y + this->height) < map[currMap].getHeight() * 32) )
        {
            spr.move(0, speed);
            this->y += speed;
        }
    }

    if(getObjectTypeNumber() == objects::player)
        if(walking && (direction == direction::up))
            for(int i = 0; i <= map[currMap].getNumberOfWarps(); i++)
            {
                collisionType touchedWarp;
                touchedWarp = didHit(i + tile::warp, this->x, this->y);
                if(touchedWarp.collided)
                {
                    mapLocation warpPoint;
                    warpPoint = map[currMap].getWarp(i);
                    game.setCurrentMap(warpPoint.mapNumber);
                    player.setPosition(warpPoint.x, warpPoint.y);
                }
            }

    moveObjectOutOfSolid();
}
