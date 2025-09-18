#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <nlohmann/json.hpp>
struct Motyw {
    sf::Color tlo;
    sf::Color kolorX;
    sf::Color kolorO;
    sf::Color bColor;
    sf::Color outlineColor;
    sf::Color textcolor;
    std::string fontPath;
    std::string musicPath;
    std::string settingsimg;
    int outlineThickness;
};
sf::Color parseColorArray(const nlohmann::json& kolorJson);
Motyw getMotyw(const std::string& Path);
extern bool theme;
extern Motyw dark;