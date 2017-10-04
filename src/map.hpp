#ifndef GMAP_H
#define GMAP_H

#include "common.hpp"

typedef struct
{
    int mapNumber;
    float x, y;
} mapLocation;

class map_t
{
    public:
        /** Default constructor */
        map_t();
        /** Constructor w/ parameters */
//      map_t(const char *imageFile, bool hasOverLayer, bool parallax, int width, int height);
        /** Set map size in tiles
         * \param width New width value, in 32px tiles
         * \param height New height value, in 32px tiles
         */
        void setSize(int width, int height) { this->width = width; this->height = height; }
        /** Access width
         * \return The current value of width
         */
        int getWidth() { return width; }
        /** Access height
         * \return The current value of height
         */
        int getHeight() { return height; }
        /** Set height
         * \param val New value to set
         */
        bool hasOverLayer() { return m_hasOverLayer; }
        /** Set overLayer
         * \param val New value to set
         */
        void setOverLayer(bool val) { m_hasOverLayer = val; }
        /** Access parallax
         * \return The current value of parallax
         */
        bool hasParallax() { return parallax; }
        /** Set parallax
         * \param val New value to set
         */
        void setParallax(bool val) { parallax = val; }
        /** Access layers
         * \return The sprite of the layers
         */
        sf::Sprite getBGLayer() { return bgLayer; }
        sf::Sprite getFGLayer() { return fgLayer; }
        sf::Sprite getOverLayer() { return overLayer; }

        int setTexture(std::string fileName);
        sf::Texture getTexture() { return texture; }
        void setFGRect(sf::IntRect newRect) { fgLayer.setTextureRect(newRect); }
        void setBGRect(sf::IntRect newRect) { bgLayer.setTextureRect(newRect); }
        void setOverRect(sf::IntRect newRect) { overLayer.setTextureRect(newRect); }

        /** Set isSolid
         * \param isSolidArray Value to put into isSolid
         */
        void setTileProperty(int *tileProperty) { this->tileProperty = tileProperty; }

        int checkProperty(sf::Vector2f coord);
        int checkProperty(int blockNum) { return tileProperty[blockNum]; }
        /** Get warp point
         * \param warpNum Number of the warp point
         */
        mapLocation getWarp(int warpNum) { return this->warp[warpNum]; }
        /** Get number of warp points
         * \return Number of warp points
         */
        int getNumberOfWarps() { return numberOfWarps; }

        int load(std::string fileName);

        int getNumberOfContainedObjects() { return m_numberOfContainedObject; }
        gameObject *getContainedObjects() { return m_containedObject; }

    private:
        int width; //!< Member variable "width", is width of the map (in 32 pixel tiles)(width * 32 = pixel width)
        int height; //!< Member variable "height", is height of the map (in 32 pixel tiles)(height * 32 = pixel height)
        bool m_hasOverLayer = false; //!< Member variable "hasOverLayer", says whether there is an overlayer or not
        bool parallax = false; //!< Member variable "parallax", says whether the background layer should parallax scroll or not
        sf::Texture texture; //!< Member variable "texture", contains texture of all three layers
        sf::Sprite bgLayer; //!< Member variable "bgLayer", sprite that defines the background layer
        sf::Sprite fgLayer; //!< Member variable "fgLayer", sprite that defines the foreground layer
        sf::Sprite overLayer; //!< Member variable "overLayer", sprite that defines the over layer

        int m_numberOfContainedObject; //!< Member variable "numberOfContainedObject", number of objects on the map
        gameObject *m_containedObject; //!< Member variable "containedObject", points to objects on map

        int *tileProperty; //!< Member variable "tileProperty", array of 16*16 tiles and their properties
        int numberOfWarps = 0; //!< Member variable "numberOfWarps", number of warps on the map
        mapLocation *warp;
};

#endif // GMAP_H
