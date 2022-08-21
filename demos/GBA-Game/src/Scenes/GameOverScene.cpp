//
// Created by Wesley Vrancken on 21/08/2022.
//

#include "libgba-sprite-engine/sprites/sprite_builder.h"
#include "libgba-sprite-engine/gba/tonc_memdef.h"
#include "libgba-sprite-engine/gba_engine.h"
#include "libgba-sprite-engine/effects/fade_out_scene.h"
#include "libgba-sprite-engine/background/text_stream.h"

#include "GameOverScene.h"
#include "../recourses/backgrounds/gameOverBackground.h"

GameOverScene::GameOverScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> GameOverScene::backgrounds()
{
    return {background.get()};
}

std::vector<Sprite *> GameOverScene::sprites()
{
    return {};
}

void GameOverScene::load()
{
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(gameOverScreenPal, sizeof(gameOverScreenPal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());

    background = std::unique_ptr<Background>(new Background(1, gameOverScreenTiles, sizeof(gameOverScreenTiles), gameOverScreenMap, sizeof(gameOverScreenMap), 16, 1, MAPLAYOUT_32X32));
    background->scroll(5, 30);

    engine->enqueueSound(GameOverSound, GameOverSound_bytes, 45000);
}

void GameOverScene::tick(u16 keys)
{
    TextStream::instance().clear();
    TextStream::instance().setText("final PlayerScore: " + std::to_string(finalScore), 13, 7);
}

void GameOverScene::setFinalScore(int score)
{
    finalScore = score;
}

