#include "WinScreen.hpp"
#include "Menu.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Motyw.hpp"



sf::Vector2f wielkosc = {200, 80};
sf::Vector2f pozycja = {100, 100};
        
void wygrana(char c){
    if(!theme){
        dark = getMotyw("../assets/themes/DarkTheme.json");
    }else{
        dark = getMotyw("../assets/themes/LightTheme.json");
    }
    if(c == 'x'){
        sf::RenderWindow nowy(sf::VideoMode({400, 200}), "Wygrywa krzyzyk!");
        sf::RectangleShape tlo({400, 200});
        tlo.setFillColor(dark.tlo);

        sf::Font font(dark.fontPath);
        sf::Text text(font, "Wygrywa krzyzyk!", 30);
        text.setFillColor(dark.textcolor);
        text.setPosition({90, 30});

        sf::RectangleShape playagain(wielkosc);
        playagain.setFillColor(dark.bColor);
        playagain.setOutlineColor(dark.outlineColor);
        playagain.setOutlineThickness(dark.outlineThickness);
        playagain.setPosition(pozycja);

        sf::Text playagainText(font, "Play Again", 30);
        playagainText.setFillColor(dark.textcolor);
        playagainText.setOutlineColor(sf::Color::Black);
        playagainText.setOutlineThickness(1);
        playagainText.setPosition({120, 120});
        
        while(nowy.isOpen()){
            
            while (auto event = nowy.pollEvent()) 
            {
                if (event->is<sf::Event::Closed>()) {
                    nowy.close();
                }
                if (event->is<sf::Event::MouseButtonPressed>() && event->is<sf::Event::MouseButtonPressed>() == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    sf::Vector2f klik((event->getIf<sf::Event::MouseButtonPressed>()->position.x), (event->getIf<sf::Event::MouseButtonPressed>()->position.y));   
                    if(pozycja.x < klik.x && klik.x < pozycja.x + wielkosc.x && pozycja.y < klik.y && klik.y < pozycja.y + wielkosc.y){
                        nowy.close();
                        wybierzplansze();
                    }
            
            }
                
            }
            nowy.clear();
            nowy.draw(tlo);
            nowy.draw(text);
            nowy.draw(playagain);
            nowy.draw(playagainText);
            nowy.display();
        }
    }else if(c == 'o'){
        sf::RenderWindow nowy(sf::VideoMode({400, 200}), "Wygrywa Kolko!");
        sf::RectangleShape tlo({400, 200});
        tlo.setFillColor(dark.tlo);
        sf::Font font(dark.fontPath);
        sf::Text text(font, "Wygrywa kolko!", 30);
        text.setFillColor(dark.textcolor);
        text.setPosition({90, 30});

        sf::RectangleShape playagain(wielkosc);
        playagain.setFillColor(dark.bColor);
        playagain.setOutlineColor(dark.outlineColor);
        playagain.setOutlineThickness(dark.outlineThickness);
        playagain.setPosition(pozycja);

        sf::Text playagainText(font, "Play Again", 30);
        playagainText.setFillColor(dark.textcolor);
        playagainText.setOutlineColor(sf::Color::Black);
        playagainText.setOutlineThickness(1);
        playagainText.setPosition({120, 120});

        while(nowy.isOpen()){
            while (auto event = nowy.pollEvent()) 
            {
                if (event->is<sf::Event::Closed>()) {
                    nowy.close();
                }
                if (event->is<sf::Event::MouseButtonPressed>() && event->is<sf::Event::MouseButtonPressed>() == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    sf::Vector2f klik((event->getIf<sf::Event::MouseButtonPressed>()->position.x), (event->getIf<sf::Event::MouseButtonPressed>()->position.y));   
                    if(playagain.getGlobalBounds().contains(klik)){
                        nowy.close();
                        wybierzplansze();
                    }
                }
            }
            nowy.clear();
            nowy.draw(tlo);
            nowy.draw(text);
            nowy.draw(playagain);
            nowy.draw(playagainText);
            nowy.display();
        }
    }else if(c == 't'){
        sf::RenderWindow nowy(sf::VideoMode({400, 200}), "REMIS!");
        sf::RectangleShape tlo({400, 200});
        tlo.setFillColor(dark.tlo);

        sf::Font font(dark.fontPath);
        sf::Text text(font, "Remis!", 30);
        text.setFillColor(dark.textcolor);
        text.setPosition({150, 30});
        
        sf::RectangleShape playagain(wielkosc);
        playagain.setFillColor(dark.bColor);
        playagain.setOutlineColor(dark.outlineColor);
        playagain.setOutlineThickness(dark.outlineThickness);
        playagain.setPosition(pozycja);

        sf::Text playagainText(font, "Play Again", 30);
        playagainText.setFillColor(dark.textcolor);
        playagainText.setOutlineColor(sf::Color::Black);
        playagainText.setOutlineThickness(1);
        playagainText.setPosition({120, 120});

        while(nowy.isOpen()){
            while (auto event = nowy.pollEvent()) 
            {
                if (event->is<sf::Event::Closed>()) {
                    nowy.close();
                }
                if (event->is<sf::Event::MouseButtonPressed>() && event->is<sf::Event::MouseButtonPressed>() == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    sf::Vector2f klik((event->getIf<sf::Event::MouseButtonPressed>()->position.x), (event->getIf<sf::Event::MouseButtonPressed>()->position.y));   
                    if(playagain.getGlobalBounds().contains(klik)){
                        nowy.close();
                        wybierzplansze();
                    }
                }
            }
            nowy.clear();
            nowy.draw(tlo);
            nowy.draw(text);
            nowy.draw(playagain);
            nowy.draw(playagainText);
            nowy.display();
        }
    }
                    
}