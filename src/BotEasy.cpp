#include "BotEasy.hpp"
#include "Game.hpp"
#include "WinScreen.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Motyw.hpp"


void boteasy(){
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

            if(event->is<sf::Event::Closed>()) {
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
                    if(tablica[i].getGlobalBounds().contains(klik)) 
                    {
                        if(ruch % 2 == 0 && mapa[i + 1] == 'n'){
                             
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
                            for(int j = 0; j < 9; j++){
                                if(mapa[j + 1] == 'n' && ruch % 2 == 1){
                                    sf::CircleShape circle(rectsize / 2 - 10);
                                    circle.setFillColor(dark.tlo);
                                    circle.setOutlineColor(dark.kolorO);
                                    circle.setOutlineThickness(dark.outlineThickness);
                                    std::vector<sf::Vector2f> av = {sf::Vector2f(tablica[j].getPosition().x + 7.5, tablica[j].getPosition().y + 7.5)};
                                    circle.setPosition(av[0]);
                                    kolko.push_back(circle);
                                    mapa[j+1] = 'o';
                                    ruch++;
                                    break;
                                }
                            }
                            
                        };
                    }
                    
                sprawdz();
                }
            }

            window.clear();
            for (auto& rect : tablica) 
            {
                window.draw(rect);
            }

            for (auto& linia : linie) 
            {
                window.draw(linia.data(), 2, sf::PrimitiveType::Lines);        
            }

            for(auto& kolo : kolko)
            {
                window.draw(kolo);
            }

            window.display();
    
        }   
    }
}