#include "Pipes.h"

#include <random>

#include "../GameObjectManager.h"
#include "../../AssetLoader/SFXManager.h"

#include "../Player/Player.h"

Pipes::Pipes() : AGameObject("Pipes")
{

}

Pipes::~Pipes()
{
}

void Pipes::initialize()
{
    this->texture = TextureManager::getInstance()->getFromTextureMap("Pipe", 0);

    player = static_cast<Player*>(GameObjectManager::getInstance()->findObjectByName("Player"));

    for (int i = 0; i < PIPE_COUNT; i++)
    {
        PipePair pipe;

        pipe.topPipe = new sf::Sprite(*texture);
        pipe.bottomPipe = new sf::Sprite(*texture);

        sf::FloatRect globalBounds = pipe.topPipe->getGlobalBounds();
        sf::Vector2f size = globalBounds.size;
        pipe.topPipe->setOrigin({ size.x / 2, 0});
        pipe.bottomPipe->setOrigin({ size.x / 2, 0});

        pipe.bottomPipe->setRotation(sf::degrees(180));

        pipe.topPipe->setScale(sf::Vector2f(0.5, 1));
        pipe.bottomPipe->setScale(sf::Vector2f(0.5, 1));

        resetPipe(pipe);
        pipePool.push_back(pipe);
    }
}

void Pipes::update(sf::Time deltaTime)
{
    float deltaSeconds = deltaTime.asSeconds();

    if (pipePool.empty())
    {
        this->initialize();
        return;
    }

    PipePair* collidedPipe = nullptr;

    for (auto& pipe : pipePool)
    {
        pipe.topPipe->move({ -PIPE_SPEED * deltaSeconds, 0 });
        pipe.bottomPipe->move({ -PIPE_SPEED * deltaSeconds , 0 });


        sf::FloatRect globalBounds = pipe.topPipe->getGlobalBounds();
        sf::Vector2f size = globalBounds.size;

        if (!pipe.passed && pipe.topPipe->getPosition().x + size.x / 2 < player->sprite->getPosition().x &&
            pipe.bottomPipe->getPosition().x + size.x / 2 < player->sprite->getPosition().x)
        {
            SFXManager::getInstance()->getSound(SFXType::POINT)->play();
            pipe.passed = true;
        }

        if (pipe.topPipe->getPosition().x + size.x < 0)
        {
            resetPipe(pipe);
        }

        if (pipe.topPipe->getGlobalBounds().findIntersection(player->sprite->getGlobalBounds()) ||
            pipe.bottomPipe->getGlobalBounds().findIntersection(player->sprite->getGlobalBounds()))
        {
            player->setDead(true);
            SFXManager::getInstance()->getSound(SFXType::DIE)->play();
            collidedPipe = &pipe; 
            break;
        }
    }

    if (collidedPipe)
    {
        resetPipe(*collidedPipe); 
    }
}


void Pipes::resetPipe(PipePair& pipe)
{
    pipe.passed = false;

    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<int> x(WINDOW_WIDTH, 2 * WINDOW_WIDTH);
    std::uniform_int_distribution<int> topY(-800, -200);
    std::uniform_int_distribution<int> gap(250, 800); 

    float spawnX;
    bool validSpawn = false;
    while (!validSpawn)
    {
        spawnX = x(engine);
        validSpawn = true;

        for (const auto& otherPipe : pipePool)
        {
            if (std::abs(spawnX - otherPipe.topPipe->getPosition().x) <= 300)
            {
                validSpawn = false;
                break;
            }
        }
    }

    float topPipeY = topY(engine);
    float pipeGap = gap(engine);

    pipe.topPipe->setPosition({ spawnX, topPipeY});
    pipe.bottomPipe->setPosition({ spawnX, topPipeY + 1600 + pipeGap});
}

void Pipes::draw(sf::RenderWindow* targetWindow)
{
    for (auto& pipe : pipePool)
    {
        targetWindow->draw(*pipe.topPipe);
        targetWindow->draw(*pipe.bottomPipe);
    }
}
