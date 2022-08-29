#include "AudioSystem.h"
#include "Core/Logger.h"
#include <fmod.hpp>

#include <map>

namespace neu
{
	void AudioSystem::Initialize()
	{
		FMOD::System_Create(&m_fmodSystem);
		void* extradriverdata = nullptr;
		m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	}

	void AudioSystem::Shutdown()
	{
		for (auto sounds : m_sounds)
		{
			sounds.second->release();
		}

		m_sounds.clear();
		m_fmodSystem->close();
		m_fmodSystem->release();
	}

	void AudioSystem::Update()
	{
		m_fmodSystem->update();
	}

	void AudioSystem::AddAudio(const std::string& name, const std::string& filename)
	{

		if (m_sounds.find(name) == m_sounds.end()) // !! use find() on m_sounds to see if element exists, only set sound if it does not
		{
			FMOD::Sound* sound = nullptr;
			m_fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
			if (sound == nullptr)
			{
				LOG("Error creating sound %s.", filename.c_str());
			}
			m_sounds[name] = sound;
		}
	}

	AudioChannel AudioSystem::PlayAudio(const std::string& name, float volume, float pitch, bool loop)
	{
		auto iter = m_sounds.find(name);

		if (iter == m_sounds.end())
		{
			LOG("Error could not find sound %s ", name.c_str());
			return AudioChannel{};
		}
		FMOD::Sound* sound = iter->second;
		FMOD_MODE mode = (loop) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		sound->setMode(mode);

		FMOD::Channel* channel;
		m_fmodSystem->playSound(sound, 0, false, &channel);
		channel->setVolume(volume);
		channel->setPitch(pitch);
		channel->setPaused(false);

		return AudioChannel{ channel };
	}
}

// neu::AudioSystem::PlayAudio(const std::string& name, bool loop)
//{
//	auto iter = m_sounds.find(name);// !! use find() on m_sounds and return the iterator
//
//	if (iter == m_sounds.end())
//	{
//		LOG("could not find sound %s.", name.c_str());
//	}
//
//		if (iter != m_sounds.end()) // !! if iterator is not m_sounds.end()
//		{
//			FMOD::Sound* sound = iter->second;
//
//			if (loop)
//			{
//				
//				sound->setMode(FMOD_LOOP_NORMAL);
//			}else
//			{
//			sound->setMode(FMOD_LOOP_OFF);
//			}
//			FMOD::Channel* channel;
//			m_fmodSystem->playSound(sound, 0, false, &channel);
//		}
//}
