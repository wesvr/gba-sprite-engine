//
// Created by Wesley Vrancken on 21/08/2022.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_CHARACTERDIRECTOR_H
#define GBA_SPRITE_ENGINE_PROJECT_CHARACTERDIRECTOR_H

#include "libgba-sprite-engine/sprites/sprite_builder.h"
#include "../recourses/sprites/mario.h"
#include "../recourses/sprites/luigi.h"
#include "../recourses/sprites/peach.h"
#include "../recourses/sprites/yoshi.h"
#include "../recourses/sprites/hand.h"

class CharacterDirector {
    const SpriteSize characterSpriteSize = SIZE_32_32;
    const u32 Y = 60;
public:
    CharacterDirector();
    explicit CharacterDirector(SpriteSize size): characterSpriteSize(size) {};
    explicit CharacterDirector(u32 y): Y(y) {};
    explicit CharacterDirector(SpriteSize size, u32 y):
            characterSpriteSize(size),
            Y(y) {};

    void buildMario(SpriteBuilder<Sprite> &builder) {
        buildCharacterCore(builder, marioSelTiles);
        builder.withLocation(50,Y);
    }

    void buildLuigi(SpriteBuilder<Sprite> &builder) {
        buildCharacterCore(builder, luigiSelTiles);
        builder.withLocation(85,Y);
    }

    void buildPeach(SpriteBuilder<Sprite> &builder) {
        buildCharacterCore(builder, peachSelTiles);
        builder.withLocation(120,Y);
    }

    void buildYoshi(SpriteBuilder<Sprite> &builder) {
        buildCharacterCore(builder, yoshiSelTiles);
        builder.withLocation(155,Y);
    }

private:
    void buildCharacterCore(SpriteBuilder<Sprite> &builder, const unsigned int* tiles) {
        builder
                .withData(tiles, sizeof(unsigned int)*256)
                .withSize(SIZE_32_32);
    }
};


#endif //GBA_SPRITE_ENGINE_PROJECT_CHARACTERDIRECTOR_H