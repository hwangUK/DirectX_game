#include "stdafx.h"
#include "CustomTimer.h"

void CustomTimer::ReSetTimer()
{
	dwCurTime = 0;
	dwOldTime = GetTickCount();
	m_dwElapseTime = 0;
	m_dwTimer = 0;
}
void CustomTimer::StartTimer()
{
	dwCurTime = GetTickCount();
	m_dwElapseTime = dwCurTime - dwOldTime;
	dwOldTime = dwCurTime;

	m_dwTimer += m_dwElapseTime;
}

int CustomTimer::GetTimer()
{
	return m_dwTimer;
}
DWORD CustomTimer::GetElapsedTimer()
{
	return m_dwElapseTime;
}

