//
// Created by Wesley Vrancken on 21/08/2022.
//

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/allocator.h>

#include "Scenes/StartScene.h"

int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    auto startScene = new StartScene(engine);
    engine -> setScene(startScene);

    while (true){
        engine -> update();
    }
}
