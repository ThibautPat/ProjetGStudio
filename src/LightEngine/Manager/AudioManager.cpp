#include "AudioManager.h"
#include "GameManager.h"

#include <filesystem>
#include <iostream>

AudioManager::AudioManager()
{
    LoadMusic("TestWav.wav", true);
    //LoadMusic("Level(2).mp3", true);
    //LoadMusic("Level(3).mp3", true);
    //LoadMusic("Level(4).mp3", true);
    //LoadMusic("Level(5).mp3", true);
    //LoadMusic("Level(6).mp3", true);
    //LoadMusic("Level(7).mp3", true);
    //LoadMusic("Level.mp3", true);
    //LoadMusic("Menu.mp3", true);
    //LoadMusic("Menu(1).mp3", true);
    //LoadMusic("Kyokumei1.mp3", true);
    //LoadMusic("Kyokumei(1).mp3", true);
    //LoadMusic("Kyokumei.mp3", true);
    //LoadMusic("Garage.mp3", true);
    //LoadMusic("Map.mp3", true);
    //LoadMusic("Map(1).mp3", true);

    LoadSound("SoundTest.wav", false);
    LoadSound("SoundTest2.wav", false);
    //LoadSound("Bullet.mp3", false);
    //LoadSound("hitmarker.mp3", false);
    //LoadSound("Ough.mp3", false);
    //LoadSound("InstallModule.mp3", false);
}

void AudioManager::PlaySound(int index)
{
    m_CurrentSounds[index]->play();
    m_CurrentSounds[index]->setVolume(20.f);
}

void AudioManager::StopSound()
{
    for (int i = 0; i < m_CurrentSounds.size(); i++)
    {
        m_CurrentSounds[i]->stop();
    }
}

void AudioManager::ChangeSound(std::string sound)
{
    m_CurrentSounds.clear();
    m_CurrentSounds.push_back(m_SoundMap[sound]);

}

void AudioManager::ClearCurrentSound()
{
    m_CurrentSounds.clear();

}

void AudioManager::AddCurrrentSound(std::string sound)
{
    for (int i = 0; i < 16; i++)
    {
        m_CurrentSounds.push_back(m_SoundMap[sound]);
    }
}

void AudioManager::AddLevelSound(std::vector<std::string*> sound)
{
    for (int i = 0; i < sound.size(); i++)
    {
        m_CurrentSounds.push_back(m_SoundMap[*sound[i]]);
    }
}

void AudioManager::LoadSound(std::string Name, bool Loop)
{
    sf::SoundBuffer* buffer = new sf::SoundBuffer;
    if (!buffer->loadFromFile("../../../res/SOUND/" + Name))
    {
    }
    m_SoundBufferMap[Name] = buffer;
    sf::Sound* sound = new sf::Sound;
    sound->setBuffer(*buffer);
    sound->setLoop(Loop);
    m_SoundMap[Name] = sound;
}

void AudioManager::LoadMusic(std::string Name, bool Loop) {

    if (!std::filesystem::exists("../../../res/SOUND/" + Name)) {
        std::cout << "File not found: " << "../../../res/SOUND/" + Name << std::endl;
        return;
    }

    sf::Music* music = new sf::Music();
    if (!music->openFromFile("../../../res/SOUND/" + Name)) {
        std::cout << "File not open: " << "../../../res/SOUND/" + Name << std::endl;
        delete music;
        return;
    }
    music->setLoop(Loop);
    m_MusicMap.insert(std::pair<std::string, sf::Music*>(Name, music));
}

void AudioManager::AddLevelMusic(std::vector<std::string*>& sounds) {
    for (std::size_t i = 0; i < sounds.size(); i++) 
    {
        std::map<std::string, sf::Music*>::iterator it = m_MusicMap.find(*sounds[i]);
        if (it != m_MusicMap.end()) {
            m_CurrentMusic.push_back(it->second);
        }
    }
}

void AudioManager::PlayCurrentMusic() {
    for (std::size_t i = 0; i < m_CurrentMusic.size(); i++) {
        if (m_CurrentMusic[i] != nullptr) 
        {
            m_CurrentMusic[i]->play();
            m_CurrentMusic[i]->setVolume(20.f);
        }
    }
}

void AudioManager::StopCurrentMusic() {
    for (std::size_t i = 0; i < m_CurrentMusic.size(); i++) {
        if (m_CurrentMusic[i] != nullptr) {
            m_CurrentMusic[i]->stop();
        }
    }
}

void AudioManager::ClearCurrentMusic() {
    m_CurrentMusic.clear();
}

AudioManager::~AudioManager() {
    for (auto it = m_SoundMap.begin(); it != m_SoundMap.end();) {
        it->second->stop();
        delete (it->second);
        it = m_SoundMap.erase(it);
    }

    for (auto it = m_SoundBufferMap.begin(); it != m_SoundBufferMap.end();) {
        delete (it->second);
        it = m_SoundBufferMap.erase(it);
    }

    for (auto it = m_MusicMap.begin(); it != m_MusicMap.end();) {
        it->second->stop();
        delete (it->second);

        it = m_MusicMap.erase(it);
    }
}