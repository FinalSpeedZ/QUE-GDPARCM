#pragma once

#include <SFML/Audio/Music.hpp>

#include "../AGameObject.h"
#include "../../Texture/TextureManager.h"
#include "../../Settings.h"

class Player;

class Pipes : public AGameObject
{
public:
    struct PipePair
    {
        sf::Sprite* topPipe;
        sf::Sprite* bottomPipe;
        bool passed = false;
    };

public:
    Pipes();
    ~Pipes() override;

    void initialize() override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow* targetWindow) override;

private:
    Player* player;

    void resetPipe(PipePair& pipe);

    std::vector<PipePair> pipePool;

    static constexpr int PIPE_COUNT = 5;
    static constexpr float PIPE_SPEED = 200.0f;
};
