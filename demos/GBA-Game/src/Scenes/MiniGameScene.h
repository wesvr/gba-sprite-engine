//
// Created by Wesley Vrancken on 21/08/2022.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_MINIGAMESCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_MINIGAMESCENE_H

#include "libgba-sprite-engine/gba_engine.h"
#include "libgba-sprite-engine/scene.h"
#include "libgba-sprite-engine/background/background.h"
#include <vector>
#include "libgba-sprite-engine/sprites/affine_sprite.h"
#include "Players/QuestionBlock.h"
#include "Players/goomba.h"
#include "Players/Luigi.h"

class MiniGameScene : public Scene{
private:
    //the background
    std::unique_ptr<Background> bg;
    std::unique_ptr<Luigi> luigi;
    std::unique_ptr<AffineSprite> luigiSprite;
    std::unique_ptr<Goomba> goomba;
    std::unique_ptr<AffineSprite> goombaSprite;
    std::unique_ptr<QuestionBlock> questionBlock;
    std::unique_ptr<AffineSprite> questionBlockSprite;

    bool
            stopScrollBg,
            Bool_Dead = false,
            Bool_Won = false;

    int
            Text_setFontColor= BLD_BLACK,
            PlayerSavedScore,
            PlayerSavedPosX=0,
            PlayerSavedPosY=3,
            scrollX,
            scrollY,

            Player_Score=0,
            Player_Lives=0;

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    MiniGameScene(std::shared_ptr<GBAEngine> engine) : Scene(engine), scrollX(0), scrollY(0), stopScrollBg(false), Player_Score(0), Player_Lives(1) {}

    void load() override;
    void tick(u16 keys) override;
    void addPoint();
    void setData(int i, int PlayerScore, int PlayerPosX, int PlayerPosY);
    void PlayerWon();
    void PlayerDied();
};

#endif //GBA_SPRITE_ENGINE_PROJECT_MINIGAMESCENE_H

