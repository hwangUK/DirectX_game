#pragma once
#include <fmod.h>
#include <string>

using namespace std;

class Sound
{
private:
	int m_nFmodBGMCount;
	int m_nFmodEffectCount;
	FMOD_SYSTEM* m_fmodSystem;
	FMOD_SOUND** m_fmodBGMSound;
	FMOD_SOUND** m_fmodEffectSound;
	FMOD_CHANNEL** m_fmodBGMChannel;

public:	
	void OnInit(int bgmCount, int effCount);
	void CreateBGsound();
	void CreateEffectSound();

	void PlaySoundEF(int index);
	void PlaySoundBG(int index);
	void StopSoundBG(int index);
	void Update();
	void ReleaseSound();		
};

