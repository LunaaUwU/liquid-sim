#include "ui.h"

sf::RectangleShape UI::m_selectedMatShape;
sf::Font UI::m_selectedMatFont;
sf::Text UI::m_selectedMatText;
sf::RectangleShape UI::m_spawnerCheckBox;

MaterialType UI::SELECTED_MATERIAL;

void UI::init(sf::VideoMode videoMode)
{
	InputManager::onLeftClick([this]() -> bool {
		if (m_selectedMatShape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) ||
			m_selectedMatText.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
		{
			return true;
		}
		else
			return false;
		});

	InputManager::onRightClick([this]() -> bool {
		if (m_selectedMatShape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) ||
			m_selectedMatText.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
		{
			return true;
		}
		else
			return false;
		});

	InputManager::onScroll([this, videoMode](float delta) {
		if (delta < 0)
			changeSelectedMat(1);
		else
			changeSelectedMat(-1);
		m_spawnerCheckBox.setPosition(sf::Vector2f(75.f + m_selectedMatText.getLocalBounds().width, videoMode.height - 50.f));
		return false;
		});

	m_selectedMatShape.setSize(sf::Vector2f(30.f, 30.f));
	m_selectedMatShape.setPosition(sf::Vector2f(20.f, videoMode.height - 50.f));
	m_selectedMatShape.setFillColor(materialToColor(MaterialType::Sand));

	m_selectedMatFont.loadFromFile("../assets/fonts/ComicSans.ttf");

	m_selectedMatText.setFont(m_selectedMatFont);
	m_selectedMatText.setCharacterSize(40);
	m_selectedMatText.setPosition(sf::Vector2f(60.f, videoMode.height - 60.f));
	m_selectedMatText.setFillColor(sf::Color(255, 255, 255));
	m_selectedMatText.setString("Sand");

	m_spawnerCheckBox.setSize(sf::Vector2f(30.f, 30.f));
	m_spawnerCheckBox.setPosition(sf::Vector2f(75.f + m_selectedMatText.getLocalBounds().width, videoMode.height - 50.f));
	m_spawnerCheckBox.setFillColor(sf::Color(255, 255, 255));
	m_spawnerCheckBox.setOutlineThickness(-2.f);
	m_spawnerCheckBox.setOutlineColor(sf::Color(0, 0, 0));
	
	int numMaterials = static_cast<int>(MaterialType::Count);
	MaterialType material;
	for (int i = 0; i < numMaterials; i++)
	{
		material = static_cast<MaterialType>(i);
		if (material != MaterialType::Ground && material != MaterialType::Count && material != MaterialType::None)
		{
			m_materialList.push_back(material);
		}
	}
	m_selectedMaterialIndex = 0;
	SELECTED_MATERIAL = m_materialList[m_selectedMaterialIndex];
}

void UI::render(sf::RenderWindow& window) const
{
	window.draw(m_selectedMatShape);
	window.draw(m_selectedMatText);
	window.draw(m_spawnerCheckBox);
}

void UI::changeSelectedMat(int value)
{
	m_selectedMaterialIndex += value;
	if (m_selectedMaterialIndex >= static_cast<int>(m_materialList.size()))
	{
		m_selectedMaterialIndex = 0;
	}
	if (m_selectedMaterialIndex < 0)
	{
		m_selectedMaterialIndex = m_materialList.size() - 1;
	}
	SELECTED_MATERIAL = m_materialList[m_selectedMaterialIndex];
	m_selectedMatShape.setFillColor(materialToColor(SELECTED_MATERIAL));
	m_selectedMatText.setString(materialToString(SELECTED_MATERIAL));
}

void UI::cleanup() {
	// Force destruction before window closes
	m_selectedMatShape = sf::RectangleShape();
	m_selectedMatText = sf::Text();
	m_selectedMatFont = sf::Font();
	m_spawnerCheckBox = sf::RectangleShape();
}