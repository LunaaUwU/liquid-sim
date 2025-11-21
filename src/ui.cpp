#include "ui.h"

MaterialType UI::SELECTED_MATERIAL;

void UI::init(const sf::VideoMode& videoMode, Grid* grid)
{
	m_grid = grid;
	m_videoMode = videoMode;
	InputManager::onLeftClick([this]() -> bool {
		if (m_spawnerCheckBox.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
		{
			updateCheckBox();
			return true;
		}
		else if (m_clearButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
		{
			m_grid->clearBoard();
			return true;
		}
		else
			return false;
		});

	InputManager::onRightClick([this]() -> bool {
		if (m_spawnerCheckBox.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
		{
			return true;
		}
		else
			return false;
		});

	InputManager::onScroll([this](float delta) {
		if (delta < 0)
			changeSelectedMat(1);
		else
			changeSelectedMat(-1);
		return false;
		});

	m_uiFont.loadFromFile("../assets/fonts/ComicSans.ttf");

	m_selectedMatShape.setSize(sf::Vector2f(30.f, 30.f));
	m_selectedMatShape.setPosition(sf::Vector2f(20.f, m_videoMode.height - 50.f));
	m_selectedMatShape.setFillColor(materialToColor(MaterialType::Sand));

	m_selectedMatText.setFont(m_uiFont);
	m_selectedMatText.setCharacterSize(40);
	m_selectedMatText.setPosition(sf::Vector2f(60.f, m_videoMode.height - 60.f));
	m_selectedMatText.setFillColor(sf::Color(255, 255, 255));
	m_selectedMatText.setString("Sand");

	m_spawnerCheckBox.setSize(sf::Vector2f(30.f, 30.f));
	m_spawnerCheckBox.setPosition(sf::Vector2f(75.f + m_selectedMatText.getLocalBounds().width, m_videoMode.height - 50.f));
	m_spawnerCheckBox.setFillColor(sf::Color(255, 255, 255));
	m_spawnerCheckBox.setOutlineThickness(-2.f);
	m_spawnerCheckBox.setOutlineColor(sf::Color(0, 0, 0));

	m_clearButton.setSize(sf::Vector2f(30.f, 30.f));
	m_clearButton.setPosition(sf::Vector2f(m_videoMode.width - 50.f, m_videoMode.height - 50.f));
	m_clearButton.setFillColor(sf::Color(80, 80, 80));

	m_clearText.setFont(m_uiFont);
	m_clearText.setCharacterSize(40);
	m_clearText.setString("Clear");
	m_clearText.setPosition(sf::Vector2f(m_videoMode.width - 70.f - m_clearText.getGlobalBounds().width, m_videoMode.height - 60.f));
	m_clearText.setFillColor(sf::Color(255, 255, 255));
	
	int numMaterials = static_cast<int>(MaterialType::Count);
	for (int i = 0; i < numMaterials; i++)
	{
		MaterialType material = static_cast<MaterialType>(i);
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
	window.draw(m_clearButton);
	window.draw(m_clearText);
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
	m_spawnerCheckBox.setPosition(sf::Vector2f(75.f + m_selectedMatText.getLocalBounds().width, m_videoMode.height - 50.f));
}

void UI::updateCheckBox()
{
	if (m_isCheckBoxChecked)
	{
		m_isCheckBoxChecked = false;
		m_spawnerCheckBox.setFillColor(sf::Color(255, 255, 255));
		m_grid->setIsSpawner(false);
	}
	else
	{
		m_isCheckBoxChecked = true;
		m_spawnerCheckBox.setFillColor(sf::Color(0, 0, 0));
		m_grid->setIsSpawner(true);
	}
}