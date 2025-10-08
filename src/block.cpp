#include "block.h"

void Block::init(MaterialType materialType, int posX, int posY)
{
	setMatType(materialType);
	shape.setSize(sf::Vector2f(10.f, 10.f));
	shape.setPosition(posX, posY);
}

void Block::render(sf::RenderWindow& window) const
{
	window.draw(shape);
}

void Block::setMatType(MaterialType type)
{
	m_materialType = type;
	switch (m_materialType)
	{
	case MaterialType::Water:
	{
		shape.setFillColor(sf::Color(0, 0, 255));
		break;
	}
	case MaterialType::Sand:
	{
		shape.setFillColor(sf::Color(255, 255, 0));
		break;
	}
	case MaterialType::Stone:
	{
		shape.setFillColor(sf::Color(200, 200, 200));
		break;
	}
	case MaterialType::Metal:
	{
		shape.setFillColor(sf::Color(55, 55, 55));
		break;
	}
	case MaterialType::Ground:
	{
		shape.setFillColor(sf::Color(73, 29, 0));
		break;
	}
	default:
	{
		shape.setFillColor(sf::Color(0, 0, 0, 0));
	}
	}
}
