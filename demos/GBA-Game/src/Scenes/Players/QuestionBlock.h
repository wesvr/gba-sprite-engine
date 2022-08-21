//
// Created by Wesley Vrancken on 21/08/2022.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_QUESTIONBLOCK_H
#define GBA_SPRITE_ENGINE_PROJECT_QUESTIONBLOCK_H

#include "libgba-sprite-engine/gba_engine.h"
#include "libgba-sprite-engine/scene.h"
#include "libgba-sprite-engine/background/background.h"
#include <vector>
#include "libgba-sprite-engine/sprites/affine_sprite.h"

class QuestionBlock {
private:
    std::unique_ptr<AffineSprite> questionBlockSprite;
    int randomTimer;
    bool triggerd;
public:
    QuestionBlock(std::unique_ptr<AffineSprite> s ) : questionBlockSprite(std::move(s)), randomTimer(0), triggerd(false) {}
    QuestionBlock() {}
    std::unique_ptr<AffineSprite>& getQuestionBlockSprite();
    void tick(u16 keys);
    void trigger();
    bool isTriggerd();
};


#endif //GBA_SPRITE_ENGINE_PROJECT_QUESTIONBLOCK_H
