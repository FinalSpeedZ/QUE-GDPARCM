#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <unordered_map>

enum class SFXType : int
{
	POINT,
	DIE,
	POP,
};

class SFXManager
{
public:
	static void initialize();
	static SFXManager* getInstance();

public:
	void unloadAll();
	sf::Sound* getSound(SFXType EType);
	void create(SFXType EType, std::string strPath);
	void add(SFXType EType, sf::Sound* pSound);

private:
	SFXManager();
	SFXManager(SFXManager const&) {};             // copy constructor is private
	SFXManager& operator=(SFXManager const&) {};  // assignment operator is private

private:
	static SFXManager* sharedInstance;

private:
	std::unordered_map<SFXType, sf::Sound*> mapSound;
	std::vector<sf::Sound*> vecSound;
};

