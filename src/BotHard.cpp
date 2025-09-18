#include "BotHard.hpp"
#include "Game.hpp"
#include "WinScreen.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Motyw.hpp"


int ocenPlansze(std::map<int, char>& mapa) {
    const int wygrane[8][3] = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
        {1, 5, 9}, {3, 5, 7}
    };

    for (auto& linia : wygrane) {
        if (mapa[linia[0]] == mapa[linia[1]] &&
            mapa[linia[1]] == mapa[linia[2]]) {
            if (mapa[linia[0]] == 'o') return +10;
            if (mapa[linia[0]] == 'x') return -10;
        }
    }
    return 0;
}
int minimax(std::map<int, char>& mapa, bool isMax, int depth) {
    int score = ocenPlansze(mapa);
    if (score == 10 || score == -10) return score - depth;

    bool movesLeft = false;
    for (int i = 1; i <= 9; i++) {
        if (mapa[i] == 'n') {
            movesLeft = true;
            break;
        }
    }
    if (!movesLeft) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 1; i <= 9; i++) {
            if (mapa[i] == 'n') {
                mapa[i] = 'o';
                best = std::max(best, minimax(mapa, false, depth + 1));
                mapa[i] = 'n';
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 1; i <= 9; i++) {
            if (mapa[i] == 'n') {
                mapa[i] = 'x';
                best = std::min(best, minimax(mapa, true, depth + 1));
                mapa[i] = 'n';
            }
        }
        return best;
    }
}
int znajdzNajlepszyRuch(std::map<int, char>& mapa) {
    int bestVal = -1000;
    int bestMove = -1;

    for (int i = 1; i <= 9; i++) {
        if (mapa[i] == 'n') {
            mapa[i] = 'o';
            int moveVal = minimax(mapa, false, 0);
            mapa[i] = 'n';

            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

void bothard() {
    if(!theme){
        dark = getMotyw("../assets/themes/DarkTheme.json");
    }else{
        dark = getMotyw("../assets/themes/LightTheme.json");
    }
    resetPlanszy();
    czykoniec = 'n';
    ruch = 0;
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Kolko i krzyzyk!");

    pozycje poz;
    const int size = 9;
    const int rectsize = 200;
    std::vector<sf::RectangleShape> tablica;
    std::vector<std::vector<sf::Vertex>> linie;
    std::vector<sf::CircleShape> kolko;


    for(int i = 0; i < 9; i++){

        sf::RectangleShape shape({rectsize, rectsize});
        shape.setFillColor(dark.tlo);
        shape.setOutlineColor(dark.outlineColor);
        shape.setOutlineThickness(dark.outlineThickness);
        shape.setPosition({poz.x, poz.y});
        tablica.push_back(shape);

        poz.x += rectsize;
            
        if((i + 1) % 3 == 0){
            poz.x = 0;
            poz.y += rectsize;
        }
    }


    while (window.isOpen())
    {
        while (auto event = window.pollEvent()) 
        {
            if(czykoniec == 'x'){
                window.close();
                wygrana('x');
            }else if(czykoniec == 'o'){ 
                window.close();
                wygrana('o');
            }else if(czykoniec == 't'){
                window.close();
                wygrana('t');
            }

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if(ruch == 9){
                czykoniec = 't';
            }

            if (event->is<sf::Event::MouseButtonPressed>() && event->is<sf::Event::MouseButtonPressed>() == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
            {
                sf::Vector2f klik(static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.x), 
                static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.y));
                    
                for (int i = 0; i < 9; ++i) 
                {
                    if (tablica[i].getGlobalBounds().contains(klik)) 
                    {
                        if(ruch % 2 == 0 && mapa[i + 1] == 'n')
                        {
                            mapa[i + 1] = 'x';
                            std::vector<sf::Vertex> line = 
                            {
                                {sf::Vector2f(tablica[i].getPosition().x, tablica[i].getPosition().y), dark.kolorX},
                                {sf::Vector2f(tablica[i].getPosition().x + rectsize, tablica[i].getPosition().y + rectsize), dark.kolorX},
                                {sf::Vector2f(tablica[i].getPosition().x + rectsize, tablica[i].getPosition().y), dark.kolorX},
                                {sf::Vector2f(tablica[i].getPosition().x, tablica[i].getPosition().y + rectsize), dark.kolorX}
                            };

                            linie.push_back(std::vector{line[0], line[1]});
                            linie.push_back(std::vector{line[2], line[3]}); 
                            ruch++;
                            if (ruch % 2 == 1) {
                                int bestMove = znajdzNajlepszyRuch(mapa);

                                if (bestMove != -1) {
                                    sf::CircleShape circle(rectsize / 2 - 10);
                                    circle.setFillColor(dark.tlo);
                                    circle.setOutlineColor(dark.kolorO);
                                    circle.setOutlineThickness(dark.outlineThickness);
                                    circle.setPosition(tablica[bestMove - 1].getPosition() + sf::Vector2f(7.5, 7.5));
                                    kolko.push_back(circle);
                                    mapa[bestMove] = 'o';
                                    ruch++;
                                }
                            }
                                
                        }
                    };
                }
                    
            sprawdz();
            }
        }

        window.clear();
        for (auto& rect : tablica) {
            window.draw(rect);
        }

        for (auto& linia : linie) {
            window.draw(linia.data(), 2, sf::PrimitiveType::Lines);        
        }

        for(auto& kolo : kolko){
            window.draw(kolo);
        }

        window.display();
    }
}