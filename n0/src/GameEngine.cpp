
#include "fwInternal.h"

GameEngine * GameEngine::s_pInstance = NULL;

GameEngine::GameEngine() :
	 m_pDevice(NULL)
	,m_pDriver(NULL)
	,m_pSceneManager(NULL)
	,m_pGUIEnvironment(NULL)
//	,m_pParticleSystem(NULL)
	,m_pBlackBox(NULL)
	,m_pInputReceiver(NULL)
	,m_pGameConfig(NULL)
	,m_pDelayTimer(NULL)
	,m_bShouldQuit(false)
	,m_pAchievementManager(NULL)
	,m_pTextRenderer(NULL)
	,m_pSoundEngine(NULL)
#ifdef DEBUG
	,m_bDebugRender(false)
#endif
{
}

GameEngine * GameEngine::Create()
{
	if (s_pInstance == NULL)
	{
		s_pInstance = NEW GameEngine();
	}
	return s_pInstance;
}

GameEngine * GameEngine::GetInstance()
{
	if (s_pInstance == NULL)
	{
		Create();
	}
	return s_pInstance;
}

ErrorCode GameEngine::Destroy()
{
	if (s_pInstance)
	{
		SAFE_DELETE(s_pInstance);
		return kErrorCode_Success;
	}
	return kErrorCode_NotFound;
}

GameEngine * GetGame() { return GameEngine::GetInstance(); }

