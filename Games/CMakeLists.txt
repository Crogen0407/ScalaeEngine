add_executable(Game WIN32
    Game.cpp
    ${SCALAE_ENTRY_SOURCE}      # Engine의 wWinMain을 Game exe에 직접 포함
    # Resources/Game.rc         # 리소스를 exe에 내장하려면 (아래 참고)
)
target_link_libraries(Game PRIVATE Scalae::Engine)