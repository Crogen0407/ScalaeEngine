add_library(Games STATIC
    Game.cpp 
)
target_link_libraries(Games PUBLIC Scalae::Engine)
