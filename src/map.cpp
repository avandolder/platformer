#include "common.hpp"

// Default constructor
map_t::map_t() {}

/*
map_t::map_t(const char *imageFile, bool hasOverLayer, bool parallax, int width, int height)
{
    //ctor

    // Load up the image file into the texture
    if(!texture.loadFromFile(imageFile))
        std::cout << "error loading map image file\n";

    // Set the sprites
    bgLayer.setTexture(texture);
    bgLayer.setTextureRect(sf::IntRect(0, 0, width*32, height*32));
    fgLayer.setTexture(texture);
    fgLayer.setTextureRect(sf::IntRect(0, height*32, width*32, height*32));
    if(hasOverLayer)
    {
        overLayer.setTexture(texture);
        overLayer.setTextureRect(sf::IntRect(0, (height*32)*2, width*32, height*32));
    }

    // Set the private variables to their respective values
    m_hasOverLayer = hasOverLayer;
    this->parallax = parallax;
    this->width = width;
    this->height = height;
}
*/

int map_t::setTexture(std::string fileName)
{
    if(!texture.loadFromFile(fileName))
        return 1;
    fgLayer.setTexture(texture);
    bgLayer.setTexture(texture);
    if(m_hasOverLayer)
        overLayer.setTexture(texture);
    return 0;
}

int map_t::checkProperty(sf::Vector2f coord)
{
    int bX = coord.x / 16, bY = coord.y / 16;
    return tileProperty[((bY * width) + bX) - 1];
}
