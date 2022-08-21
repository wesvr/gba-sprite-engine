project(foodthrowing)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/food_scene.cpp
        src/food_scene.h
        src/avatar.h src/bullet_data.h src/bullet.cpp src/bullet.h ../GBA-Game/src/main.cpp ../GBA-Game/src/Scenes/StartScene.cpp ../GBA-Game/src/Scenes/StartScene.h ../GBA-Game/src/Scenes/PlayerSelectScene.cpp ../GBA-Game/src/Scenes/PlayerSelectScene.h ../GBA-Game/src/Scenes/MiniGameScene.cpp ../GBA-Game/src/Scenes/MiniGameScene.h ../GBA-Game/src/Scenes/MapScene.cpp ../GBA-Game/src/Scenes/MapScene.h ../GBA-Game/src/Scenes/GameOverScene.cpp ../GBA-Game/src/Scenes/GameOverScene.h ../GBA-Game/src/Scenes/Players/QuestionBlock.cpp ../GBA-Game/src/Scenes/Players/QuestionBlock.h ../GBA-Game/src/Scenes/Players/Luigi.cpp ../GBA-Game/src/Scenes/Players/Luigi.h ../GBA-Game/src/Scenes/Players/goomba.cpp ../GBA-Game/src/Scenes/Players/goomba.h ../GBA-Game/src/recourses/sprites/yoshi.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
