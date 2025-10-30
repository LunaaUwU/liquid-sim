#include "ui.h"

sf::RectangleShape UI::m_selectedMatShape;
sf::Font UI::m_selectedMatFont;
sf::Text UI::m_selectedMatText;

void UI::init(sf::VideoMode videoMode)
{
	m_selectedMatShape.setSize(sf::Vector2f(30.f, 30.f));
	m_selectedMatShape.setPosition(sf::Vector2f(20.f, videoMode.height - 50.f));
	m_selectedMatShape.setFillColor(sf::Color(0, 0, 0, 0));
	changeSelectedMat(MaterialType::Sand);

	m_selectedMatFont.loadFromFile("../assets/fonts/ComicSans.ttf");

	m_selectedMatText.setFont(m_selectedMatFont);
	m_selectedMatText.setCharacterSize(40);
	m_selectedMatText.setPosition(sf::Vector2f(60.f, videoMode.height - 60.f));
	m_selectedMatText.setFillColor(sf::Color(255, 255, 255));
	m_selectedMatText.setString("Sand");
}

void UI::render(sf::RenderWindow& window) const
{
	window.draw(m_selectedMatShape);
	window.draw(m_selectedMatText);
}

void UI::changeSelectedMat(MaterialType selectedMat)
{
	m_selectedMatShape.setFillColor(materialToColor(selectedMat));
	m_selectedMatText.setString(materialToString(selectedMat));
}

void UI::cleanup() {
	// Force destruction before window closes
	m_selectedMatShape = sf::RectangleShape();
	m_selectedMatText = sf::Text();
	m_selectedMatFont = sf::Font();
}