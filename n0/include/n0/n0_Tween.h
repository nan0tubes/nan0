#ifndef __NAN0_TWEEN_H__
#define __NAN0_TWEEN_H__

namespace n0
{
	class Tween
	{
	public:
		enum ETweenType
		{
			TweenType_Linear = 0,
			TweenType_Sin,
			TweenType_SinFaked,
		};
		
		struct STweenPtr
		{
			virtual void Update(f32 progress) = 0;
			virtual void Finish() = 0;
			virtual void Begin() = 0;
		};

	public:
		template<typename T>
		struct STweenValue : public STweenPtr
		{
			STweenValue(T * pValue, T target)
				: m_pValue(pValue)
				, m_target(target)
				, m_original(0)
			{
				// empty
			}

			void Begin() { m_original = *m_pValue; }
			void Finish() { *m_pValue = m_target; }
			void Update(f32 progress) 
			{
				*m_pValue = m_original + (m_target - m_original) * progress; 
			}

			T * m_pValue;
			T m_target;
			T m_original;

		}; // STweenValue

	public:
		Tween()
			: m_tweenType(TweenType_Linear)
			, m_durationMS(0)
			, m_elapsedMS(0)
		{
			// empty
		}

		Tween(ETweenType tweenType, u64 durationMS)
			: m_tweenType(tweenType)
			, m_durationMS(durationMS)
			, m_elapsedMS(0)
		{
			// empty
		}

		template<class T>
		Tween(ETweenType tweenType, u64 durationMS, T * pValue, T target)
			: Tween(tweenType, durationMS)
		{
			AddValue(pValue, target);
		}

		virtual ~Tween();

		virtual void Tick(u64 deltaMS);

		template<class T>
		void AddValue(T * pValue, T target)
		{
			m_tweenValues.push_back(new STweenValue<T>(pValue, target));
		}
		
		void SetTweenType(ETweenType tweenType) { m_tweenType = tweenType; }
		void SetDuration(u64 durationMS) { m_durationMS = durationMS; }

		bool IsComplete() const { return m_elapsedMS >= m_durationMS; }
	
	protected:
		ETweenType m_tweenType;
		u64 m_durationMS;
		u64 m_elapsedMS;
		std::vector<STweenPtr*> m_tweenValues;

	}; // Tween

} // namespace n0

#endif // __NAN0_TWEEN_H__