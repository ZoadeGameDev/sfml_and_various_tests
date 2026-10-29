//
// Created by zoade on 29.10.2026.
//

#include "game.h"

// public
Character character;

void Game::BeginWindow() {
    window.create(sf::VideoMode({900, 600}), "Moving Character", sf::Style::Default);
    window.setFramerateLimit(60);
    character.SetPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

void Game::Loop() {
    while (window.isOpen()) {
        CheckWindowEvents();

        character.Move();

        window.clear(sf::Color::Black);
        character.Draw(window);
        window.display();
    }
}


// private
// This method will grow
void Game::CheckWindowEvents() {
    while (const std::optional event = window.pollEvent()) {
        //CheckIfWindowClosed(event);
        // close window
        if (event -> is<sf::Event::Closed>()) {
            window.close();
        }
        // change window dimension
        if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            const sf::Vector2f taille(resized->size);
            window.setView(sf::View(sf::FloatRect({0.f, 0.f}, taille)));

        }

    }
}



