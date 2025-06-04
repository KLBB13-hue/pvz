cmake_minimum_required(VERSION 3.16)

add_library(
  GameObject
  STATIC
  GameObject.cpp
        Background.cpp
        Plant.cpp
        Sunflower.cpp
        Grid.cpp
        ShovelButton.cpp
        Sun.cpp
        SeedButton.cpp
        Peashooter.cpp
        Wallnut.cpp
        CherryBomb.cpp
        Repeater.cpp
        Pea.cpp
        Zombies.cpp
)

target_link_libraries(
  GameObject
  Framework
)
