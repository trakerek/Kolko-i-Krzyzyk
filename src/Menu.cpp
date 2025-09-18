
#include "Menu.hpp"
#include "Game.hpp"
#include "BotEasy.hpp"
#include "BotHard.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Motyw.hpp"

sf::Vector2f wielkosc1 = {200, 100};


void wybierztryb(){
    if(!theme){
        dark = getMotyw("../assets/themes/DarkTheme.json");
    }else{
        dark = getMotyw("../assets/themes/LightTheme.json");
    }
    
    sf::RenderWindow menu(sf::VideoMode({600, 600}), "Wybierz plansze!");
    sf::RectangleShape shape({600, 600});
    shape.setFillColor(dark.tlo);
    shape.setOutlineColor(dark.outlineColor);
    shape.setOutlineThickness(dark.outlineThickness);
    
    sf::Font font(dark.fontPath);
    sf::Text text(font, "Wybierz Tryb Gry!",30);
    text.setCharacterSize(36);
    text.setFillColor(dark.textcolor);
    text.setPosition({150, 50});

    sf::RectangleShape easy(wielkosc1);
    easy.setFillColor(dark.bColor);
    easy.setOutlineColor(dark.outlineColor);
    easy.setOutlineThickness(dark.outlineThickness);
    easy.setPosition({200, 150});

    sf::Text easyText(font, "Latwy", 30);
    easyText.setFillColor(dark.textcolor);
    easyText.setOutlineColor(sf::Color::Black);
    easyText.setOutlineThickness(1);
    easyText.setPosition({250, 180});

    sf::RectangleShape hard(wielkosc1);
    hard.setFillColor(dark.bColor);
    hard.setOutlineColor(dark.outlineColor);
    hard.setOutlineThickness(dark.outlineThickness);
    hard.setPosition({200, 350});

    sf::Text hardText(font, "Trudny", 30);
    hardText.setFillColor(dark.textcolor);
    hardText.setOutlineColor(sf::Color::Black);
    hardText.setOutlineThickness(1);
    hardText.setPosition({250, 380});

    sf::RectangleShape back({wielkosc1.x/2, wielkosc1.y/2});
    back.setFillColor(dark.bColor);
    back.setOutlineColor(dark.outlineColor);
    back.setOutlineThickness(dark.outlineThickness);
    back.setPosition({30, 500});

    sf::Text backtext(font, "Powrot", 30);
    backtext.setFillColor(dark.textcolor);
    backtext.setOutlineColor(sf::Color::Black);
    backtext.setOutlineThickness(1);
    backtext.setPosition({33, 508});

    while(menu.isOpen()){

        while (auto event = menu.pollEvent()) 
        {
            if (event->is<sf::Event::Closed>()) {
                menu.close();
            }
            if (event->is<sf::Event::MouseButtonPressed>() && event->is<sf::Event::MouseButtonPressed>() == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
                {
                    sf::Vector2f klik(static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.x), 
                    static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.y));

                    if(klik.x > 200 && klik.x < 400 && klik.y > 100 && klik.y < 200){
                        menu.close();
                        boteasy();
                    }
                }
            if (event->is<sf::Event::MouseButtonPressed>() && event->is<sf::Event::MouseButtonPressed>() == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
                {
                    sf::Vector2f klik(static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.x), 
                    static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.y));

                    if(klik.x > 200 && klik.x < 400 && klik.y > 300 && klik.y < 400){
                        menu.close();
                        bothard();

                    }
                    if(klik.x > 30 && klik.x < 130 && klik.y > 500 && klik.y < 550){
                        menu.close();
                        wybierzplansze();
                    }
                }
                
        }
    menu.clear();
    menu.draw(shape);
    menu.draw(text);
    menu.draw(easy);
    menu.draw(easyText);
    menu.draw(hard);
    menu.draw(hardText);
    menu.draw(back);
    menu.draw(backtext);
    menu.display();
    }
}
void wybierzplansze(){
    if(!theme){
        dark = getMotyw("../assets/themes/DarkTheme.json");
    }else{
        dark = getMotyw("../assets/themes/LightTheme.json");
    }
    sf::RenderWindow menu(sf::VideoMode({600, 600}), "Wybierz plansze!");
    sf::RectangleShape shape({600, 600});
    shape.setFillColor(dark.tlo);
    shape.setOutlineColor(dark.outlineColor);
    shape.setOutlineThickness(dark.outlineThickness);

    sf::Texture settings;
    if(!settings.loadFromFile(dark.settingsimg)) return;
    
    sf::RectangleShape set({50, 50});

    set.setOutlineColor(sf::Color::Black);
    set.setOutlineThickness(5);
    set.setPosition({500, 50});
    set.setTexture(&settings);


    sf::Font font(dark.fontPath);
    sf::Text text(font, "Wybierz Tryb Gry!",30);
    text.setCharacterSize(36);
    text.setFillColor(dark.textcolor);
    text.setPosition({150, 50});

    sf::RectangleShape ovo(wielkosc1);
    ovo.setFillColor(dark.bColor);
    ovo.setOutlineColor(dark.outlineColor);
    ovo.setOutlineThickness(dark.outlineThickness);
    ovo.setPosition({200, 150});

    sf::Text ovoText(font, "2 graczy", 30);
    ovoText.setFillColor(sf::Color(219, 112, 147));
    ovoText.setOutlineColor(sf::Color::Black);
    ovoText.setOutlineThickness(1);
    ovoText.setPosition({240, 180});

    sf::RectangleShape bot(wielkosc1);
    bot.setFillColor(dark.bColor);
    bot.setOutlineColor(dark.outlineColor);
    bot.setOutlineThickness(dark.outlineThickness);
    bot.setPosition({200, 350});

    sf::Text botText(font, "Bot", 30);
    botText.setFillColor(sf::Color(219, 112, 147));
    botText.setOutlineColor(sf::Color::Black);
    botText.setOutlineThickness(1);
    botText.setPosition({270, 380});




    while(menu.isOpen()){
        while (auto event = menu.pollEvent()) 
        {
            if (event->is<sf::Event::Closed>()) {
                menu.close();
            }
            if (event->is<sf::Event::MouseButtonPressed>() && event->is<sf::Event::MouseButtonPressed>() == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
                {
                    sf::Vector2f klik(static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.x), 
                    static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.y));

                    if(klik.x > 200 && klik.x < 400 && klik.y > 150 && klik.y < 250){
                        menu.close();
                        rysujplansze();
                    }
                }
            if (event->is<sf::Event::MouseButtonPressed>() && event->is<sf::Event::MouseButtonPressed>() == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
                {
                    sf::Vector2f klik(static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.x), 
                    static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.y));

                    if(klik.x > 200 && klik.x < 400 && klik.y > 350 && klik.y < 450){
                        menu.close();
                        wybierztryb();
                    }
                }
            if(event->is<sf::Event::MouseButtonPressed>() && event->is<sf::Event::MouseButtonPressed>() == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                sf::Vector2f klik(static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.x), 
                static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.y));
                if(klik.x > 500 && klik.x < 550 && klik.y > 50 && klik.y < 100){
                    menu.close();
                    theme = !theme;
                    wybierzplansze();
                }
            }

        }
        menu.clear();
        menu.draw(shape);
        menu.draw(text);
        menu.draw(ovo);
        menu.draw(ovoText);
        menu.draw(bot);
        menu.draw(botText);
        menu.draw(set);
        menu.display();
    }
};