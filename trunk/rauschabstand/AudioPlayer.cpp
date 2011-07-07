#include "AudioPlayer.hpp"

#include <cAudio/plugins/mp3Decoder/cMP3Plugin.h>

#include <iostream>
#include <sstream>

int error(const std::string& msg)
{
	std::cerr << msg << std::endl;
	return -1;
}

cAudio::cVector3 ogreVecTocVec(Ogre::Vector3 vec) {
	cAudio::cVector3 cVec;
	cVec.x = (float) vec.x;
	cVec.y = (float) vec.y;
	cVec.z = (float) vec.z;
	return cVec;
}

AudioPlayer::AudioPlayer(const std::string& audio)
{
	//Create an Audio Manager
	//cAudio::IPluginManager* pluginMgr = cAudio::getPluginManager();
	//pluginMgr->installPlugin(new cMP3DecoderPlugin());

	audioMgr = cAudio::createAudioManager(true);
	playerPos = new cAudio::cVector3(0.0f, 0.0f, 0.0f);
	audioMgr->getListener()->setPosition(*playerPos);
	trackMusic = audioMgr->create("bgmusic", audio.c_str(), true);
	//trackMusic->setVolume(0.2f);
	shipHum = audioMgr->create("shipHum", "shipHum.wav", false);
}

AudioPlayer::~AudioPlayer()
{
	delete playerPos;
	audioMgr->shutDown();
    cAudio::destroyAudioManager(audioMgr);
}

void AudioPlayer::addObstacles(std::vector<Ogre::Vector3> positions) {
	IAudioSource* obstacle;
	std::ostringstream ss;
	cAudio::cVector3 position;
	for (unsigned int i = 0; i < positions.size(); i++) {
		ss << "obstacle" << i;
		obstacle =  audioMgr->create(ss.str().c_str(), "obstacleHum.wav", false);
		position = ogreVecTocVec(positions[i]);
		position.x =  0;
		position.y =  0;
		position.z = -position.z;
		obstacle->setPosition(position);
		//obstacle->setMaxDistance(500.0f);
		obstacle->setRolloffFactor(15.0f);
		obstacle->setVolume(20.0f);
		obstacles.push_back(obstacle);
		ss.str("");
	}
}

void AudioPlayer::play()
{
	trackMusic->play();/*
	for (unsigned int i = 0; i < obstacles.size(); i++) {
		obstacles[i]->play3d(obstacles[i]->getPosition(), 1.0, true);
	}*/
}

void AudioPlayer::playShip() {
	shipHum->play2d(true);
}

void AudioPlayer::resumeShip() {
	if (!shipHum->isPlaying()) {
		playShip();
	}
}

void AudioPlayer::playSound(const std::string& audio) {
	audioMgr->create("temp", audio.c_str(), false)->play2d();
}

void AudioPlayer::pause()
{
	trackMusic->pause();
	shipHum->pause();
	for (unsigned int i = 0; i < obstacles.size(); i++) {
		obstacles[i]->pause();
	}
}

void AudioPlayer::stop()
{
	trackMusic->stop();
	shipHum->stop();
	for (unsigned int i = 0; i < obstacles.size(); i++) {
		obstacles[i]->stop();
	}
}

bool AudioPlayer::isPlaying()
{
	return trackMusic->isPlaying();
}

int AudioPlayer::getLength()
{
	return (int) trackMusic->getTotalAudioTime();
}

float AudioPlayer::getPitch() {
	return trackMusic->getPitch();
}

void AudioPlayer::increasePitch(float diff) {
	trackMusic->setPitch(trackMusic->getPitch() + diff);
	shipHum->setPitch(shipHum->getPitch() + diff);
}

void AudioPlayer::decreasePitch(float diff) {
	trackMusic->setPitch(trackMusic->getPitch() - diff);
	shipHum->setPitch(shipHum->getPitch() - diff);
}

void AudioPlayer::updateObstacles(Ogre::Vector3 shipVec) {
	shipVec.y = 0;
	for (unsigned int i = 0; i < obstacles.size(); i++) {
		obstacles[i]->move(obstacles[i]->getPosition() - ogreVecTocVec(shipVec));
	}
}

void AudioPlayer::reset(std::vector<Ogre::Vector3> positions) {
	stop();
	trackMusic->setPitch(1.0f);
	shipHum->setPitch(1.0f);
	cAudio::cVector3 position;
	for (unsigned int i = 0; i < obstacles.size(); i++) {
		obstacles[i]->setPitch(1.0f);
		position = ogreVecTocVec(positions[i]);
		position.x =  0;
		position.y =  0;
		position.z = -position.z;
		obstacles[i]->setPosition(position);
	}
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