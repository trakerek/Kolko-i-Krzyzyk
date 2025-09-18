#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
struct pozycje
{
    float x = 0;
    float y = 0;
};

int ruch = 0;
char czykoniec = 'n';
map <int,char> mapa = 
    {
        {1,'n'},{2,'n'},{3,'n'},
        {4,'n'},{5,'n'},{6,'n'},
        {7,'n'},{8,'n'},{9,'n'}
    };
void sprawdz(){
    if(mapa[1] == 'x' && mapa[2] == 'x' && mapa[3] == 'x' ||
    mapa[4] == 'x' && mapa[5] == 'x' && mapa[6] == 'x' ||
    mapa[7] == 'x' && mapa[8] == 'x' && mapa[9] == 'x' ||
    mapa[1] == 'x' && mapa[4] == 'x' && mapa[7] == 'x' ||
    mapa[2] == 'x' && mapa[5] == 'x' && mapa[8] == 'x' ||
    mapa[3] == 'x' && mapa[6] == 'x' && mapa[9] == 'x' ||
    mapa[1] == 'x' && mapa[5] == 'x' && mapa[9] == 'x' ||
    mapa[3] == 'x' && mapa[5] == 'x' && mapa[7] == 'x'
    ){
        czykoniec = 'x';
    }else if(mapa[1] == 'o' && mapa[2] == 'o' && mapa[3] == 'o' ||
    mapa[4] == 'o' && mapa[5] == 'o' && mapa[6] == 'o' ||
    mapa[7] == 'o' && mapa[8] == 'o' && mapa[9] == 'o' ||
    mapa[1] == 'o' && mapa[4] == 'o' && mapa[7] == 'o' ||
    mapa[2] == 'o' && mapa[5] == 'o' && mapa[8] == 'o' ||
    mapa[3] == 'o' && mapa[6] == 'o' && mapa[9] == 'o' ||
    mapa[1] == 'o' && mapa[5] == 'o' && mapa[9] == 'o' ||
    mapa[3] == 'o' && mapa[5] == 'o' && mapa[7] == 'o'
    ){
        czykoniec = 'o';
    }else if(ruch == 9){
        czykoniec = 't';
    }

}

void boteasy(){
    mapa = {
    {1,'n'},{2,'n'},{3,'n'},
    {4,'n'},{5,'n'},{6,'n'},
    {7,'n'},{8,'n'},{9,'n'}
};
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
            shape.setFillColor(sf::Color::Blue);
            shape.setOutlineColor(sf::Color::Red);
            shape.setOutlineThickness(5);
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
                    wygrana('x');
                    window.close();
                }else if(czykoniec == 'o'){
                    
                    wygrana('o');
                    window.close();
                }else if(czykoniec == 't'){
                    wygrana('t');
                    window.close();
                }
                if (event->is<sf::Event::Closed>()) {
                    window.close();
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
                                    {sf::Vector2f(tablica[i].getPosition().x, tablica[i].getPosition().y), sf::Color::Red},
                                    {sf::Vector2f(tablica[i].getPosition().x + rectsize, tablica[i].getPosition().y + rectsize), sf::Color::Red},
                                    {sf::Vector2f(tablica[i].getPosition().x + rectsize, tablica[i].getPosition().y), sf::Color::Red},
                                    {sf::Vector2f(tablica[i].getPosition().x, tablica[i].getPosition().y + rectsize), sf::Color::Red}
                                    
                                };

                                linie.push_back(std::vector{line[0], line[1]});
                                linie.push_back(std::vector{line[2], line[3]}); 
                                ruch++;
                                for(int j = 0; j < 9; j++){
                                    if(mapa[j + 1] == 'n' && ruch % 2 == 1){
                                        sf::CircleShape circle(rectsize / 2 - 10);
                                        circle.setFillColor(sf::Color::Blue);
                                circle.setOutlineColor(sf::Color::Red);
                                circle.setOutlineThickness(5);
                                std::vector<sf::Vector2f> av = {sf::Vector2f(tablica[j].getPosition().x + 7.5, tablica[j].getPosition().y + 7.5)};
                                circle.setPosition(av[0]);
                                kolko.push_back(circle);
                                mapa[j+1] = 'o';
                                ruch++;
                                break;
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

void wybierztryb(){
    sf::RenderWindow menu(sf::VideoMode({600, 600}), "Wybierz plansze!");
    sf::RectangleShape shape({600, 600});
    shape.setFillColor(sf::Color(216, 191, 216));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(5);
    
    sf::Font font("assets/arial.ttf");
    sf::Text text(font, "Wybierz Tryb Gry!",30);
    text.setCharacterSize(36);
    text.setFillColor(sf::Color::White);
    text.setPosition({150, 10});

    sf::RectangleShape easy({200, 100});
    easy.setFillColor(sf::Color::White);
    easy.setOutlineColor(sf::Color::Black);
    easy.setOutlineThickness(5);
    easy.setPosition({200, 100});

    sf::Text easyText(font, "Latwy", 30);
    easyText.setFillColor(sf::Color(219, 112, 147));
    easyText.setOutlineColor(sf::Color::Black);
    easyText.setOutlineThickness(1);
    easyText.setPosition({260, 130});

    sf::RectangleShape hard({200, 100});
    hard.setFillColor(sf::Color::White);
    hard.setOutlineColor(sf::Color::Black);
    hard.setOutlineThickness(5);
    hard.setPosition({200, 300});

    sf::Text hardText(font, "Trudny", 30);
    hardText.setFillColor(sf::Color(219, 112, 147));
    hardText.setOutlineColor(sf::Color::Black);
    hardText.setOutlineThickness(1);
    hardText.setPosition({260, 330});

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
                        boteasy();
                        menu.close();
                    }
                }
            if (event->is<sf::Event::MouseButtonPressed>() && event->is<sf::Event::MouseButtonPressed>() == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
                {
                    sf::Vector2f klik(static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.x), 
                    static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.y));

                    if(klik.x > 200 && klik.x < 400 && klik.y > 300 && klik.y < 400){
                        cout<<"trudny";
                        menu.close();
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
    menu.display();
    }
}



