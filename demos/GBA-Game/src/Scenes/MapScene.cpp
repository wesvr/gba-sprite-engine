//
// Created by Wesley Vrancken on 21/08/2022.
//

#include "libgba-sprite-engine/effects/fade_out_scene.h"
#include "libgba-sprite-engine/background/text_stream.h"
#include "libgba-sprite-engine/sprites/sprite_builder.h"
#include "libgba-sprite-engine/sprites/affine_sprite.h"
#include "libgba-sprite-engine/gba/tonc_memdef.h"
#include "libgba-sprite-engine/gba_engine.h"

#include "MapScene.h"
#include "GameOverScene.h"
#include "MiniGameScene.h"

#include "../recourses/backgrounds/BoardMapBackground.h"
#include "../recourses/sprites/mario.h"
#include "../recourses/sprites/luigi.h"


MapScene::MapScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> MapScene::backgrounds()
{
    return {background.get()};
}

std::vector<Sprite *> MapScene::sprites()
{
    return {PlayerSprite.get()};
}

void MapScene::load()
{

    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(shroomCityPal, sizeof(shroomCityPal)));
    background = std::unique_ptr<Background>(new Background(1, shroomCityTiles, sizeof(shroomCityTiles), shroomCityMap, sizeof(shroomCityMap), 16, 1, MAPLAYOUT_64X64));

    SpriteBuilder<AffineSprite> affineBuilder;

    if (character == PlayerSelectScene::mario_char)
    {
        foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(mario_sharedPal, sizeof(mario_sharedPal)));

        PlayerSprite = affineBuilder
                .withData(marioTiles, sizeof(marioTiles))
                .withSize(SIZE_32_64)
                .withLocation(72 + (PlayerPosX * 16), 225 + (PlayerPosY * 16))
                .buildPtr();
    }
    else if (character == PlayerSelectScene::luigi_char)
    {
        foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(luigi_sharedPal, sizeof(luigi_sharedPal)));

        PlayerSprite = affineBuilder
                .withData(luigiTiles, sizeof(luigiTiles))
                .withSize(SIZE_32_64)
                .withLocation(72 + (PlayerPosX * 16), 225 + (PlayerPosY * 16))
                .buildPtr();
    }
    else if (character == PlayerSelectScene::peach_char)
    {
        foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(luigi_sharedPal, sizeof(luigi_sharedPal)));

        PlayerSprite = affineBuilder
                .withData(luigiTiles, sizeof(luigiTiles))
                .withSize(SIZE_32_64)
                .withLocation(72 + (PlayerPosX * 16), 225 + (PlayerPosY * 16))
                .buildPtr();
    }
    else if (character == PlayerSelectScene::yoshi_char)
    {
        // Colors
        foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(luigi_sharedPal, sizeof(luigi_sharedPal)));

        //Shadow
        PlayerSprite = affineBuilder
                .withData(luigiTiles, sizeof(luigiTiles))
                .withSize(SIZE_32_64)
                .withLocation(72 + (PlayerPosX * 16), 225 + (PlayerPosY * 16))
                .buildPtr();
    }

    PlayerSprite->makeAnimated(0, 2, 10);
    engine->enqueueMusic(Music, Music_Bytes, 45000);
}

