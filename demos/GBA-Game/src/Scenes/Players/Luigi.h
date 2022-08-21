//
// Created by Wesley Vrancken on 21/08/2022.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_LUIGI_H
#define GBA_SPRITE_ENGINE_PROJECT_LUIGI_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/background/background.h>
#include <vector>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

class Luigi {
private:
    std::unique_ptr<AffineSprite> luigiSprite;
    bool dead;
    int CurrentLvl;
    int lives;

public:
    Luigi(std::unique_ptr<AffineSprite> s) : luigiSprite(std::move(s)), dead(false) {}
    Luigi() {}
    std::unique_ptr<AffineSprite>& getLuigiSprite();
    void tick(u16 keys);
    void tickEndScene(u16 keys);
    void kill();
    bool isDead();
    void setCurrentLvl(int lvl);
    int getCurrentLvl();
    void subtracktLife();
    int getLives();
    void setLives(int lives);

};


#endif //GBA_SPRITE_ENGINE_PROJECT_LUIGI_H
