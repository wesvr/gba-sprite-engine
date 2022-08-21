//
// Created by Wesley Vrancken on 21/08/2022.
//

#include "goomba.h"

#define bottomHeightFor32 45
#define bottomHeightFor16 29

std::unique_ptr<AffineSprite>& Goomba::getGoombaSprite() {
    return goombaSprite;
}

bool Goomba::isDead() {
    return dead;
}

void Goomba::kill() {
    dead = true;
}

void Goomba::resurrect() {
    randomTimer = rand() %100 + 150;
}

void Goomba::tick(u16 keys) {
    goombaSprite->setVelocity(-1,0);

    if(keys & KEY_RIGHT) {
        goombaSprite->setVelocity(goombaSprite->getVelocity().x-1,0);
    }

    if(goombaSprite->getX() <= 1) goombaSprite->moveTo(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT-bottomHeightFor16);

    if(randomTimer > 0){
        if(randomTimer == 1){
            dead = false;
            goombaSprite->moveTo(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT-bottomHeightFor16);
            goombaSprite->animate();
        }
        randomTimer--;
    }
}
