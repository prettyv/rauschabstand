/*
    Copyright (c) 2011 <copyright holder> <email>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef AUDIOPLAYER_HPP
#define AUDIOPLAYER_HPP

#include "cAudio/include/cAudio.h"
#include <vector>
#include <OgreVector3.h>

class AudioPlayer {

	public:

		AudioPlayer(const std::string& audio);
		virtual ~AudioPlayer();
		
		void addObstacles(std::vector<Ogre::Vector3> positions);

		void play();
		void playObstacles();
		void pause();
		void stop();
		
		bool isPlaying();
		void addFile(const std::string& file);
		int getLength();
		
		float getPitch();
		void increasePitch(float diff);
		void decreasePitch(float diff);
		void updateObstacles(Ogre::Vector3 shipVec);
		
		void reset(std::vector< Ogre::Vector3 > positions);

	private:

		cAudio::IAudioManager* audioMgr;
		cAudio::IAudioSource* trackMusic;
		cAudio::cVector3* playerPos;
		std::vector<cAudio::IAudioSource*> obstacles;
};

#endif // AUDIOPLAYER_HPP
