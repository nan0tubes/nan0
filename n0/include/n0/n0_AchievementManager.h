#ifndef __ACHIEVEMENTMANAGER_H__
#define __ACHIEVEMENTMANAGER_H__


class AchievementObjective
{
private:
	u32 m_objectiveID;
	// progress toward goal, objective is complete when (progress == goal)
	u32 m_progress;
	u32 m_amountRequired;
	bool m_isValid;
	std::string m_title;
	std::string m_description;

public:
	explicit AchievementObjective(Json::Value & objective);
	virtual ~AchievementObjective();

	void MakeProgress(u32 value);

	inline u32 GetID() const { return m_objectiveID; }
	inline u32 GetGoal() const { return m_amountRequired; }
	inline u32 GetProgress() const { return m_progress; }
	inline float GetPercentComplete() const { return ((float)m_progress / (float)m_amountRequired); } // returns a value between 0.f and 1.f
	inline bool IsValid() const { return m_isValid; }
	inline bool IsComplete() const { return (m_progress == m_amountRequired); }
};





class Achievement
{
private:
	u32 m_achievementID;
	bool m_isValid;
	std::vector<AchievementObjective*> m_objectives;
	std::string m_title;
	std::string m_description;

public:
	explicit Achievement(const Json::Value & achievement);
	virtual ~Achievement();

	void MakeProgress(u32 objectiveId, u32 value);

	inline u32 GetId() const { return m_achievementID; }
	inline u32 GetNumObjectives() const { return m_objectives.size(); }
	inline bool IsValid() const { return m_isValid; }
	inline bool IsComplete() const { for (u32 i = 0; i < m_objectives.size(); ++i) { if (!m_objectives.at(i)->IsComplete()) return false; } return true; }
};




class AchievementManager : IEventHandler<32>, IEventListener
{
public:
	AchievementManager();
	virtual ~AchievementManager();

	ErrorCode Init(const char filename[]);

	virtual bool OnEvent(Event *);
	virtual bool FireEvent(Event *e);
	void CleanUp();

private:
	std::vector<Achievement*> m_achievements;
};

#endif // __ACHIEVEMENTMANAGER_H__