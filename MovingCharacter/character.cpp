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
    float modifier = 10 * deltaTime;

    const float joystick_x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
    if (std::abs(joystick_x) > 20.f) {
        wanted_x = joystick_x * modifier;
        std::println("joystick_x = {}", joystick_x);
    }
    const float joystick_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);
    if (std::abs(joystick_y) > 20.f) {
        wanted_y = joystick_y * modifier;
    }

    // Keyboards controls
    float keyboard_speed_x = 950.f * deltaTime;
    float keyboard_speed_y = 950.f * deltaTime;

    // Horizontal Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
        transition_time_x_ += 0.5f;
        transition_time_x_ = std::clamp(transition_time_x_, 0.0f, 1.0f);
        wanted_x = keyboard_speed_x * transition_time_x_;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
        transition_time_x_ += 0.5f;
        transition_time_x_ = std::clamp(transition_time_x_, 0.0f, 1.0f);
        wanted_x = -keyboard_speed_x * transition_time_x_;
    }

    // Vertical Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
        transition_time_y_ += 0.5f;
        transition_time_y_ = std::clamp(transition_time_y_, 0.0f, 1.0f);
        wanted_y = -keyboard_speed_y * transition_time_y_;
    } else if  (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
        transition_time_y_ += 0.5f;
        transition_time_y_ = std::clamp(transition_time_y_, 0.0f, 1.0f);
        wanted_y = keyboard_speed_y * transition_time_y_;
    }

    // Apply the wanted movement
    sprite_->move({wanted_x,wanted_y});

    // Reset if stop moving
    if (wanted_x == 0 & wanted_y == 0) {
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