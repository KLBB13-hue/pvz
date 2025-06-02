cmake_minimum_required(VERSION 3.16)

add_library(
  GameObject
  STATIC
  GameObject.cpp
        Background.cpp
        Plant.cpp
        Sunflower.cpp
        Grid.cpp
)

target_link_libraries(
  GameObject
  Framework
)
