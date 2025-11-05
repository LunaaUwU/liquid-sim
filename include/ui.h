#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "material-type.h"
#include "input-manager.h"
#include "grid.h"

class UI
{
public:

	void init(sf::VideoMode& videoMode, Grid* grid);

	void update(sf::Int32 deltaMS);

	void render(sf::RenderWindow& window) const;

	void changeSelectedMat(int value);

	static MaterialType SELECTED_MATERIAL;
	

private:

	void updateCheckBox();

	Grid* m_grid;

	sf::VideoMode m_videoMode;

	int m_selectedMaterialIndex;
	std::vector<MaterialType> m_materialList;

	sf::Font m_uiFont;
	sf::RectangleShape m_selectedMatShape;
	sf::Text m_selectedMatText;
	sf::RectangleShape m_spawnerCheckBox;
	sf::RectangleShape m_clearButton;
	sf::Text m_clearText;
	sf::RectangleShape m_flipButton;
	sf::Text m_flipText;

	bool m_isCheckBoxChecked = false;
};