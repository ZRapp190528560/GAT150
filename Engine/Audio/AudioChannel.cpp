#include "pch.h"
#include "AudioChannel.h"

bool AZ::audioChannel::isPlaying()
{
	bool isPlaying = false;
	if (m_channel){
		m_channel->isPlaying(&isPlaying);
	}

	return isPlaying;
}

void AZ::audioChannel::stop(){
	if (isPlaying()){
		m_channel->stop();
	}
}
