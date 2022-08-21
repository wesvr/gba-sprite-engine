//
// Created by Wesley Vrancken on 21/08/2022.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_STARTSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_STARTSCENE_H

#include "libgba-sprite-engine/scene.h"
#include "libgba-sprite-engine/sprites/affine_sprite.h"
#include "../recourses/sounds/startScreenSound.h"

class StartScene : public Scene {
private:
    std::unique_ptr<AffineSprite> Sprite_Luigi;
    std::unique_ptr<AffineSprite> Sprite_Goomba;
    std::unique_ptr<Background> background;
    std::unique_ptr<Sprite> Sprite_Start;

    const signed char *const Music= startScreenSound;
    const int Music_Bytes= startScreenSound_bytes;

public:
    StartScene(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_STARTSCENE_H

