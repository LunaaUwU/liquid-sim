#pragma once

enum class MaterialType {
    None,
    Sand,
    Water,
    Stone,
    Metal,
    Steam,
    Ground,
    Lava,
    Count // To make it possible to get the length of the enum
};

inline std::string materialToString(MaterialType type)
{
    switch (type)
    {
        case MaterialType::None:   return "None";
        case MaterialType::Sand:   return "Sand";
        case MaterialType::Water:  return "Water";
        case MaterialType::Stone:  return "Stone";
        case MaterialType::Metal:  return "Metal";
        case MaterialType::Steam:  return "Steam";
        case MaterialType::Ground: return "Ground";
        case MaterialType::Lava:   return "Lava";
        default:                   return "Unknown";
    }
}

inline sf::Color materialToColor(MaterialType type)
{
    switch (type)
    {
        case MaterialType::Sand:   return sf::Color(255, 255, 0);
        case MaterialType::Water:  return sf::Color(0, 0, 255);
        case MaterialType::Stone:  return sf::Color(115, 115, 115);
        case MaterialType::Metal:  return sf::Color(55, 55, 55);
        case MaterialType::Steam:  return sf::Color(215, 215, 215);
        case MaterialType::Ground: return sf::Color(73, 29, 0);
        case MaterialType::Lava:   return sf::Color(255, 88, 0);
        default:                   return sf::Color(0, 0, 0, 0);
    }
}