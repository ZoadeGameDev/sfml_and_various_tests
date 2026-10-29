add_executable(MovingCharacter main.cpp
        game.cpp
        game.h
        character.cpp
        character.h
)

target_link_libraries(MovingCharacter PUBLIC SFML::Graphics)