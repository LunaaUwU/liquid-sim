#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "material-type.h"
#include "input-manager.h"

class UI
{
public:

	void init(sf::VideoMode videoMode);

	void update(sf::Int32 deltaMS);

	void render(sf::RenderWindow& window) const;

	void cleanup();

	void changeSelectedMat(int value);

	static MaterialType SELECTED_MATERIAL;
	

private:
	int m_selectedMaterialIndex;
	std::vector<MaterialType> m_materialList;

	static sf::RectangleShape m_selectedMatShape;
	static sf::Text m_selectedMatText;
	static sf::Font m_selectedMatFont;
	static sf::RectangleShape m_spawnerCheckBox;
};