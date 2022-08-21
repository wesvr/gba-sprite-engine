//
// Created by Wesley Vrancken on 21/08/2022.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GAMEOVERSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_GAMEOVERSCENE_H

#include "libgba-sprite-engine/scene.h"
#include "../recourses/sounds/gameOverSound.h"

class GameOverScene : public Scene
{
private:
    std::unique_ptr<Background> background;
    int finalScore;

    const signed char *const Music= GameOverSound;
    const int Music_Bytes= GameOverSound_bytes;

public:
    GameOverScene(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;

    void setFinalScore(int score);
};

#endif // GBA_SPRITE_ENGINE_PROJECT_GAMEOVERSCENE_H

