# Model
set(ModelSources
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Spaceship.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Aliens.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Shoot.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Powerup.cpp
    )

# Controller
set(ControlSources
    ${CMAKE_CURRENT_SOURCE_DIR}/control/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/SpaceshipControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/AlienControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/OverlayControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/Powerup.cpp
    )

# View
set(ViewSources
    ${CMAKE_CURRENT_SOURCE_DIR}/view/Layer.cpp
    )

# add src code to target
add_executable(SpaceInvaders
        ${ModelSources}
        ${ControlSources}
        ${ViewSources}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )