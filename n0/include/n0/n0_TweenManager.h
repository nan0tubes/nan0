#ifndef __NAN0_TWEENMANAGER_H__
#define __NAN0_TWEENMANAGER_H__


namespace n0
{
	class TweenManager
	{
	public:
		TweenManager();
		virtual ~TweenManager();

		template<class T>
		Tween * AddTween(Tween::ETweenType tweenType, u64 durationMS, T * pValue, T target)
		{
			if (pValue)
			{
				return AddTween(new Tween(tweenType, durationMS, pValue, target));
			}
			return NULL;
		}
		Tween * AddTween() { return AddTween(new Tween()); }
		Tween * AddTween(Tween::ETweenType tweenType, u64 durationMS) { return AddTween(new Tween(tweenType, durationMS)); }
		Tween * AddTween(Tween * pTween);
		virtual void RemoveTween(Tween * pTween);
		virtual void RemoveAllTweens();
		virtual void Tick(u64 deltaMS);

	protected:
		std::set<Tween*> m_Tweens;

	}; // class TweenManager

} // namespace n0

#endif // __NAN0_TWEENMANAGER_H__