//
// Created by zoade on 29.10.2026.
//

#ifndef SFML_AND_VARIOUS_TEST_GAME_H
#define SFML_AND_VARIOUS_TEST_GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "character.h"

class Game {
public:


    void BeginWindow();

    void Loop();

private:
    void CheckEvents();

    //void CheckIfWindowClosed(const std::optional<sf::Event> &event);

    sf::RenderWindow window;

};


#endif // SFML_AND_VARIOUS_TEST_GAME_H
