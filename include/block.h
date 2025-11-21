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

    sf::Vector2f getPos() const
    {
        return m_shape.getPosition();
    }

    int getGridI() const
    {
        return gridI;
    }

    int getGridJ() const
    {
        return gridJ;
    }

    int getMoveDir() const
    {
        return m_moveDirection;
    }

    void setMoveDir(int waterMoveDir)
    {
        m_moveDirection = waterMoveDir;
    }

    bool getIsSpawner() const
    {
        return m_isSpawner;
    }

    void setIsSpawner(bool value)
    {
        m_isSpawner = value;
        if (value)
        {
            m_shape.setOutlineColor(sf::Color(255, 255, 255));
            m_shape.setOutlineThickness(-2.f);
        }
        else
        {
            m_shape.setOutlineColor(sf::Color(0, 0, 0));
            m_shape.setOutlineThickness(0.f);
        }
    }

    float getCondensationTimer() const
    {
        return m_condensationTimer;
    }

    void setCondensationTimer(float condensationTimer)
    {
        m_condensationTimer = condensationTimer;
    }

    bool getIsStarter() const
    {
        return m_isStarter;
    }

    void setIsStarter(bool isStarter)
    {
        m_isStarter = isStarter;
    }

    
    static constexpr float CONDENSATION_THRESHOLD = 3000.f;

private:

    int gridI = 0;
    int gridJ = 0;

    sf::RectangleShape m_shape;

    MaterialType m_materialType = MaterialType::None;

    bool m_isSpawner = false;
    bool m_isStarter = false;

    int m_moveDirection = 0; // temp, 0 is not moving, 1 is left, 2 is right

    float m_condensationTimer = 0.f;
};