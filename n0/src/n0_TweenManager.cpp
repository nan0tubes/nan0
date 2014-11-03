#include "n0/n0.h"

namespace n0
{

	TweenManager::TweenManager()
	{

	}

	TweenManager::~TweenManager()
	{
		RemoveAllTweens();
	}

	Tween * TweenManager::AddTween(Tween * pTween)
	{
		if (pTween)
		{
			//TODO: insert an OnTweenComplete event listener/callback
			m_Tweens.insert(pTween);
			return pTween;
		}
		return NULL;
	}

	void TweenManager::RemoveTween(Tween * pTween)
	{
		std::set<Tween*>::iterator it = m_Tweens.find(pTween);
		if (it != m_Tweens.end())
		{
			Tween * pTween = *it;
			delete pTween;
			m_Tweens.erase(it);
		}
	}

	void TweenManager::RemoveAllTweens()
	{
		for (std::set<Tween*>::iterator it = m_Tweens.begin(); it != m_Tweens.end(); ++it)
		{
			delete *it;
		}
		m_Tweens.clear();
	}

	void TweenManager::Tick(u64 deltaMS)
	{
		for (std::set<Tween*>::iterator it = m_Tweens.begin(); it != m_Tweens.end();)
		{
			Tween * pTween = *it;

			pTween->Tick(deltaMS);

			if (pTween->IsComplete())
			{
				m_Tweens.erase(it++);
				delete pTween;
			}
			else
			{
				++it;
			}
		}
	}

} // namespace n0