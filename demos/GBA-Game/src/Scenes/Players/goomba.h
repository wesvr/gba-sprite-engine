//
// Created by Wesley Vrancken on 21/08/2022.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GOOMBA_H
#define GBA_SPRITE_ENGINE_PROJECT_GOOMBA_H

#include "libgba-sprite-engine/gba_engine.h"
#include "libgba-sprite-engine/scene.h"
#include "libgba-sprite-engine/background/background.h"
#include <vector>
#include "libgba-sprite-engine/sprites/affine_sprite.h"

class Goomba {
private:
    std::unique_ptr<AffineSprite> goombaSprite;
    bool dead;
    int randomTimer;
public:
    Goomba(std::unique_ptr<AffineSprite> s): goombaSprite(std::move(s)), dead(false), randomTimer(0) {}
    Goomba() {}
    std::unique_ptr<AffineSprite>& getGoombaSprite();
    bool isDead();
    void kill();
    void resurrect();
    void tick(u16 keys);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_GOOMBA_H
