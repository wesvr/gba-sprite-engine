//
// Created by Wesley Vrancken on 21/08/2022.
//

#include "libgba-sprite-engine/sprites/sprite_builder.h"
#include "libgba-sprite-engine/sprites/affine_sprite.h"
#include "libgba-sprite-engine/background/text_stream.h"
#include "libgba-sprite-engine/effects/fade_out_scene.h"
#include "MapScene.h"
#include "MiniGameScene.h"
#include "Players/goomba.h"
#include "Players/QuestionBlock.h"
#include "../recourses/backgrounds/miniGameBackground.h"
#include "../recourses/sprites/LuigiTiles.h"
#include "../recourses/sprites/sharedPal.h"
#include "../recourses/sprites/goombaTiles.h"
#include "../recourses/sprites/QuestionBlockTiles.h"
#include "../recourses/sounds/backgroundSound.h"
#include "../recourses/sounds/gameOverSound.h"
#include "../recourses/sounds/WinnerSound.h"


#define bottomHeightFor32 45
#define bottomHeightFor16 29

std::vector<Background *> MiniGameScene::backgrounds() {
    return {bg.get()};
}

void MiniGameScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager> (new ForegroundPaletteManager(spritesPal, sizeof(spritesPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));

    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);

    SpriteBuilder<AffineSprite> affineBuilder;

    luigiSprite = affineBuilder
            .withData(luigi_animationTiles, sizeof(luigi_animationTiles))
            .withSize(SIZE_16_32)
            .withLocation(GBA_SCREEN_WIDTH/2-8, GBA_SCREEN_HEIGHT-bottomHeightFor32)
            .withAnimated(5,5)
            .buildPtr();

    luigi = std::unique_ptr<Luigi>{new Luigi(std::move(luigiSprite))};
    luigi->getLuigiSprite()->stopAnimating();
    luigi->setCurrentLvl(1);
    goombaSprite = affineBuilder
            .withData(GoombaTiles, sizeof(GoombaTiles))
            .withSize(SIZE_16_16)
            .withLocation(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT-bottomHeightFor16)
            .withAnimated(3,5)
            .buildPtr();

    goomba = std::unique_ptr<Goomba>{new Goomba(std::move(goombaSprite))};

    questionBlockSprite = affineBuilder
            .withData(question_blockTiles, sizeof(question_blockTiles))
            .withSize(SIZE_16_16)
            .withLocation(GBA_SCREEN_WIDTH/2+10,GBA_SCREEN_HEIGHT-bottomHeightFor32-30)
            .withAnimated(0,1)
            .buildPtr();

    questionBlock = std::unique_ptr<QuestionBlock>{new QuestionBlock(std::move(questionBlockSprite))};

    engine->enqueueMusic(backgroundMusic, sizeof(backgroundMusic), 45000);
}

std::vector<Sprite *> MiniGameScene::sprites() {

    std::vector<Sprite*> sprites;
    sprites.push_back(luigi->getLuigiSprite().get());
    sprites.push_back(questionBlock->getQuestionBlockSprite().get());
    if(!goomba->isDead())sprites.push_back(goomba->getGoombaSprite().get());

    return sprites;
}

void MiniGameScene::addPoint() {
    Player_Score++;
    if(Player_Score %5 == 0) {
        Player_Lives++;
    }
    PlayerWon();

}

