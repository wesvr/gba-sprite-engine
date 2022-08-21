//
// Created by Wesley Vrancken on 21/08/2022.
//

#include "libgba-sprite-engine/sprites/sprite_builder.h"
#include "libgba-sprite-engine/gba/tonc_memdef.h"
#include "libgba-sprite-engine/gba_engine.h"
#include "libgba-sprite-engine/effects/fade_out_scene.h"

#include "StartScene.h"
#include "PlayerSelectScene.h"

#include "../recourses/backgrounds/startBackground.h"
#include "libgba-sprite-engine/background/text_stream.h"
#include "../recourses/sprites/sharedPal.h"
#include "../recourses/sprites/LuigiTiles.h"
#include "../recourses/sprites/goombaTiles.h"

StartScene::StartScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> StartScene::backgrounds() {
    return {};
}

std::vector<Sprite *> StartScene::sprites() {

    std::vector<Sprite*> sprites;
    sprites.push_back(Sprite_Luigi.get());
    sprites.push_back(Sprite_Goomba.get());

    return { sprites};
}

void StartScene::load() {

    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());
    //backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(startScreenPal, sizeof(startScreenPal)));// Blue background
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(spritesPal, sizeof(spritesPal)));// Animation Luigi and Goomba

    TextStream::instance().setText("PRESS START", 15, 9);

    SpriteBuilder<AffineSprite> builder;

    Sprite_Luigi = builder
            .withData(luigi_animationTiles, sizeof(luigi_animationTiles))
            .withSize(SIZE_16_32)
            .withLocation(GBA_SCREEN_WIDTH / 2, GBA_SCREEN_HEIGHT / 2)
            .withAnimated(5,10)
            .buildPtr();

    Sprite_Goomba = builder
            .withData(GoombaTiles, sizeof(GoombaTiles))
            .withSize(SIZE_16_16)
            .withLocation(GBA_SCREEN_WIDTH / 2 - 20, GBA_SCREEN_HEIGHT / 2 + 16)
            .withAnimated(3,5)
            .buildPtr();

    engine -> enqueueMusic(Music, Music_Bytes, 45000);
}

void StartScene::tick(u16 keys) {
    if(keys & KEY_START) {
        if(!engine -> isTransitioning()) {
            engine -> transitionIntoScene(new PlayerSelectScene(engine), new FadeOutScene(5));
        }
    }
}