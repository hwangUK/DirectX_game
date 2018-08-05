#pragma once
class CustomTimer{
private:
	DWORD dwOldTime;
	DWORD dwCurTime;

	DWORD m_dwElapseTime;
	int m_dwTimer;

public:
	void ReSetTimer();
	void StartTimer();
	int GetTimer();
	DWORD GetElapsedTimer();
};

