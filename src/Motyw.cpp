#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Motyw.hpp"

Motyw dark;
bool theme = true;
sf::Color parseColorArray(const nlohmann::json& kolorJson) {
    if (kolorJson.size() != 3) throw std::runtime_error("Nieprawidłowy rozmiar koloru");

    return sf::Color(
        kolorJson[0].get<int>(),
        kolorJson[1].get<int>(),
        kolorJson[2].get<int>()
    );
}
Motyw getMotyw(const std::string& Path){
    std::ifstream f(Path);
    nlohmann::json dane;
    f >> dane;

    Motyw motyw;
    motyw.tlo = parseColorArray(dane["backgroundColor"]);
    motyw.kolorX = parseColorArray(dane["xColor"]);
    motyw.kolorO = parseColorArray(dane["oColor"]);
    motyw.bColor = parseColorArray(dane["bColor"]);
    motyw.textcolor = parseColorArray(dane["fontcolor"]);
    motyw.outlineColor = parseColorArray(dane["outlineColor"]);
    motyw.fontPath = dane["font"].get<std::string>();
    motyw.musicPath = dane["sound"].get<std::string>();
    motyw.settingsimg = dane["settingsimg"].get<std::string>();
    motyw.outlineThickness = dane["outlineWidth"].get<int>();
    return motyw;
};
