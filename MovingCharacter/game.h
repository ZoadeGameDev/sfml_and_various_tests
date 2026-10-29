//
// Created by zoade on 29.10.2026.
//

#ifndef SMFL_AND_VARIOUS_TEST_GAME_H
#define SMFL_AND_VARIOUS_TEST_GAME_H
#include <SFML/Graphics.hpp>
#include "character.h"

class Game {
public:


    void BeginWindow();

    void Loop();

private:
    void CheckWindowEvents();

    //void CheckIfWindowClosed(const std::optional<sf::Event> &event);

    sf::RenderWindow window;

};


#endif // SMFL_AND_VARIOUS_TEST_GAME_H
