// src/Game.cpp
#include "Game.hpp"
#include "WinScreen.hpp"
#include "Menu.hpp"
#include "Motyw.hpp"



int ruch = 0;
char czykoniec = 'n';
std::map<int, char> mapa = {
    {1,'n'},{2,'n'},{3,'n'},
    {4,'n'},{5,'n'},{6,'n'},
    {7,'n'},{8,'n'},{9,'n'}
};

void resetPlanszy() {
    mapa = {
        {1,'n'},{2,'n'},{3,'n'},
        {4,'n'},{5,'n'},{6,'n'},
        {7,'n'},{8,'n'},{9,'n'}
    }; 
    czykoniec = 'n';
    ruch = 0;
}

void sprawdz() {
    int win[8][3] = {
        {1,2,3}, {4,5,6}, {7,8,9},
        {1,4,7}, {2,5,8}, {3,6,9},
        {1,5,9}, {3,5,7}
    };

    for (auto& line : win) {
        if (mapa[line[0]] == mapa[line[1]] && mapa[line[1]] == mapa[line[2]] && mapa[line[0]] != 'n') {
            czykoniec = mapa[line[0]];
            return;
        }
    }

    if (ruch == 9) {
        czykoniec = 'r';
    }
}

void rysujplansze() {
    resetPlanszy();
    ruch = 0;
    if(!theme){
        dark = getMotyw("../assets/themes/DarkTheme.json");
    }else{
        dark = getMotyw("../assets/themes/LightTheme.json");
    }
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Kolko i krzyzyk!");
        

        pozycje poz;
        const int size = 9;
        const int rectsize = 200;
        std::vector<sf::RectangleShape> tablica;
        std::vector<std::vector<sf::Vertex>> linie;
        std::vector<sf::CircleShape> kolko;


        for(int i = 0; i < 9; i++){

            sf::RectangleShape shape({rectsize, rectsize});
            shape.setFillColor(sf::Color(dark.tlo));
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
                            }else if(mapa[i + 1] == 'n' && ruch % 2 == 1){
                                mapa[i + 1] = 'o';
                                sf::CircleShape circle(rectsize / 2 - 10);
                                circle.setFillColor(dark.tlo);
                                circle.setOutlineColor(dark.kolorO);
                                circle.setOutlineThickness(dark.outlineThickness);
                                std::vector<sf::Vector2f> av = {sf::Vector2f(tablica[i].getPosition().x + 7.5, tablica[i].getPosition().y + 7.5)};
                                circle.setPosition(av[0]);
                                kolko.push_back(circle);
                                ruch++;
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
