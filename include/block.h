#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "material-type.h"

class Grid;

class Block
{
public:

    void init(MaterialType materialType, int posX, int posY);

    void render(sf::RenderWindow& window) const;

    MaterialType getMatType() const
    {
        return m_materialType;
    }

    void setMatType(MaterialType type);

    bool getMoved()
    {
        return m_moved;
    }

    void setMoved(bool moved)
    {
        m_moved = moved;
    }

private:

    bool m_moved = false;

    sf::RectangleShape shape;

    MaterialType m_materialType;
};