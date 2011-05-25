#define USE_SNDFILE 1

#include <CLAM/Network.hxx>
#include <CLAM/OfflineNetworkPlayer.hxx>
#include <CLAM/MonoOfflineNetworkPlayer.hxx>
#include <CLAM/MonoAudioFileReader.hxx>
#include <CLAM/ControlPrinter.hxx>

#include "SpectrumXMLWriter.hpp"
#include "TestDataSource.hpp"
#include "TestMonitor.hpp"
#include <CLAM/PANetworkPlayer.hxx>

#include "AudioPlayer.hpp"

int error(const std::string& msg)
{
	std::cerr << msg << std::endl;
	return -1;
}

AudioPlayer::AudioPlayer(const std::string& audio)
{
	m_network = new CLAM::Network();
	
	std::string reader = m_network->AddProcessing("MonoAudioFileReader");
	CLAM::MonoAudioFileReaderConfig cfg;
	cfg.SetSourceFile(audio);
	if (!m_network->ConfigureProcessing(reader, cfg)) {
		error("Could not open the file");
	}
	
	std::string tonality = m_network->AddProcessing("TonalAnalysis");
	
	std::string time = m_network->AddProcessing("ControlPrinter");
	CLAM::ControlPrinterConfig ctrlcfg;
	ctrlcfg.SetGuiOnly(false);
	m_network->ConfigureProcessing(time, ctrlcfg);

	std::string peaks = m_network->AddProcessing("MyFuckingMonitor");
	std::string sink = m_network->AddProcessing("AudioSink");
	
	m_network->ConnectPorts(reader + ".Samples Read", tonality + ".Audio Input");
	m_network->ConnectControls(reader + ".Current Time Position", time + ".In Control");
	m_network->ConnectPorts(tonality + ".Chroma Peaks", peaks + ".Input");
	m_network->ConnectPorts(reader + ".Samples Read", sink + ".1");
	CLAM::PANetworkPlayer* player = new CLAM::PANetworkPlayer();
	m_network->SetPlayer(player);
}

AudioPlayer::~AudioPlayer()
{
	delete m_network;
}


void AudioPlayer::play()
{
	m_network->Start();
}

void AudioPlayer::pause()
{
	m_network->Pause();
}

void AudioPlayer::stop()
{
	m_network->Stop();
}

bool AudioPlayer::isPlaying()
{
	return m_network->IsPlaying();
}

void AudioPlayer::addFile(const std::string& file)
{	
	
}

int AudioPlayer::getLength()
{
	double length = ((CLAM::MonoAudioFileReader&) m_network->GetProcessing("MonoAudioFileReader")).GetHeader().GetLength();
	return (int) length / 1000;
}

void AudioPlayer::tempShit()
{
	CLAM::TData currentTime = 0.0f;
	CLAM::TData passedSeconds = 0.0f;
	CLAM::TData highestPeak = 0.0f;
	CLAM::TData currentPeak = 0.0f;
	CLAM::TData freq = 0.0f;
	/*
	while (m_network->IsPlaying()) {
		TestDataSource* testData = &((TestMonitor&) network.GetProcessing(peaks));

		if (testData.positionData() != 0 && testData.magnitudeData() != 0) {
			currentPeak = *testData.magnitudeData();
		}
		
		if (currentPeak > highestPeak) {
			highestPeak = currentPeak;
			freq = *testData.positionData();
		}
		currentTime = ((CLAM::InControl<CLAM::TData>&) ((CLAM::ControlPrinter&) network.GetProcessing(time)).GetInControl("In Control")).GetLastValue() - passedSeconds;
		
		if (currentTime > 1000.0f) {
			std::cout << "peak: " << highestPeak * 1000;
			std::cout << " - frequency: " << freq * 1000;
			passedSeconds += 1000.0f;
			highestPeak = 0.0f;
			std::cout << std::endl;
		}
		sleep(10);
	}
	*/
}

/*
int main(int argc, char** argv)
{
	if (argc != 2) return error ("needs a filename.");

	AudioPlayer player(argv[1]);
	player.play();
	while(player.isPlaying()) {
		sleep(1);
	}
}
*/