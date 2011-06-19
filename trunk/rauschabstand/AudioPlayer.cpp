#include "AudioPlayer.hpp"

#include <cAudio/plugins/mp3Decoder/cMP3Plugin.h>

#include <iostream>

int error(const std::string& msg)
{
	std::cerr << msg << std::endl;
	return -1;
}

AudioPlayer::AudioPlayer(const std::string& audio)
{
	//Create an Audio Manager
	cAudio::IPluginManager* pluginMgr = cAudio::getPluginManager();
	pluginMgr->installPlugin(new cMP3DecoderPlugin());
	
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
	audioSrc->play();
	
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

float AudioPlayer::getPitch() {
	return audioSrc->getPitch();
}

void AudioPlayer::increasePitch(float diff) {
	audioSrc->setPitch(audioSrc->getPitch() + diff);
}

void AudioPlayer::decreasePitch(float diff) {
	audioSrc->setPitch(audioSrc->getPitch() - diff);
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