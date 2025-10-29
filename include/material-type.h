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