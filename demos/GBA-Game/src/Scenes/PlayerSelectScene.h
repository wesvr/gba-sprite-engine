//
// Created by Wesley Vrancken on 21/08/2022.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYERSELECTSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYERSELECTSCENE_H

#include "libgba-sprite-engine/scene.h"
#include "../../engine/include/libgba-sprite-engine/gba/tonc_memdef.h"

class PlayerSelectScene : public Scene {
private:
    std::unique_ptr<Background> background;
    std::unique_ptr<Sprite> Sprite_Mario;
    std::unique_ptr<Sprite> Sprite_Luigi;
    std::unique_ptr<Sprite> Sprite_Peach;
    std::unique_ptr<Sprite> Sprite_Yoshi;
    std::unique_ptr<Sprite> Sprite_Hand;


    bool
            Bool_PressingLeft,
            Bool_PressingRight,
            Bool_PressingA,
            Bool_PlayerIsSelected,
            BOOL_PlayerIsSelected;

    int Text_setFontColor= BLD_WHITE;

    void buildPlayableCharacterSprites();

public:
    int PlayerPosition;
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    PlayerSelectScene(const std::shared_ptr<GBAEngine> &engine);

    void load() override;
    void PlayerIsSelected(u16 keys);
    void PlayerIsNotSelected(u16 keys);
    void tick(u16 keys) override;

    enum CharSelection { mario_char, luigi_char, peach_char, yoshi_char };
    CharSelection charSelect;

};

#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYERSELECTSCENE_H
