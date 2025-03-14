#include "SFXManager.h"

SFXManager* SFXManager::sharedInstance = NULL;

SFXManager::SFXManager()
{
    this->create(SFXType::POINT, "../Media/flappyPoint.mp3");
    this->create(SFXType::DIE, "../Media/flappyDie.mp3");
    this->create(SFXType::POP, "../Media/flappyPop.mp3");
}

void SFXManager::initialize()
{
    sharedInstance = new SFXManager();
}

SFXManager* SFXManager::getInstance()
{
    return sharedInstance;
}

void SFXManager::unloadAll()
{
    for (sf::Sound* sound : this->vecSound)
    {
        if (sound->getStatus() == sf::SoundSource::Status::Stopped) 
        {
            delete sound;
        }
    }
}

sf::Sound* SFXManager::getSound(SFXType EType)
{
    return this->mapSound[EType];
}

void SFXManager::create(SFXType EType, std::string strPath)
{
    sf::SoundBuffer* pBuffer = new sf::SoundBuffer();
    sf::Sound* pSound = new sf::Sound(*pBuffer);

    pBuffer->loadFromFile(strPath);
    pSound->setBuffer(*pBuffer);
    this->add(EType, pSound);
}

void SFXManager::add(SFXType EType, sf::Sound* pSound)
{
    this->mapSound[EType] = pSound;
    this->vecSound.push_back(pSound);
}

