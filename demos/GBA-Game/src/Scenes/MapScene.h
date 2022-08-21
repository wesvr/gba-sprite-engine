//
// Created by Wesley Vrancken on 21/08/2022.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_MAPSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_MAPSCENE_H

#include "libgba-sprite-engine/sprites/sprite.h"
#include "libgba-sprite-engine/sprites/affine_sprite.h"
#include "libgba-sprite-engine/background/background.h"
#include "libgba-sprite-engine/scene.h"
#include "PlayerSelectScene.h"
#include "../recourses/sounds/ShroomCitySound.h"

class MapScene : public Scene
{
private:
    std::unique_ptr<Background> background;
    std::unique_ptr<AffineSprite> PlayerSprite;
    PlayerSelectScene::CharSelection character;

    const signed char *const Music= ShroomCityMusic;
    const int Music_Bytes= ShroomCityMusic_bytes;

    enum Direction
    {
        up,
        down,
        left,
        right
    };

    bool
            Bool_PressingA,
            Bool_PressingB,
            Bool_PressingUp,
            Bool_PressingDown,
            Bool_pressingRight,
            Bool_pressingLeft,
            Bool_idle;

    int
            Text_setFontColor= BLD_BLACK,

            PlayerLives = 3,
            PlayerScore = 0,
            PlayerPosX = 0,
            PlayerPosY = 3,

    // 1 = nothing, 2 = skip turn, 3 = roll again, 4 = minigame
    featureMap[7][9] = {{0, 1, 1, 3, 4, 1, 0, 0, 0},
                        {0, 2, 0, 0, 0, 1, 3, 1, 2},
                        {0, 2, 0, 0, 0, 0, 0, 0, 1},
                        {1, 1, 2, 0, 0, 0, 0, 4, 1},
                        {0, 0, 1, 0, 0, 0, 0, 1, 0},
                        {0, 0, 1, 0, 0, 0, 0, 1, 0},
                        {0, 0, 1, 4, 3, 3, 1, 2, 0}};



public:
    MapScene(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;

    void setCharacter(PlayerSelectScene::CharSelection character);
    void MovePlayerTo(Direction);

    void ChoiceMinigameInMap();
    void SetPlayerData(int Player_Lives, int Player_Score, int Player_PosX, int Player_PosY);
};

#endif // GBA_SPRITE_ENGINE_PROJECT_MAPSCENE_H