void wybierzplansze(){
    sf::RenderWindow menu(sf::VideoMode({600, 600}), "Wybierz plansze!");
    sf::RectangleShape shape({600, 600});
    shape.setFillColor(sf::Color(216, 191, 216));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(5);
    
    sf::Font font("assets/arial.ttf");
    sf::Text text(font, "Wybierz Tryb Gry!",30);
    text.setCharacterSize(36);
    text.setFillColor(sf::Color::White);
    text.setPosition({150, 10});

    sf::RectangleShape ovo({200, 100});
    ovo.setFillColor(sf::Color::White);
    ovo.setOutlineColor(sf::Color::Black);
    ovo.setOutlineThickness(5);
    ovo.setPosition({200, 100});

    sf::Text ovoText(font, "2 graczy", 30);
    ovoText.setFillColor(sf::Color(219, 112, 147));
    ovoText.setOutlineColor(sf::Color::Black);
    ovoText.setOutlineThickness(1);
    ovoText.setPosition({240, 130});

    sf::RectangleShape bot({200, 100});
    bot.setFillColor(sf::Color::White);
    bot.setOutlineColor(sf::Color::Black);
    bot.setOutlineThickness(5);
    bot.setPosition({200, 300});

    sf::Text botText(font, "Bot", 30);
    botText.setFillColor(sf::Color(219, 112, 147));
    botText.setOutlineColor(sf::Color::Black);
    botText.setOutlineThickness(1);
    botText.setPosition({270, 330});




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
                        rysujplansze();
                    }
                }
            if (event->is<sf::Event::MouseButtonPressed>() && event->is<sf::Event::MouseButtonPressed>() == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
                {
                    sf::Vector2f klik(static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.x), 
                    static_cast<float>(event->getIf<sf::Event::MouseButtonPressed>()->position.y));

                    if(klik.x > 200 && klik.x < 400 && klik.y > 300 && klik.y < 400){
                        menu.close();
                        wybierztryb();
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
        menu.display();
    }
};
void wygrana(char c){
    if(c == 'x'){
        sf::RenderWindow nowy(sf::VideoMode({400, 200}), "Wygrywa krzyzyk!");
        sf::RectangleShape tlo({400, 200});
        tlo.setFillColor(sf::Color(219, 112, 147));
        sf::Font font("assets/arial.ttf");
        sf::Text text(font, "Wygrywa krzyzyk!", 30);
        text.setFillColor(sf::Color::White);
        text.setPosition({50, 50});

        sf::RectangleShape playagain({100, 50});
        playagain.setFillColor(sf::Color::White);
        playagain.setOutlineColor(sf::Color::Black);
        playagain.setOutlineThickness(5);
        playagain.setPosition({150, 100});

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
            nowy.display();
        }
    }else if(c == 'o'){
        sf::RenderWindow nowy(sf::VideoMode({400, 200}), "Wygrywa Kolko!");
        sf::RectangleShape tlo({400, 200});
        tlo.setFillColor(sf::Color(219, 112, 147));
        sf::Font font("assets/arial.ttf");
        sf::Text text(font, "Wygrywa kolko!", 30);
        text.setFillColor(sf::Color::White);
        text.setPosition({50, 50});

        sf::RectangleShape playagain({100, 50});
        playagain.setFillColor(sf::Color::White);
        playagain.setOutlineColor(sf::Color::Black);
        playagain.setOutlineThickness(5);
        playagain.setPosition({150, 100});

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
            nowy.display();
        }
    }else if(c == 't'){
        sf::RenderWindow nowy(sf::VideoMode({400, 200}), "REMIS!");
        sf::RectangleShape tlo({400, 200});
        tlo.setFillColor(sf::Color(219, 112, 147));
        sf::Font font("assets/arial.ttf");
        sf::Text text(font, "Remis!", 30);
        text.setFillColor(sf::Color::White);
        text.setPosition({50, 50});
        
        sf::RectangleShape playagain({100, 50});
        playagain.setFillColor(sf::Color::White);
        playagain.setOutlineColor(sf::Color::Black);
        playagain.setOutlineThickness(5);
        playagain.setPosition({150, 100});

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
            nowy.display();
        }
    }
                    
}
void rysujplansze(){
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Kolko i krzyzyk!");
        

        pozycje poz;
        const int size = 9;
        const int rectsize = 200;
        std::vector<sf::RectangleShape> tablica;
        std::vector<std::vector<sf::Vertex>> linie;
        std::vector<sf::CircleShape> kolko;


        for(int i = 0; i < 9; i++){

            sf::RectangleShape shape({rectsize, rectsize});
            shape.setFillColor(sf::Color::Blue);
            shape.setOutlineColor(sf::Color::Red);
            shape.setOutlineThickness(5);
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
                    wygrana('x');
                    window.close();
                }else if(czykoniec == 'o'){
                    
                    wygrana('o');
                    window.close();
                }else if(czykoniec == 't'){
                    wygrana('t');
                    window.close();
                }
                if (event->is<sf::Event::Closed>()) {
                    window.close();
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
                                    {sf::Vector2f(tablica[i].getPosition().x, tablica[i].getPosition().y), sf::Color::Red},
                                    {sf::Vector2f(tablica[i].getPosition().x + rectsize, tablica[i].getPosition().y + rectsize), sf::Color::Red},
                                    {sf::Vector2f(tablica[i].getPosition().x + rectsize, tablica[i].getPosition().y), sf::Color::Red},
                                    {sf::Vector2f(tablica[i].getPosition().x, tablica[i].getPosition().y + rectsize), sf::Color::Red}
                                    
                                };

                                linie.push_back(std::vector{line[0], line[1]});
                                linie.push_back(std::vector{line[2], line[3]}); 
                                ruch++;
                            }else if(mapa[i + 1] == 'n' && ruch % 2 == 1){
                                mapa[i + 1] = 'o';
                                sf::CircleShape circle(rectsize / 2 - 10);
                                circle.setFillColor(sf::Color::Blue);
                                circle.setOutlineColor(sf::Color::Red);
                                circle.setOutlineThickness(5);
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
        
    
};
int main()
{
    // sf::Music music;
    // if(!music.openFromFile("sound.mp3")){
    //     return -1;
    // }
    
    // music.setVolume(50);
    // music.play();

    wybierzplansze();
    return 0;
}