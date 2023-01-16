#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "Setting.h"

using namespace std;

class MusicManager
{
public:
    void music_load(string file);
    void play_music(int numb);
    void stop_music(int numb);
    void update();
private:
    vector<sf::Music*> musics;
    vector<bool> state;
};