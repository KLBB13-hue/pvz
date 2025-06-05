cmake_minimum_required(VERSION 3.16)

add_library(
  GameObject
  STATIC
  GameObject.cpp
        Background.cpp
        Plant.cpp
        Sunflower.cpp
        ShovelButton.cpp
        Sun.cpp
        SeedButton.cpp
        Peashooter.cpp
        Wallnut.cpp
        CherryBomb.cpp
        Repeater.cpp
        Pea.cpp
        Zombies.cpp
        Grid.cpp
        CooldownMask.cpp
)

target_link_libraries(
  GameObject
  Framework
)
