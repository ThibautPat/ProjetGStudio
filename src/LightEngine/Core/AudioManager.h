#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <vector>

class AudioManager
{
protected:

	std::map<std::string, sf::Sound*> m_SoundMap{};
	std::map<std::string, sf::SoundBuffer*> m_SoundBufferMap{};
	std::vector<sf::Sound*> m_CurrentSounds;

	std::map<std::string, sf::Music*> m_MusicMap{};
	std::vector<sf::Music*> m_CurrentMusic;

public:

	AudioManager();

	void PlaySound();
	void StopSound();
	void ChangeSound(std::string sound);
	void ClearCurrentSound();
	void AddCurrrentSound(std::string sound);
	void AddLevelSound(std::vector<std::string*> sound);
	void LoadSound(std::string Name, bool Loop);
	void LoadMusic(std::string Name, bool Loop);
	void AddLevelMusic(std::vector<std::string*>& sounds);
	void ClearCurrentMusic();
	void PlayCurrentMusic();
	void StopCurrentMusic();

	~AudioManager();
};
