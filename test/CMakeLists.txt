enable_testing()

set(ControlSources
    ${CMAKE_SOURCE_DIR}/src/control/Game.cpp
    )

set(ModelSources
    ${CMAKE_SOURCE_DIR}/src/model/Spaceship.cpp
    ${CMAKE_SOURCE_DIR}/src/model/Aliens.cpp
    ${CMAKE_SOURCE_DIR}/src/model/Shoot.cpp
    )

set(ViewSources
    ${CMAKE_SOURCE_DIR}/src/view/Layer.cpp
    )

set(TestSources
    ${CMAKE_CURRENT_SOURCE_DIR}/GameTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SpaceshipTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AliensTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ShootTest.cpp
    )

add_executable(Test
    ${ModelSources}
    ${ControlSources}
    ${ViewSources}
    ${TestSources}
    )
