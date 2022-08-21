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
#include "../recourses/sprites/mario.h"
#include "../recourses/sprites/luigi.h"
#include "../recourses/sprites/peach.h"
#include "../recourses/sprites/yoshi.h"
#include "../recourses/sprites/hand.h"
#include "../recourses/sounds/backgroundSound.h"
#include "StartScene.h"
#include "MapScene.h"

// TODO: Conversion problem!
//#include "../BuildPlayer.h"

PlayerSelectScene::PlayerSelectScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> PlayerSelectScene::backgrounds() {
    //return {background.get()};
    return {};
}

std::vector<Sprite *> PlayerSelectScene::sprites() {
    return {Sprite_Mario.get(), Sprite_Luigi.get(), Sprite_Peach.get(), Sprite_Yoshi.get(), Sprite_Hand.get()};
}

void PlayerSelectScene::load() {
    PlayerPosition = 0;

    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());
    //backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(charSelectPal, sizeof(charSelectPal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(charSelectSharedPal, sizeof(charSelectSharedPal)));

    //background = std::unique_ptr<Background>(new Background(1, charSelectTiles, sizeof(charSelectTiles), charSelectMap, sizeof(charSelectMap), 16, 1, MAPLAYOUT_32X32));

    SpriteBuilder<Sprite> builder;

    // Selection screens

    //TODO:
    /*MarioBuilder *marioBuilder;
    Build(reinterpret_cast<BuildPlayer *>(marioBuilder));*/


    Sprite_Mario = builder
            .withData(marioSelTiles, sizeof(marioSelTiles))
            .withSize(SIZE_32_32)
            .withLocation(50, 60)
            .buildPtr();

    Sprite_Luigi = builder
            .withData(luigiSelTiles, sizeof(luigiSelTiles))
            .withSize(SIZE_32_32)
            .withLocation(85, 60)
            .buildPtr();

    Sprite_Peach = builder
            .withData(peachSelTiles, sizeof(peachSelTiles))
            .withSize(SIZE_32_32)
            .withLocation(120, 60)
            .buildPtr();

    Sprite_Yoshi = builder
            .withData(yoshiSelTiles, sizeof(yoshiSelTiles))
            .withSize(SIZE_32_32)
            .withLocation(155, 60)
            .buildPtr();

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
            if (PlayerPosition == 1) {
                charSelect = CharSelection::mario_char;
            } else if (PlayerPosition == 2) {
                charSelect = CharSelection::luigi_char;
            } else if (PlayerPosition == 3) {
                charSelect = CharSelection::peach_char;
            } else if (PlayerPosition == 4) {
                charSelect = CharSelection::yoshi_char;
            }

            //character selection meegeven aan de volgende scene
            auto mainGameScene = new MapScene(engine);
            //mainGameScene->setCharacter(charSelect= static_cast<CharSelection>(PlayerPosition));
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
    if (Bool_PressingLeft && !(keys & KEY_LEFT)) {
        PlayerPosition = ((PlayerPosition - 1) % 5) + 0.1;
        Bool_PressingLeft = false;
    }

    if (Bool_PressingRight && !(keys & KEY_RIGHT)) {
        PlayerPosition = ((PlayerPosition + 1) % 5) + 0.1;
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
    if (PlayerPosition == 1) {
        Sprite_Hand->moveTo(55, 40);
    } else if (PlayerPosition == 2) {
        Sprite_Hand->moveTo(90, 40);
    } else if (PlayerPosition == 3) {
        Sprite_Hand->moveTo(125, 40);
    } else if (PlayerPosition == 4) {
        Sprite_Hand->moveTo(160, 40);
    }
}
