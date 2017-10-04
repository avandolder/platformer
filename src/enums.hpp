#ifndef ENUMS_H
#define ENUMS_H

namespace objects
{
    enum objectNumber
    {
        player = 0,
        jumpBoot,
        testObject,
        last
    };
};

namespace maps
{
    enum mapNumber
    {
        sample = 0,
        other,
        last
    };
}

namespace direction
{
    enum directionNumber
    {
        left = 0,
        right,
        up,
        down,
        last
    };
};

class tile
{
public:
    static enum
    {
        passable = 0,
        solid,
        ladder,
        warp,
        totalProperties
    } properties;
private:
    int currentProperty = 0;
};

#endif // ENUMS_H
