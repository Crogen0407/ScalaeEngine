add_library(Game STATIC
    Game.cpp 
)
target_link_libraries(Game PUBLIC Scalae::Engine)