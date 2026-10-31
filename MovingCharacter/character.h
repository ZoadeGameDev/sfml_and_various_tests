//
// Created by zoade on 29.10.2026.
//

#ifndef SFML_AND_VARIOUS_TEST_CHARACTER_H
#define SFML_AND_VARIOUS_TEST_CHARACTER_H
#include <SFML/Graphics.hpp>
#include <print>
#include <cmath>

class Character {
public:
    // Setup Character
    Character();

    void Draw(sf::RenderWindow& window);

    void SetPosition(float x,float y);

    // Character Actions
    void Move(float deltaTime);

private:
    // Visuals
    void AnimateMove(float deltaTime);


    float wanted_size_;
    sf::Texture texture_;
    std::optional<sf::Sprite> sprite_;

    float anim_time_ = 0.0f;
    int pose_ = 0;
    int wanted_pose_ = pose_;

    float transition_time_x_ = 0.f;
    float transition_time_y_ = 0.f;
    float actual_x_ = 0;
    float actual_y_ = 0;

};


#endif // SFML_AND_VARIOUS_TEST_CHARACTER_H