ErrorCode GameEngine::Init()
{
	m_pGameConfig = NEW GameConfig();
	if (!m_pGameConfig)
		return kErrorCode_BadAllocation;
	m_pGameConfig->Load();

	m_pBlackBox = NEW blackbox::BlackBox(m_pGameConfig->GetBlackboxConfigFilename());
	if (!m_pBlackBox)
		return kErrorCode_BadAllocation;

	m_pBlackBox->Log("System",5,"GameEngine Initialize");
	m_pDelayTimer = NEW fwDelayTimer<MAXDELAYS>();

	m_pInputReceiver = NEW InputReceiver();
	if (!m_pInputReceiver)
	{
		m_pBlackBox->Log("System", 0, "Error creating m_pInputReceiver");
		return kErrorCode_BadAllocation;
	}

// 	m_aiController = NEW AiController();
// 	if(!m_aiController)
// 	{
// 		m_pBlackBox->Log("System", 0, "Error creating m_aiController");
// 		return kErrorCode_BadAllocation;
// 	}
// 	ErrorCode ec = LoadTeam();
// 	if(ec != kErrorCode_Success)
// 	{
// 		m_pBlackBox->Log("System", 0, "Error creating Team information");
// 		return ec;
// 	}
	m_pInputReceiver->RegisterEventListener(SInputEvent::kEvent_InputQuit_Up,this,&GameEngine::OnQuit);

	m_pDevice = irr::createDevice(m_pGameConfig->GetDeviceDriverType(),
								  m_pGameConfig->GetWindowDimensions(),
								  m_pGameConfig->GetBitDepth(),
								  m_pGameConfig->GetIsFullscreen(),
								  m_pGameConfig->GetUseStencilBuffer(),
								  m_pGameConfig->GetUseVSync(),
								  m_pInputReceiver);
	if (!m_pDevice)
	{
		m_pBlackBox->Log("System", 0, "Error creating m_pDevice");
		return kErrorCode_BadAllocation;
	}
	
	m_pSoundEngine = irrklang::createIrrKlangDevice();
	if (!m_pSoundEngine)
	{
		m_pBlackBox->Log("SYSTEM", 0, "Error creating m_pSoundEngine");
	}

	const bool joystickSupport = m_pDevice->activateJoysticks(m_JoystickInfo);

	if(joystickSupport)
	{
		std::cout << "Joystick support is enabled and " << m_JoystickInfo.size() << " joystick(s) are present." << std::endl;
		for (irr::u32 joystick = 0; joystick < m_JoystickInfo.size(); ++joystick)
		{
			m_pInputReceiver->SetActiveJoytickProfile(Hash(m_JoystickInfo[joystick].Name.c_str()));
			std::cout << "Joystick " << joystick << ":" << std::endl;
			std::cout << "\tName: '" << m_JoystickInfo[joystick].Name.c_str() << "'" << std::endl;
			std::cout << "\tHash: " << Hash(m_JoystickInfo[joystick].Name.c_str()) << std::endl;
			std::cout << "\tAxes: " << m_JoystickInfo[joystick].Axes << std::endl;
			std::cout << "\tButtons: " << m_JoystickInfo[joystick].Buttons << std::endl;
			std::cout << "\tHat is: ";

			switch(m_JoystickInfo[joystick].PovHat)
			{
			case irr::SJoystickInfo::POV_HAT_PRESENT:
				std::cout << "present" << std::endl;
				break;
			case irr::SJoystickInfo::POV_HAT_ABSENT:
				std::cout << "absent" << std::endl;
				break;
			case irr::SJoystickInfo::POV_HAT_UNKNOWN:
			default:
				std::cout << "unknown" << std::endl;
				break;
			}
		}
	}
	else
	{
		std::cout << "Joystick support is not enabled." << std::endl;
	}

	//TODO: 
	m_pInputReceiver->LoadProfile("");

	m_pTextRenderer = new TextRenderer(m_pDevice);
	if (!m_pTextRenderer)
	{
		m_pBlackBox->Log("System", 0, "Error creating m_pTextRenderer");
		return kErrorCode_BadAllocation;
	}

// 	m_pChatManager = new ChatManager();
// 	if (!m_pChatManager)
// 	{
// 		m_pBlackBox->Log("System", 0, "Error creating m_pChatManager");
// 		return kErrorCode_BadAllocation;
// 	}
// 
// 	m_pQuestManger = new QuestManager();
// 	if (!m_pQuestManger)
// 	{
// 		m_pBlackBox->Log("System", 0, "Error creating m_pQuestManger");
// 		return kErrorCode_BadAllocation;
// 	}
//
// 	m_pParticleSystem = m_pSceneManager->addParticleSystemSceneNode(false);
// 	if (!m_pParticleSystem)
// 	{
// 		m_pBlackBox->Log("System", 0, "Error creating m_pParticleSystem");
// 		return kErrorCode_BadAllocation;
// 	}

	m_pAchievementManager = new AchievementManager();
	if (!m_pAchievementManager)
	{
		m_pBlackBox->Log("System", 0, "Error creating m_pAchievementManager");
		return kErrorCode_BadAllocation;
	}

	m_pDriver = m_pDevice->getVideoDriver();
	if (!m_pDriver)
	{
		m_pBlackBox->Log("System", 0, "Error creating m_pDriver");
		return kErrorCode_BadAllocation;
	}

	m_pSceneManager = m_pDevice->getSceneManager();
	if (!m_pSceneManager)
	{
		m_pBlackBox->Log("System", 0, "Error creating m_pSceneManager");
		return kErrorCode_BadAllocation;
	}

	m_pGUIEnvironment = m_pDevice->getGUIEnvironment();
	if (!m_pGUIEnvironment)
	{
		m_pBlackBox->Log("System", 0, "Error creating m_pGUIEnvironment");
		return kErrorCode_BadAllocation;
	}

	m_PreviousFrameTime = m_pDevice->getTimer()->getTime();
	m_pDriver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT);

	RegisterEventListener(SSceneEvent::kEvent_SceneDestroyed,this,&GameEngine::OnSceneDestroyed);
	srand ( m_pDevice->getTimer()->getRealTime());
	m_pBlackBox->Log("System",5,"GameEngine Initialize Complete");
	return kErrorCode_Success;
}

