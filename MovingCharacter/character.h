//
// Created by zoade on 29.10.2026.
//

#ifndef SMFL_AND_VARIOUS_TEST_CHARACTER_H
#define SMFL_AND_VARIOUS_TEST_CHARACTER_H
#include <SFML/Graphics.hpp>
#include <print>

class Character {
public:
    Character();

    void Draw(sf::RenderWindow& window);

    void SetPosition(float x,float y);

    void Move(float deltaTime);

private:
    float wanted_size_;
    sf::Texture texture_;
    std::optional<sf::Sprite> sprite_;


};


#endif // SMFL_AND_VARIOUS_TEST_CHARACTER_H
