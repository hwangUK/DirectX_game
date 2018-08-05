#include "stdafx.h"
#include "Sound.h"
#include <cstdio>

void Sound::OnInit(int bgmCount, int effCount)
{
	FMOD_System_Create(&m_fmodSystem);
	FMOD_System_Init(m_fmodSystem, 3, FMOD_INIT_NORMAL, NULL);
	m_nFmodBGMCount = bgmCount;
	m_nFmodEffectCount = effCount;
	m_fmodBGMChannel = new FMOD_CHANNEL *[m_nFmodBGMCount];
	m_fmodBGMSound = new FMOD_SOUND *[m_nFmodBGMCount];
	m_fmodEffectSound = new FMOD_SOUND *[m_nFmodEffectCount];
}

void Sound::CreateBGsound() {
	 
	char filename[100];
	
	for (int i = 0; i < m_nFmodBGMCount; i++) {
		sprintf_s(filename, "sound\\BGsound%d.mp3", i);
		FMOD_System_CreateSound(m_fmodSystem, filename, FMOD_LOOP_NORMAL, 0, &m_fmodBGMSound[i]);
	}
}

void Sound::CreateEffectSound() {
	char filename[100];	
	for (int i = 0; i < m_nFmodEffectCount; i++) {
		sprintf_s(filename, "sound\\EFsound%d.mp3", i);
		FMOD_System_CreateSound(m_fmodSystem, filename, FMOD_DEFAULT, 0, &m_fmodEffectSound[i]);
	}

}

void Sound::PlaySoundBG(int index) {
	FMOD_System_PlaySound(m_fmodSystem, m_fmodBGMSound[index], 0, 0, &m_fmodBGMChannel[index]);
}

void Sound::PlaySoundEF(int index) {
	FMOD_CHANNEL *pchannel;
	FMOD_System_PlaySound(m_fmodSystem, m_fmodEffectSound[index], 0, 0, &pchannel);

}

void Sound::StopSoundBG(int index) {
	FMOD_Channel_Stop(m_fmodBGMChannel[index]);
}

void Sound::Update() {
	FMOD_System_Update(m_fmodSystem);
}

void Sound::ReleaseSound() {
	if(m_fmodBGMChannel !=NULL) delete[] m_fmodBGMChannel;

	for (int i = 0; i < m_nFmodBGMCount; i++)	FMOD_Sound_Release(m_fmodBGMSound[i]);	
	if (m_fmodBGMSound != NULL) delete[] m_fmodBGMSound;

	for (int i = 0; i < m_nFmodEffectCount; i++)FMOD_Sound_Release(m_fmodEffectSound[i]);	
	if (m_fmodEffectSound != NULL) delete[] m_fmodEffectSound;

	FMOD_System_Close(m_fmodSystem);
	FMOD_System_Release(m_fmodSystem);
}

