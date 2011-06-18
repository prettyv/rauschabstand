#include "AudioPlayer.hpp"

#include <iostream>

int error(const std::string& msg)
{
	std::cerr << msg << std::endl;
	return -1;
}

AudioPlayer::AudioPlayer(const std::string& audio)
{
	//Create an Audio Manager
        audioMgr = cAudio::createAudioManager(true);
        audioSrc = audioMgr->create("bgmusic", audio.c_str(), true);
}

AudioPlayer::~AudioPlayer()
{
	audioMgr->shutDown();
    cAudio::destroyAudioManager(audioMgr);
}


void AudioPlayer::play()
{
	audioSrc->play2d(false);
	
}

void AudioPlayer::pause()
{
	audioSrc->pause();
}

void AudioPlayer::stop()
{
	audioSrc->stop();
}

bool AudioPlayer::isPlaying()
{
	return audioSrc->isPlaying();
}

void AudioPlayer::addFile(const std::string& file) {	
	audioMgr->create("sfx", file.c_str(), true);
}

int AudioPlayer::getLength()
{
	return (int) audioSrc->getTotalAudioTime();
}

/*
int main(int argc, char** argv)
{
	if (argc != 2) return error ("needs a filename.");

	AudioPlayer player(argv[1]);
	player.play();
	while(player.isPlaying()) {
		cAudio::cAudioSleep(10);
	}
}
*/