ErrorCode GameEngine::Tick()
{
	ASSERT(m_pInputReceiver);
	ASSERT(m_pDevice);

	if (m_bShouldQuit)
		return kErrorCode_Quit;

	if (!m_pDevice->run())
		return kErrorCode_Quit;

	// time and frame rate calculations
	const irr::u32 tickBeginTime = m_pDevice->getTimer()->getTime();
	const irr::u32 frameDeltaTime = tickBeginTime - m_PreviousFrameTime;
    m_PreviousFrameTime = tickBeginTime;
	/*
	if (m_pInputReceiver->IsKeyDown(irr::KEY_KEY_L))
	{
		char temp[1024] = {'\0'};
		snprintf(temp, 1024, "frameDeltaTime = %u", frameDeltaTime);
		m_pBlackBox->Log("DEBUG", 0, temp);
	}
	*/
	// change the window's caption; show current frame rate only if it was different from last frame
    const int currentFPS = m_pDriver->getFPS();
    if (m_PreviousFPS != currentFPS)
    {
        irr::core::stringw tmp(L"framewerks - Irrlicht Engine [");
        tmp += m_pDriver->getName();
        tmp += L"] fps: ";
        tmp += currentFPS;

        m_pDevice->setWindowCaption(tmp.c_str());
        m_PreviousFPS = currentFPS;
    }
	//Update Timers
	m_pDelayTimer->Update(frameDeltaTime);
	ProcessEvents();
	//
	//Update Scenes
	std::list<IUpdateable*>::iterator updateIt = m_UpdateStack.begin();
	for(bool error = false; !error && updateIt != m_UpdateStack.end(); ++updateIt)
	{
		(*updateIt)->Update(frameDeltaTime);
	}

	// BEGIN SCENE
	//============================================================
	m_pDriver->beginScene(true, true, irr::video::SColor(255,128,0,0));

	m_pSceneManager->drawAll();
	m_pGUIEnvironment->drawAll();

	std::list<IDrawable*>::iterator drawIt = m_DrawStack.begin();
	for(bool error = false; !error && drawIt != m_DrawStack.end(); ++drawIt)
	{
		m_pTextRenderer->Begin();
		(*drawIt)->Draw();
		m_pTextRenderer->End();
	}
/*
	irr::core::position2d<irr::s32> m = m_pDevice->getCursorControl()->getPosition();
	m_pDriver->draw2DRectangle(irr::video::SColor(100,255,255,255),
		irr::core::rect<irr::s32>(m.X-20, m.Y-20, m.X+20, m.Y+20));
*/
	m_pDriver->endScene();
	//============================================================
	// END SCENE

	//Update sceneReferences
	std::list<Scene*>::iterator sceneIt = m_sceneList.begin();
	while(sceneIt != m_sceneList.end())
	{
		if(!(*sceneIt)->IsAlive())
		{	
			delete *sceneIt;
			sceneIt = m_sceneList.erase(sceneIt);
		}
		else
		{
			++sceneIt;
		}
	}

	// frame rate limiting calculations
	const irr::u32 frameDuration = 1000 / m_pGameConfig->GetFramerate();
	if (frameDuration > 0) // 0 means no limit
	{
		const irr::u32 tickEndTime = m_pDevice->getTimer()->getTime();
		ASSERT(tickBeginTime >= tickEndTime);
		const irr::u32 tickDuration = tickEndTime - tickBeginTime;
		if (tickDuration < frameDuration)
			m_pDevice->sleep(frameDuration - tickDuration);
	}

	return kErrorCode_Success;
}

void GameEngine::CleanUp()
{
	Scene *pScene = NULL;	
	while(!m_sceneList.empty())
	{
		pScene = m_sceneList.front();
		SAFE_DELETE(pScene);
		m_sceneList.pop_front();
	}
	m_sceneList.clear();
	if (m_pDevice)
		m_pDevice->drop();
	if (m_pBlackBox)
		m_pBlackBox->Log("System",5,"GameEngine ShutDown");
	SAFE_DELETE(m_pBlackBox); //TODO: should BlackBox be shutdown nearer to the end to allow catching shutdown messages?
	SAFE_DELETE(m_pInputReceiver);
	SAFE_DELETE(m_pGameConfig);
// 	SAFE_DELETE(m_pQuestManger);
// 	SAFE_DELETE(m_pChatManager);
	if (m_pTextRenderer)
		m_pTextRenderer->CleanUp();
	SAFE_DELETE(m_pTextRenderer);
	if (m_pAchievementManager)
		m_pAchievementManager->CleanUp();
	SAFE_DELETE(m_pAchievementManager);
	if (m_pSoundEngine)
		m_pSoundEngine->drop();
}

/*
void GameEngine::CreateScene(u32 sceneType, u32 sceneName)
{
	Scene *pScene = NULL;
	if(sceneType == GameScene::GetSceneType())
	{
		pScene = new GameScene(sceneName);
	}
	else if (sceneType == SplashScene::GetSceneType())
	{
		pScene = new SplashScene(sceneName);
	}
	else if (sceneType == MainMenuScene::GetSceneType())
	{
		pScene = new MainMenuScene(sceneName);
	}
	else if (sceneType == ChatScene::GetSceneType())
	{
		pScene = new ChatScene(sceneName);
	}
	else if (sceneType == RageScene::GetSceneType())
	{
		pScene = new RageScene(sceneName);
	}
	else if (sceneType == CreditsScene::GetSceneType())
	{
		pScene = new CreditsScene(sceneName);
	}
	else if (sceneType == SummaryScene::GetSceneType())
	{
		pScene = new SummaryScene(sceneName);
	}


	if(pScene)
	{
		pScene->Init(m_pDevice);
	}
}
*/

