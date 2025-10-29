#include "ui.h"

sf::RectangleShape UI::m_selectedMatShape;

void UI::init(sf::VideoMode videoMode)
{
	m_selectedMatShape.setSize(sf::Vector2f(30.f, 30.f));
	m_selectedMatShape.setPosition(sf::Vector2f(20.f, videoMode.height - 20.f - 30.f));
	m_selectedMatShape.setFillColor(sf::Color(0, 0, 0, 0));
	changeSelectedMat(MaterialType::Sand);
}

void UI::render(sf::RenderWindow& window) const
{
	window.draw(m_selectedMatShape);
}

void UI::changeSelectedMat(MaterialType selectedMat)
{
	switch (selectedMat)
	{
	case MaterialType::Sand:
	{
		m_selectedMatShape.setFillColor(sf::Color(255, 255, 0));
		break;
	}
	case MaterialType::Water:
	{
		m_selectedMatShape.setFillColor(sf::Color(0, 0, 255));
		break;
	}
	case MaterialType::Stone:
	{
		m_selectedMatShape.setFillColor(sf::Color(135, 135, 135));
		break;
	}
	case MaterialType::Metal:
	{
		m_selectedMatShape.setFillColor(sf::Color(55, 55, 55));
		break;
	}
	case MaterialType::Steam:
	{
		m_selectedMatShape.setFillColor(sf::Color(215, 215, 215));
		break;
	}
	case MaterialType::Ground:
	{
		m_selectedMatShape.setFillColor(sf::Color(73, 29, 0));
		break;
	}
	case MaterialType::Lava:
	{
		m_selectedMatShape.setFillColor(sf::Color(255, 88, 0));
		break;
	}
	default:
	{
		m_selectedMatShape.setFillColor(sf::Color(0, 0, 0, 0));
	}
	}
}