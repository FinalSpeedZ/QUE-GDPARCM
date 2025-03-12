#pragma once

#include "AGameObject.h"

class IconObject : public AGameObject
{
public:
    IconObject(std::string name, int textureIndex);

    void initialize() override;
    void update(sf::Time deltaTime) override;

    void draw(sf::RenderWindow* targetWindow) override;

private:
    int textureIndex;
    sf::Sprite* sprite = nullptr;
};