Scene * GameEngine::GetScene(u32 sceneName)
{
	Scene *ret = NULL;
	std::list<Scene*>::iterator it;
	for(it = m_sceneList.begin();!ret && it != m_sceneList.end();it++)
	{
		if((*it)->GetSceneName() == sceneName)
		{
			ret = (*it);
		}
	}
	return ret;
}

bool GameEngine::OnSceneDestroyed(Event *e)
{
	if(!e)
		return false;
	SSceneEvent *sceneEvent = (SSceneEvent *)e;
	if(sceneEvent->m_type == SSceneEvent::kEvent_SceneDestroyed)
	{
		m_sceneList.remove((Scene*)sceneEvent->pData);
		delete (Scene*)sceneEvent->pData;
		return true;
	}
	return false;
}

bool GameEngine::OnQuit(Event *evt)
{
	if(evt->m_type == SInputEvent::kEvent_InputQuit_Up)
	{ 
		m_bShouldQuit = true;
	}
	return m_bShouldQuit; 
}

/*
ErrorCode GameEngine::LoadTeam()
{

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError error = doc.LoadFile("assets/teamList.xml");

	// if file load was successful
	if (error == tinyxml2::XML_SUCCESS)
	{
		// root node
		const tinyxml2::XMLNode * libraryNode = doc.FirstChildElement("Team");
		if (libraryNode)
		{
			const tinyxml2::XMLNode * unitNode = libraryNode->FirstChildElement("Unit");
			while (unitNode)
			{
	
				//TODO: the following nodes need proper error checking

				const tinyxml2::XMLNode * classNode = unitNode->FirstChildElement("Class")->FirstChild();
				const tinyxml2::XMLNode * nameNode = unitNode->FirstChildElement("Name")->FirstChild();
				const tinyxml2::XMLNode * portraitNode = unitNode->FirstChildElement("Portrait")->FirstChild();
				const tinyxml2::XMLNode * tex1Node = unitNode->FirstChildElement("Tex1")->FirstChild();
				const tinyxml2::XMLNode * tex2Node = unitNode->FirstChildElement("Tex2")->FirstChild();
				const tinyxml2::XMLNode * modelNode = unitNode->FirstChildElement("Model")->FirstChild();
				const tinyxml2::XMLNode * speedNode = unitNode->FirstChildElement("Speed")->FirstChild();
				const tinyxml2::XMLNode * rangeNode = unitNode->FirstChildElement("Range")->FirstChild();
				const tinyxml2::XMLNode * healthNode = unitNode->FirstChildElement("Health")->FirstChild();
				const tinyxml2::XMLNode * damageNode = unitNode->FirstChildElement("Damage")->FirstChild();
				const tinyxml2::XMLNode * moveNode = unitNode->FirstChildElement("Move")->FirstChild();
				if (!classNode || !nameNode || !portraitNode || !tex1Node ||!tex2Node ||  !modelNode || !speedNode || !rangeNode || !healthNode || !damageNode || !moveNode )
				{
					continue;
				}
				u32 type = Hash(classNode->Value());
				u32 name = Hash(nameNode->Value());
				char portrait[kStrLen_Medium]; std::strcpy(portrait,portraitNode->Value());
				char tex1[kStrLen_Medium]; strcpy(tex1,tex1Node->Value());
				char tex2[kStrLen_Medium]; strcpy(tex2,tex1Node->Value());
				char model[kStrLen_Medium]; std::strcpy(model,modelNode->Value());
				float speed = std::atof(speedNode->Value());
				float range = std::atof(rangeNode->Value());
				float health = std::atof(healthNode->Value());
				float damage = std::atof(damageNode->Value());
				float move = std::atof(moveNode->Value());
				
				PlayerObject * pUnit = new PlayerObject();
				
				pUnit->Init(type,name,portrait,tex1,tex2,model,speed,range,health,damage,move);
				m_unitList.push_back(pUnit);

				unitNode = unitNode->NextSiblingElement("Unit");
			}
		
		}
	}
	// file not found (or some other error)
	else
	{
		return kErrorCode_NotFound;
	}
	return kErrorCode_Success;
}
*/