void MapScene::tick(u16 keys)
{

    TextStream::instance().setText("PlayerScore: " + std::to_string(PlayerScore), 1, 1);
    TextStream::instance().setText("PlayerLives: " + std::to_string(PlayerLives), 2, 1);
    TextStream::instance().setFontColor(Text_setFontColor);

    // check if the PlayerSprite is still alive
    if (PlayerLives <= 0)
    {
        if (!(engine->isTransitioning()))
        {
            auto gameOver = new GameOverScene(engine);
            gameOver->setFinalScore(PlayerScore);
            engine->transitionIntoScene(gameOver, new FadeOutScene(5));
        }
    }

    if ((Bool_PressingUp && !(keys & KEY_UP)))
    {
        PlayerSprite->makeAnimated(2, 4, 2);
        MovePlayerTo(up);
        Bool_idle = false;
        Bool_PressingUp = false;
    }
    else if (Bool_PressingDown && !(keys & KEY_DOWN))
    {
        PlayerSprite->makeAnimated(6, 4, 2);
        MovePlayerTo(down);
        Bool_idle = false;
        Bool_PressingDown = false;
    }
    else if (Bool_pressingRight && !(keys & KEY_RIGHT))
    {
        PlayerSprite->makeAnimated(10, 4, 2);
        MovePlayerTo(right);
        Bool_idle = false;
        Bool_pressingRight = false;
    }
    else if (Bool_pressingLeft && !(keys & KEY_LEFT))
    {
        PlayerSprite->makeAnimated(14, 4, 2);
        MovePlayerTo(left);
        Bool_idle = false;
        Bool_pressingLeft = false;
    }
    else if (Bool_PressingA && !(keys & KEY_A))
    {
        ChoiceMinigameInMap();
        Bool_PressingA = false;
    }
    else if (Bool_PressingB && !(keys & KEY_B))
    {
        Bool_PressingB = false;
    }
    else
    {
        if (!Bool_idle)
        {
            PlayerSprite->makeAnimated(8, 2, 15);
            Bool_idle = true;
        }
    }

    // check for keypresses
    if (keys & KEY_A)
    {
        Bool_PressingA = true;
    }
    else if (keys & KEY_B)
    {
        Bool_PressingB = true;
    }
    else if (keys & KEY_UP)
    {
        Bool_PressingUp = true;
    }
    else if (keys & KEY_DOWN)
    {
        Bool_PressingDown = true;
    }
    else if (keys & KEY_LEFT)
    {
        Bool_pressingLeft = true;
    }
    else if (keys & KEY_RIGHT)
    {
        Bool_pressingRight = true;
    }

    background->scroll(PlayerSprite->getX(), PlayerSprite->getY() - 80);
}

void MapScene::setCharacter(PlayerSelectScene::CharSelection character)
{
    this->character = character;
}

void MapScene::MovePlayerTo(Direction direction)
{
    if (direction == up)
    {
        if (PlayerPosY > 0)
        {
            if (featureMap[PlayerPosY - 1][PlayerPosX] != 0)
            {
                PlayerPosY = PlayerPosY - 1;
                PlayerSprite->moveTo(PlayerSprite->getX(), PlayerSprite->getY() - 16);
            }
        }
    }
    else if (direction == down)
    {
        if (PlayerPosY < 6)
        {
            if (featureMap[PlayerPosY + 1][PlayerPosX] != 0)
            {
                PlayerPosY = PlayerPosY + 1;
                PlayerSprite->moveTo(PlayerSprite->getX(), PlayerSprite->getY() + 16);
            }
        }
    }
    else if (direction == left)
    {
        if (PlayerPosX > 0)
        {
            if (featureMap[PlayerPosY][PlayerPosX - 1] != 0)
            {
                PlayerPosX = PlayerPosX - 1;
                PlayerSprite->moveTo(PlayerSprite->getX() - 16, PlayerSprite->getY());
            }
        }
    }
    else if (direction == right)
    {
        if (PlayerPosX < 8)
        {
            if (featureMap[PlayerPosY][PlayerPosX + 1] != 0)
            {
                PlayerPosX = PlayerPosX + 1;
                PlayerSprite->moveTo(PlayerSprite->getX() + 16, PlayerSprite->getY());
            }
        }
    }
}

void MapScene::ChoiceMinigameInMap()
{

    if (featureMap[PlayerPosY][PlayerPosX] == 3)
    {
        if (!engine->isTransitioning())
        {
            auto miniGameScene = new MiniGameScene(engine);
            //miniGameScene->setCharacter(character);
            miniGameScene->setData(PlayerLives, PlayerScore, PlayerPosX, PlayerPosY);
            engine->transitionIntoScene(new MiniGameScene(engine), new FadeOutScene(5));
        }
    }
}

void MapScene::SetPlayerData(int Player_Lives, int Player_Score, int Player_PosX, int Player_PosY)
{
    this->PlayerLives = Player_Lives;
    this->PlayerScore = Player_Score;
    this->PlayerPosX = Player_PosX;
    this->PlayerPosY = Player_PosY;
}

