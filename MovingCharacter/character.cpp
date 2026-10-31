//
// Created by zoade on 29.10.2026.
//

#include "character.h"

// Setup Character
Character::Character() {
    if (!texture_.loadFromFile("../../Assets/PNG/Players/Tilemap/tilemap_packed.png")) {
        std::println("no texture");
    }
    else {
        std::println("texture was found");
    }
    sprite_ = sf::Sprite(texture_);
    if (!sprite_) {
        std::println("no sprite");
    } else {
        std::println("sprite was found");
    }
    wanted_size_ = 4.f;
    sprite_->setTextureRect(sf::IntRect({0,48}, {24, 24}));
    sprite_->setScale({wanted_size_, wanted_size_});
    sprite_->setOrigin({float(sprite_->getTextureRect().size.x / 2), float(sprite_->getTextureRect().size.y / 2)});
}

void Character::Draw(sf::RenderWindow& window) {
    window.draw(*sprite_);
}

void Character::SetPosition(float x,float y) {
    sprite_->setPosition({x, y});
}

// Character Actions
void Character::Move(float deltaTime) {
    float wanted_x = 0;
    float wanted_y = 0;

    // Controller controls
    float modifier = 10;
    bool using_joystick = false;

    const float joystick_x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
    if (std::abs(joystick_x) > 20.f) {
        using_joystick = true;
        wanted_x = joystick_x * modifier;
        std::println("joystick_x = {}", joystick_x);
    }
    const float joystick_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);
    if (std::abs(joystick_y) > 20.f) {
        using_joystick = true;
        wanted_y = joystick_y * modifier;
    }

    // Keyboards controls
    float keyboard_speed_x = 950.f;
    float keyboard_speed_y = 950.f;

    // Horizontal Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
        wanted_x = keyboard_speed_x;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
        wanted_x = -keyboard_speed_x;
    }
    // Vertical Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
        wanted_y = -keyboard_speed_y;
    } else if  (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
        wanted_y = keyboard_speed_y;
    }


    if (using_joystick) {
        //std::println("--- USING JOYSTICK ---");
        actual_x_ = wanted_x;
        actual_y_ = wanted_y;
    } else {
        //std::println("+++ USING KEYBOARD +++");
        // Make the movement the wanted movement via a smooth transition (Only for keyboard)
        float smoothness = 50 * deltaTime;
        actual_x_ += (wanted_x - actual_x_) * smoothness;
        actual_y_ += (wanted_y - actual_y_) * smoothness;

        // STOP it from sliding if we click right and left continuously
        if ((actual_x_ > 0.f && wanted_x < 0.f) || (actual_x_ < 0.f && wanted_x > 0.f)) {
            actual_x_ = 0.f;
        }
        if ((actual_y_ > 0.f && wanted_y < 0.f) || (actual_y_ < 0.f && wanted_y > 0.f)) {
            actual_y_ = 0.f;
        }
    }

    // Apply the movement
    sprite_->move({actual_x_ * deltaTime,actual_y_ * deltaTime});

    // Reset if stop moving
    if (wanted_x == 0 && wanted_y == 0) {
        actual_x_ = 0;
        actual_y_ = 0;
        sprite_->setTextureRect(sf::IntRect({0 * 24,48}, {24, 24}));
        transition_time_x_ = 0.f;
        transition_time_y_ = 0.f;
    } else {
        AnimateMove(deltaTime); // to change later, according to the physic library
    }
}

// Visuals
void Character::AnimateMove(float deltaTime) {
    constexpr float period = 0.15;
    anim_time_ += deltaTime;
    while (anim_time_ >= period) {
        anim_time_ -= period;
        wanted_pose_ = (wanted_pose_ + 1 ) % 2; // restrict it from 0 to 1, it correspond to states
                                                // we then need to multiply by the right x.
    }
    sprite_->setTextureRect(sf::IntRect({wanted_pose_ * 24,48}, {24, 24}));
}