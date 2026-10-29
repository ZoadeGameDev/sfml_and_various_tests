//
// Created by zoade on 29.10.2026.
//

#include "character.h"


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

void Character::Move(float deltaTime) {
    float wanted_x = 0;
    float wanted_y = 0;
    float modifier = 10 * deltaTime;

    const float joystick_x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
    if (std::abs(joystick_x) > 20.f) {
        wanted_x = joystick_x * modifier;
    }
    const float joystick_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);
    if (std::abs(joystick_y) > 20.f) {
        wanted_y = joystick_y * modifier;
    }
    sprite_->move({wanted_x,wanted_y});
}