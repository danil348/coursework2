#include "Music.h"

void MusicManager::music_load(string file) {
    sf::Music* music;
    music = new sf::Music;
    if (music->openFromFile(file) == false) {
        return; // error
    }
    music->setVolume(50.f);
    this->musics.push_back(music);
    this->state.push_back(0);
}

void MusicManager::play_music(int numb)
{
    if (Setting::sound == true) {
        if (this->state[numb] == 0) {
            this->musics[numb]->play();
            this->state[numb] = 1;
        }
    }
}

void MusicManager::stop_music(int numb)
{
    if (this->state[numb] == 1) {
        this->musics[numb]->stop();
        this->state[numb] = 0;
    }
}

void MusicManager::update() 
{
    if (Setting::sound == false) {
        for (int i = 0; i < this->state.size(); i++) {
            this->musics[i]->setVolume(0.0f);
        }
    }
    else {
        for (int i = 0; i < this->state.size(); i++) {
            this->musics[i]->setVolume(50.0f);
        }
    }
}