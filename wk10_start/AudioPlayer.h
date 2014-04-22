#pragma once
#pragma comment (lib, "irrklang.lib")
#include <iostream>
#include <string>
#include <Windows.h>
#include "irrKlang/irrKlang.h"

using namespace irrklang;

class AudioPlayer
{
private:
	ISoundEngine* sndEngine;
	ISound* currSound;
	std::string fileName;
	int trackPos;
	int volume;
public:
	AudioPlayer(void);
	AudioPlayer(std::string soundFile); //initialises the file sound, doesn't play it
	~AudioPlayer(void);

	void playSound();
	void playSound(std::string soundFile);
	void pause();
	void resume();
	void volUp(int volUp);
	void volDown(int volDown);
	void mute();
};

