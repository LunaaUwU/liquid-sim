#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "material-type.h"

class Grid;

class Block
{
public:

    void init(MaterialType materialType, int posX, int posY, int i, int j);

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

    sf::Vector2f getPos()
    {
        return m_shape.getPosition();
    }

    int getGridI()
    {
        return gridI;
    }

    int getGridJ()
    {
        return gridJ;
    }

    int getMoveDir()
    {
        return m_moveDirection;
    }

    void setMoveDir(int waterMoveDir)
    {
        m_moveDirection = waterMoveDir;
    }

    bool getIsSpawner()
    {
        return m_isSpawner;
    }

    void setIsSpawner(bool value)
    {
        m_isSpawner = value;
        if (value)
        {
            m_shape.setOutlineColor(sf::Color(255, 255, 255));
            m_shape.setOutlineThickness(2.f);
        }
        else
        {
            m_shape.setOutlineColor(sf::Color(0, 0, 0));
            m_shape.setOutlineThickness(0.f);
        }
    }

private:

    bool m_moved = false;

    int gridI;
    int gridJ;

    sf::RectangleShape m_shape;

    MaterialType m_materialType;

    bool m_isSpawner = false;

    int m_moveDirection = 0; // temp, 0 is not moving, 1 is left, 2 is right
};