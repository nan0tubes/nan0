#include "n0/n0.h"

namespace n0
{

	Tween::~Tween()
	{
		for (std::vector<STweenPtr*>::iterator it = m_tweenValues.begin(); it != m_tweenValues.end(); ++it)
		{
			STweenPtr * pValue = *it;
		//	pValue->m_pValue = NULL;
			delete pValue;
		}
	}

	

	void Tween::Tick(u64 delataMS)
	{
		const u64 preTickElapsed = m_elapsedMS;
		m_elapsedMS += delataMS;

		// tween all the values, don't worry about checking if complete, tween will be deleted by TweenManager once it's complete
		for (std::vector<STweenPtr*>::iterator it = m_tweenValues.begin(); it != m_tweenValues.end(); ++it)
		{
			// if no time has elapsed, initialize the start position
 			if (preTickElapsed <= 0)
			{
				(*it)->Begin();
			}

			f32 progress = (f32)m_elapsedMS / (f32)m_durationMS;

			// calculate progress (in percent) based on requested tween type
			if (m_tweenType == TweenType_Sin)
			{
				progress = 0.5f - cos(-progress * PI_HALF) * 0.5f;
			}
			else if (m_tweenType == TweenType_SinFaked)
			{
				progress = progress * progress * (3 - 2 * progress);
			}

			(*it)->Update(progress);

 			// don't overshoot the target
 			if (IsComplete())
				(*it)->Finish();
		}

		// if we're done, notify listeners
		if (IsComplete())
		{

		}
	}

} // namespace n0