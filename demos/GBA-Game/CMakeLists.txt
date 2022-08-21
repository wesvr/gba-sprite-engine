project(GBA-Game)

add_executable(${PROJECT_NAME}.elf
        src/builderPattern/CharacterDirector.cpp
        src/builderPattern/CharacterDirector.h

        src/recourses/backgrounds/playerSelectMenuBackground.h
        src/recourses/backgrounds/gameOverBackground.h
        src/recourses/backgrounds/miniGameBackground.h
        src/recourses/backgrounds/BoardMapBackground.h
        src/recourses/backgrounds/startBackground.h

        src/recourses/sounds/backgroundSound.h
        src/recourses/sounds/gameOverSound.h
        src/recourses/sounds/ShroomCitySound.h
        src/recourses/sounds/startScreenSound.h

        src/recourses/sprites/hand.h
        src/recourses/sprites/mario.h
        src/recourses/sprites/luigi.h
        src/recourses/sprites/peach.h
        src/recourses/sprites/yoshi.h
        src/recourses/sprites/start.h

        src/recourses/sprites/goombaTiles.h
        src/recourses/sprites/QuestionBlockTiles.h

        src/Scenes/PlayerSelectScene.h
        src/Scenes/PlayerSelectScene.cpp
        src/Scenes/GameOverScene.h
        src/Scenes/GameOverScene.cpp
        src/Scenes/MapScene.h
        src/Scenes/MapScene.cpp
        src/Scenes/StartScene.h
        src/Scenes/StartScene.cpp
        src/main.cpp

        src/recourses/sprites/sharedPal.h
        src/recourses/sprites/goombaTiles.h
        src/recourses/sprites/LuigiTiles.h

        src/recourses/backgrounds/miniGameBackground.h
        src/Scenes/Players/goomba.cpp
        src/Scenes/Players/goomba.h
        src/recourses/sprites/goombaTiles.h
        src/Scenes/MiniGameScene.cpp
        src/Scenes/MiniGameScene.h
        src/Scenes/Players/Luigi.cpp
        src/Scenes/Players/Luigi.h
        src/recourses/sprites/LuigiTiles.h
        src/Scenes/Players/QuestionBlock.cpp
        src/Scenes/Players/QuestionBlock.h
        src/recourses/sprites/QuestionBlockTiles.h
        src/recourses/sprites/sharedPal.h src/builderPattern/CharacterDirector.cpp src/builderPattern/CharacterDirector.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )