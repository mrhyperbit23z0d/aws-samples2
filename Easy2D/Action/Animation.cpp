#include "..\eactions.h"
#include "..\Win\winbase.h"

e2d::Animation::Animation(float duration)
{
	m_nDuration = 0;
	m_nTotalDuration = UINT(duration * 1000);
}

e2d::Animation::~Animation()
{
}

bool e2d::Animation::_isEnd() const
{
	return m_nDuration >= m_nTotalDuration;
}

void e2d::Animation::_init()
{
	EAction::_init();
	// 记录当前时间
	m_nLast = GetNow();
}

bool e2d::Animation::_isDelayEnough()
{
	// 判断时间间隔是否足够
	if (GetInterval(m_nLast) > m_nAnimationInterval)
	{
		// 重新记录时间
		m_nLast += milliseconds(m_nAnimationInterval);
		m_nDuration += m_nAnimationInterval;
		return true;
	}
	return false;
}

void e2d::Animation::_reset()
{
	EAction::_reset();
	m_nDuration = 0;
	// 记录当前时间
	m_nLast = GetNow();
}
