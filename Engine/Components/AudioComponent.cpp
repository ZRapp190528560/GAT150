#include "pch.h"
#include "AudioComponent.h"
#include "Audio/Sound.h"
#include "Audio/AudioSystem.h"

bool AZ::audioComponent::create(void* data){
	m_owner = static_cast<gameObject*>(data);
	
	return true;
}

void AZ::audioComponent::destroy(){
	m_channel.stop();
}

void AZ::audioComponent::read(const rapidjson::Value& value){
	json::Get(value, "sound", m_soundName);
	json::Get(value, "loop", m_loop);
	json::Get(value, "playOnAwake", m_playOnAwake);

	if (m_playOnAwake){
		play();
	}
}

void AZ::audioComponent::update(){
}

void AZ::audioComponent::play(){
	m_channel.stop();

	sound* sound = m_owner->m_engine->getSystem<AZ::resourceManager>()->get<AZ::sound>(m_soundName, m_owner->m_engine->getSystem<AZ::audioSystem>());
	ASSERT_MSG((sound), "Could not find sound: " + m_soundName);
	m_channel = sound->play(m_loop);
}

void AZ::audioComponent::stop(){
	m_channel.stop();
}
