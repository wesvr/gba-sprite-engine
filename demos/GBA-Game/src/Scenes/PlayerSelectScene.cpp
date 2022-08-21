//
// Created by Wesley Vrancken on 21/08/2022.
//

#include "libgba-sprite-engine/sprites/sprite_builder.h"
#include "libgba-sprite-engine/gba/tonc_memdef.h"
#include "libgba-sprite-engine/gba_engine.h"
#include "libgba-sprite-engine/effects/fade_out_scene.h"
#include "libgba-sprite-engine/background/text_stream.h"

#include "PlayerSelectScene.h"
#include "../recourses/backgrounds/charSelectMenuBackground.h"
#include "../recourses/sounds/backgroundSound.h"
#include "StartScene.h"
#include "MapScene.h"
#include "../builderPattern/CharacterDirector.h"
#include <iostream>

PlayerSelectScene::PlayerSelectScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> PlayerSelectScene::backgrounds() {
    return {};
}

std::vector<Sprite *> PlayerSelectScene::sprites() {
    return {Sprite_Mario.get(), Sprite_Luigi.get(), Sprite_Peach.get(), Sprite_Yoshi.get(), Sprite_Hand.get()};
}

void PlayerSelectScene::load() {
    PlayerPosition = 0;

    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(charSelectSharedPal, sizeof(charSelectSharedPal)));

    buildPlayableCharacterSprites();

    SpriteBuilder<Sprite> builder;

    Sprite_Hand = builder
            .withData(handSelTiles, sizeof(handSelTiles))
            .withSize(SIZE_16_16)
            .withLocation(55, 40)
            .buildPtr();

    engine -> enqueueMusic(backgroundMusic, backgroundMusic_bytes, 45000);
}
void PlayerSelectScene::PlayerIsSelected(u16 keys){
    if ((Bool_PressingLeft && !(keys & KEY_LEFT)) || (Bool_PressingRight && !(keys & KEY_RIGHT))) {
        TextStream::instance().clear();
        TextStream::instance().setText("Confirm your choice",13,8);
        TextStream::instance().setFontColor(Text_setFontColor);

        if(BOOL_PlayerIsSelected) {
            TextStream::instance().setText(">NO", 15,10);
            TextStream::instance().setFontColor(Text_setFontColor);
            BOOL_PlayerIsSelected = false;
        }else{
            TextStream::instance().setText(">YES", 15,10);
            TextStream::instance().setFontColor(Text_setFontColor);
            BOOL_PlayerIsSelected = true;
        }

        Bool_PressingLeft = false;
        Bool_PressingRight = false;
    }

    if(Bool_PressingA && !(keys & KEY_A)){

        if(BOOL_PlayerIsSelected){
            if (PlayerPosition == 0) {
                charSelect = CharSelection::mario_char;
            } else if (PlayerPosition == 1) {
                charSelect = CharSelection::luigi_char;
            } else if (PlayerPosition == 2) {
                charSelect = CharSelection::peach_char;
            } else if (PlayerPosition == 3) {
                charSelect = CharSelection::yoshi_char;
            }

            //character selection meegeven aan de volgende scene
            auto mainGameScene = new MapScene(engine);
            mainGameScene->setCharacter(charSelect= static_cast<CharSelection>(PlayerPosition));
            mainGameScene->setCharacter(charSelect);
            engine->transitionIntoScene(mainGameScene, new FadeOutScene(5));
        } else {
            Bool_PlayerIsSelected = false;
            TextStream::instance().clear();
        }
        Bool_PressingA = false;
    }
}
void PlayerSelectScene::PlayerIsNotSelected(u16 keys){
    static int leftPressed = 0;
    static int rightPressed = 0;
    if (Bool_PressingLeft && !(keys & KEY_LEFT)) {
        leftPressed++;
        TextStream::instance().setText("left key" + std::to_string(((PlayerPosition - 1) % 4)), 0, 0);
        TextStream::instance().setFontColor(Text_setFontColor);
        PlayerPosition = ((PlayerPosition - 1) % 4);
        Bool_PressingLeft = false;
    }

    if (Bool_PressingRight && !(keys & KEY_RIGHT)) {
        rightPressed++;
        TextStream::instance().setText("right key" + std::to_string(rightPressed), 1, 0);
        TextStream::instance().setFontColor(Text_setFontColor);
        PlayerPosition = ((PlayerPosition + 1) % 4);
        Bool_PressingRight = false;
    }

    if ((keys & KEY_B) && !(engine->isTransitioning())){
        engine->transitionIntoScene(new StartScene(engine), new FadeOutScene(5));
    }

    if (Bool_PressingA && !(keys & KEY_A)){

        TextStream::instance().setText("Confirm your choice",13,8);
        TextStream::instance().setFontColor(Text_setFontColor);

        TextStream::instance().setText(">NO", 15,10);
        TextStream::instance().setFontColor(Text_setFontColor);

        Bool_PlayerIsSelected = true;
        BOOL_PlayerIsSelected = false;

        Bool_PressingA = false;
    }
}

void PlayerSelectScene::tick(u16 keys) {

    if (Bool_PlayerIsSelected) {
        PlayerIsSelected(keys);
    } else {
        PlayerIsNotSelected(keys);
    }

    //Triggering voor de knoppen
    if (keys & KEY_LEFT) {
        Bool_PressingLeft = true;
    } else if (keys & KEY_RIGHT) {
        Bool_PressingRight = true;
    } else if (keys & KEY_A) {
        Bool_PressingA = true;
    }

    //Positie van de Sprite_Hand
    if (PlayerPosition == 0) {
        Sprite_Hand->moveTo(55, 40);
    } else if (PlayerPosition == 1) {
        Sprite_Hand->moveTo(90, 40);
    } else if (PlayerPosition == 2) {
        Sprite_Hand->moveTo(125, 40);
    } else if (PlayerPosition == 3) {
        Sprite_Hand->moveTo(160, 40);
    }
}

void PlayerSelectScene::buildPlayableCharacterSprites() {
    SpriteBuilder<Sprite> builder;

    // Selection screens
    CharacterDirector director;
    director.buildMario(builder);
    Sprite_Mario = builder.buildPtr();

    director.buildLuigi(builder);
    Sprite_Luigi = builder.buildPtr();

    director.buildPeach(builder);
    Sprite_Peach = builder.buildPtr();

    director.buildYoshi(builder);
    Sprite_Yoshi = builder.buildPtr();
}