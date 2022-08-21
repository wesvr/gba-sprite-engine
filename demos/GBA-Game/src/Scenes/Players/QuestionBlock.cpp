//
// Created by Wesley Vrancken on 21/08/2022.
//

#include "QuestionBlock.h"

#define bottomHeightFor32 45
#define bottomHeightFor16 29

std::unique_ptr<AffineSprite>& QuestionBlock::getQuestionBlockSprite() {
    return questionBlockSprite;
}

void QuestionBlock::trigger() {
    triggerd = true;
    randomTimer = rand() % 100 + 150;
}

bool QuestionBlock::isTriggerd() {
    return triggerd;
}

void QuestionBlock::tick(u16 keys) {
    questionBlockSprite->setVelocity(0, 0);

    if (keys & KEY_RIGHT) {

        questionBlockSprite->setVelocity(-1, 0);
    }

    if (questionBlockSprite->getX() <= 0)
        questionBlockSprite->moveTo(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT - bottomHeightFor32 - 30);

    if (randomTimer > 0) {
        if (randomTimer == 1) {
            questionBlockSprite->animateToFrame(0);
            triggerd = false;
        }
        randomTimer--;

    }
}