void MiniGameScene::tick(u16 keys) {
    if (Bool_Dead && (keys & KEY_A))
    {
        if (!engine->isTransitioning())
        {
            auto mainGameScene = new MapScene(engine);
            //mainGameScene->setCharacter(character);
            mainGameScene->SetPlayerData(Player_Lives - 1, PlayerSavedScore + Player_Score, PlayerSavedPosX, PlayerSavedPosY);
            engine->transitionIntoScene(mainGameScene, new FadeOutScene(5));
        }
    }
    else if (Bool_Won && (keys & KEY_A))
    {
        if (!engine->isTransitioning())
        {
            auto mainGameScene = new MapScene(engine);
            //mainGameScene->setCharacter(character);
            mainGameScene->SetPlayerData(Player_Lives, PlayerSavedScore + Player_Score, PlayerSavedPosX, PlayerSavedPosY);
            engine->transitionIntoScene(mainGameScene, new FadeOutScene(5));
        }
    }
    if(!luigi->isDead() ){
        TextStream::instance().setText("Points: " + std::to_string(Player_Score) + " Lives: " + std::to_string(Player_Lives) , 0,0);


        goomba->tick(keys);
        questionBlock->tick(keys);
        luigi->tick(keys);

        if((keys & KEY_RIGHT) && !stopScrollBg){
            scrollX +=1;
            bg->scroll(scrollX,scrollY);
        }

        //collision detection between Luigi and goomba
        if((luigi->getLuigiSprite()->collidesWith(*goomba->getGoombaSprite()) && (luigi->getLuigiSprite()->getY() == GBA_SCREEN_HEIGHT-bottomHeightFor32) && !goomba->isDead())){

            Player_Lives--;
            if(Player_Lives == 0){
                goomba->getGoombaSprite()->stopAnimating();
                goomba->getGoombaSprite()->setVelocity(0,0);
                luigi->kill();
                luigi->getLuigiSprite()->stopAnimating();
                luigi->getLuigiSprite()->animateToFrame(0);
            }
            else{
                goomba->getGoombaSprite()->moveTo(goomba->getGoombaSprite()->getX()+50, goomba->getGoombaSprite()->getY());
            }
        }


        if(luigi->getLuigiSprite()->collidesWith(*goomba->getGoombaSprite()) && luigi->getLuigiSprite()->getVelocity().y > 0 && luigi->getLuigiSprite()->getY()+32 >= GBA_SCREEN_HEIGHT-bottomHeightFor16-14){
            goomba->getGoombaSprite()->stopAnimating();
            goomba->getGoombaSprite()->moveTo(0,0);
            goomba->kill();
            luigi->getLuigiSprite()->setVelocity(0,-1);

        }

        //collision detection between Luigi and question block
        //vanonder er tegen
        if(luigi->getLuigiSprite()->collidesWith(*questionBlock->getQuestionBlockSprite()) && (luigi->getLuigiSprite()->getVelocity().y < 0) && luigi->getLuigiSprite()->getY() > questionBlock->getQuestionBlockSprite()->getY()+10){
            luigi->getLuigiSprite()->setVelocity(0,1);
            questionBlock->getQuestionBlockSprite()->animateToFrame(2);
            if(!questionBlock->isTriggerd()){
                addPoint();
                questionBlock->trigger();
            }
        }

        //er tegen langs zijkanten
        if(luigi->getLuigiSprite()->getX()+10 <= questionBlock->getQuestionBlockSprite()->getX() && luigi->getLuigiSprite()->collidesWith(*questionBlock->getQuestionBlockSprite())){
            questionBlock->getQuestionBlockSprite()->setVelocity(0,0);
            luigi->getLuigiSprite()->setVelocity(0,1);
            stopScrollBg = true;
        } else stopScrollBg = false;

        //erop
        if(luigi->getLuigiSprite()->collidesWith(*questionBlock->getQuestionBlockSprite()) && luigi->getLuigiSprite()->getY() < (questionBlock->getQuestionBlockSprite()->getY()-30)
           && luigi->getLuigiSprite()->getX()+8 > questionBlock->getQuestionBlockSprite()->getX()){
            luigi->getLuigiSprite()->setVelocity(0,0);
        }
    }
    else{
        PlayerDied();
    }
}

void MiniGameScene::PlayerDied()
{
    PlayerSavedScore = PlayerSavedScore + Player_Score;
    engine.get()->enqueueSound(GameOverSound, GameOverSound_bytes, 45000);
    TextStream::instance().clear();
    TextStream::instance().setText("You Died!", 10, 11);
    TextStream::instance().setText("Press X to return", 11, 7);
    TextStream::instance().setFontColor(Text_setFontColor);
    questionBlock->getQuestionBlockSprite()->setVelocity(0,0);
    Bool_Dead = true;
}

void MiniGameScene::PlayerWon()
{
    if(Player_Score == 3) {
        PlayerSavedScore = PlayerSavedScore + Player_Score;
        engine.get()->enqueueSound(youWin, youWin_bytes, 45000);
        TextStream::instance().clear();
        TextStream::instance().setText("You WON!", 10, 11);
        TextStream::instance().setText("Press X to return", 11, 7);
        TextStream::instance().setFontColor(Text_setFontColor);
        questionBlock->getQuestionBlockSprite()->setVelocity(0,0);
        Bool_Won = true;
    }
}

void MiniGameScene::setData(int lives, int PlayerScore, int PlayerPosX, int PlayerPosY)
{
    this->Player_Lives = lives;
    PlayerSavedScore = PlayerScore;
    PlayerSavedPosX = PlayerPosX;
    PlayerSavedPosY = PlayerPosY;
}
