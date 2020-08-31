#include "pch.h"
#include "Sound.h"
#include "AudioSystem.h"

bool AZ::sound::create(const std::string& name, void* data){
    m_system = static_cast<audioSystem*>(data)->m_system;
    FMOD_RESULT result = m_system->createSound(name.c_str(), FMOD_DEFAULT, 0, &m_sound);
    ASSERT_MSG(result == FMOD_OK, "Error creating sound:" + name);

    return true;
}

void AZ::sound::destroy(){
    if (m_sound) {
        m_sound->release();
    }
}

AZ::audioChannel AZ::sound::play(bool loop){
    FMOD_MODE mode = (loop) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
    m_sound->setMode(mode);

    FMOD::Channel* channel;
    FMOD_RESULT result = m_system->playSound(m_sound, 0, false, &channel);
    ASSERT_MSG(result == FMOD_OK, "Error playing FMOD sound.");

    return audioChannel{ channel };
}
