#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <nlohmann/json.hpp>
#include <fstream>
struct pozycje {
    float x = 0;
    float y = 0;
};


extern int ruch;
extern char czykoniec;
extern std::map<int, char> mapa;
void sprawdz();
void rysujplansze();
void resetPlanszy();
