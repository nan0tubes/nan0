#include "n0/n0.h"

namespace n0
{

//MARK: - AchievementObject
AchievementObjective::AchievementObjective()
	: m_progress(0)
{
	char msg[kStrLen_Huge];
	
	m_isValid = true;
	m_title = objective.get("title", "").asString();
	if (m_title.size() == 0)
	{
		snprintf(msg, kStrLen_Huge, "Objective is missing 'title'.");
		GetGame()->GetBlackBox()->Log("SYSTEM", 0, msg);
		m_isValid = false;
		return;
	}
#ifdef DEBUG
	snprintf(msg, kStrLen_Huge, "...'%s'", m_title.c_str());
	GetGame()->GetBlackBox()->Log("DEBUG", 0, msg);
#endif
	m_objectiveID = Hash(m_title.c_str());
	m_description = objective.get("description", "").asString();
	m_amountRequired = objective.get("amount_required", 0).asUInt();
	if (m_amountRequired == 0)
	{
		snprintf(msg, kStrLen_Huge, "Objective is missing 'amount_required'.");
		GetGame()->GetBlackBox()->Log("SYSTEM", 0, msg);
		m_isValid = false;
		return;
	}
}

AchievementObjective::~AchievementObjective() 
{
	//TODO:
}

void AchievementObjective::MakeProgress(u32 value)
{
	u32 sum = m_progress + value;
	if (value >= m_amountRequired || sum < m_progress || sum < value || sum >= m_amountRequired)
	{
		m_progress = m_amountRequired;
		SAchievementEvent e(SAchievementEvent::kEvent_Achievement_AchievementProgress, m_objectiveID, 0);
		GetGame()->FireEvent(&e);
	}
	else
	{
		m_progress = sum;
	}
}

//MARK: - Achievement
Achievement::Achievement(const Json::Value & achievement)
{
	char msg[kStrLen_Huge];

	m_isValid = true;
	m_title = achievement.get("title", "").asString();
	if (m_title.size() == 0)
	{
		snprintf(msg, kStrLen_Huge, "Achievement is missing 'title'.");
		GetGame()->GetBlackBox()->Log("SYSTEM", 0, msg);
		m_isValid = false;
		return;
	}
#ifdef DEBUG
	snprintf(msg, kStrLen_Huge, ".'%s'", m_title.c_str());
	GetGame()->GetBlackBox()->Log("DEBUG", 0, msg);
#endif
	m_achievementID = Hash(m_title.c_str());
	m_description = achievement.get("description", "").asString();
	Json::Value objectives = achievement["objectives"];
	for (u32 i = 0; i < objectives.size(); ++i)
	{
		AchievementObjective *objective = new AchievementObjective(objectives[i]);
		if (objective->IsValid())
			m_objectives.push_back(objective);
		else
		{
			snprintf(msg, kStrLen_Huge, "An error was encountered in '%s'; bad objective at index %u", m_title.c_str(), i);
			GetGame()->GetBlackBox()->Log("SYSTEM", 0, msg);
			delete objective;
		}
	}

}

Achievement::~Achievement() 
{
	for (u32 i = 0; i < m_objectives.size(); ++i)
		delete m_objectives.at(i);
	m_objectives.clear();
}

void Achievement::MakeProgress(u32 objectiveId, u32 value)
{
	for (u32 i = 0; i < m_objectives.size(); ++i)
	{
		if (!m_objectives[i]->IsComplete() && m_objectives[i]->GetID() == objectiveId)
		{
			m_objectives[i]->MakeProgress(value);
		}
	}
	if (IsComplete())
	{
		SAchievementEvent e(SAchievementEvent::kEvent_Achievement_AchievementComplete, objectiveId, 0);
		GetGame()->FireEvent(&e);
	}
}

//MARK: - AchievementManager
AchievementManager::AchievementManager()
{
	GetGame()->RegisterEventListener(SAchievementEvent::kEvent_Achievement_GameNotification, this, &AchievementManager::OnEvent);
	GetGame()->RegisterEventListener(SAchievementEvent::kEvent_Achievement_AchievementProgress, this, &AchievementManager::OnEvent);
	GetGame()->RegisterEventListener(SAchievementEvent::kEvent_Achievement_AchievementComplete, this, &AchievementManager::OnEvent);
}

AchievementManager::~AchievementManager()
{
	CleanUp();
}

ErrorCode AchievementManager::Init(const char filename[])
{
	char msg[kStrLen_Huge];

	if (!filename)
	{
		snprintf(msg, kStrLen_Huge, "Cannot load achievements from an empty filename.", filename);
		GetGame()->GetBlackBox()->Log("SYSTEM", 0, msg);
		return kErrorCode_InvalidData;
	}

	Json::Value jRoot;
	Json::Reader jReader;
	
	std::ifstream datafile(filename, std::ifstream::binary);
	if (!jReader.parse(datafile, jRoot))
	{
		snprintf(msg, kStrLen_Huge, "There was an error parsing the achievements data file.");
		GetGame()->GetBlackBox()->Log("SYSTEM", 0, msg);
		return kErrorCode_InvalidData;
	}

	Json::Value achievements = jRoot["achievements"];
	if (achievements.size() == 0)
	{
		snprintf(msg, kStrLen_Huge, "There were no achievements found in the achievements data file");
		GetGame()->GetBlackBox()->Log("SYSTEM", 0, msg);
		return kErrorCode_InvalidData;
	}

#ifdef DEBUG
	snprintf(msg, kStrLen_Huge, "Loading achievements from '%s'.", filename);
	GetGame()->GetBlackBox()->Log("DEBUG", 0, msg);
#endif

	// declare a flag, true if there was a problem loading the achievement data
	bool isSuccess = true;

	for (u32 i = 0; i < achievements.size(); ++i)
	{
		Achievement *achievement = new Achievement(achievements[i]);
		if (achievement->IsValid())
			m_achievements.push_back(achievement);
		else
		{
			snprintf(msg, kStrLen_Huge, "There was a problem with the achievement at index %u.", i);
			GetGame()->GetBlackBox()->Log("SYSTEM", 0, msg);
			delete achievement;
			isSuccess = false;
		}
	}

	snprintf(msg, kStrLen_Huge, "Achievements loaded, %s.", isSuccess ? "successfully" : "unsuccessfully");
	GetGame()->GetBlackBox()->Log("SYSTEM", 0, msg);

	return (isSuccess ? kErrorCode_Success : KErrorCode_SoftFailure);
}

bool AchievementManager::OnEvent(Event *e)
{
	printf("Achievementmanager::OnEvent | ");

	SAchievementEvent *ae = (SAchievementEvent*)e;
	switch (ae->m_type)
	{
		case SAchievementEvent::kEvent_Achievement_GameNotification:
		{
			printf("kEvent_Achievement_GameNotification\n");
			for (u32 i = 0; i < m_achievements.size(); ++i)
			{
				if (!m_achievements[i]->IsComplete())
				{
					m_achievements[i]->MakeProgress(ae->m_id, ae->m_value);
				}
			}
			break;
		}

		case SAchievementEvent::kEvent_Achievement_AchievementProgress:
		{
			printf("kEvent_Achievement_AchievementProgress\n");
			break;
		}

		case SAchievementEvent::kEvent_Achievement_AchievementComplete:
		{
			printf("kEvent_Achievement_AchievementComplete\n");
			break;
		}

		default:
			break;
	}
	return false;
}

bool AchievementManager::FireEvent(Event *e)
{
	if (IEventHandler::FireEvent(e) == false)
	{
		printf("handling it mahself yo\n");
	}
	return true;
}

void AchievementManager::CleanUp()
{
	GetGame()->DeRegisterEventListener(SAchievementEvent::kEvent_Achievement_GameNotification, this, &AchievementManager::OnEvent);
	GetGame()->DeRegisterEventListener(SAchievementEvent::kEvent_Achievement_AchievementProgress, this, &AchievementManager::OnEvent);
	GetGame()->DeRegisterEventListener(SAchievementEvent::kEvent_Achievement_AchievementComplete, this, &AchievementManager::OnEvent);

	for (u32 i = 0; i < m_achievements.size(); ++i)
		delete m_achievements.at(i);
	m_achievements.clear();
}


};