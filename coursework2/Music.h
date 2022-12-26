#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

using namespace std;


class MusicManager
{
public:
    void music_load(string file);
    void play_music(int numb);
    void stop_music(int numb);
private:
    vector<sf::Music*> musics;
    vector<bool> state;
};