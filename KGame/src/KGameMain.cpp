
#include "global.h"

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768

class Fixme : public n0::IEventListener
{
public:
	Fixme() {}
	~Fixme() {}
	bool OnEvent(n0::n0Event *_evt) 
	{
		n0::SMouseEvent * pEvt = (n0::SMouseEvent *)_evt;
		n0::SMouseEventData * pEvtData = (n0::SMouseEventData *)pEvt->pData;

		printf("Mouse Click at %d,%d\n",pEvtData->x, pEvtData->y);
		return true;
	}

};

int main()
{

	int bitDepth = 24;
	int screenW = WIN_WIDTH;
	int screenH = WIN_HEIGHT;
	n0::windows::InitSystem(NULL,screenW,screenH);

	n0::SetFrameRate(30);

	n0::n0Texture * pTex = n0::n0TextureManager::GetInstance()->GenerateTexture(1,256,256);
	n0::n0InputEvents::GetInstance()->RegisterInputEvent(n0::SMouseEvent::kEvent_LeftMBDown,0,"TargetClick",NULL);
	n0::n0InputEvents::GetInstance()->RegisterEventListener(Hash("TargetClick"),new Fixme(),&Fixme::OnEvent,Hash("fixMeEvent"));

	while(! n0::windows::UserQuitMsg())
	{
		n0::StartFrame();

		n0::DrawTexturedRect(200,200,400,400);
		// draw the UI

		n0::EndFrame();
	}

	return 0;

}


int  APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	n0::windows::SetHInstance(hInstance);
	int bitDepth = 24;
	int screenW = WIN_WIDTH;
	int screenH = WIN_HEIGHT;

	if(n0::InitGraphics(screenW,screenH,bitDepth))
	{
		// audio engine
		//		irrklang::ISoundEngine * pSoundEngine = irrklang::createIrrKlangDevice();

		n0::n0Texture * pTex = n0::n0TextureManager::GetInstance()->GenerateTexture(1,256,256);
		n0::n0InputEvents::GetInstance()->RegisterInputEvent(n0::SMouseEvent::kEvent_LeftMBDown,0,"TargetClick",NULL);
		n0::n0InputEvents::GetInstance()->RegisterEventListener(Hash("TargetClick"),new Fixme(),&Fixme::OnEvent,Hash("fixMeEvent"));


		// 		if (pSoundEngine)
		// 			pSoundEngine->play2D("IsAnyoneThere.mp3");

		//MARK: GAME LOOP
		while(!n0::windows::UserQuitMsg())
		{
			//Do stuff in here
			n0::StartFrame();

			pTex->Bind();
			n0::DrawTexturedRect(200,200,400,400);
			// draw the UI

			n0::EndFrame();

		}

		//MARK: CLEAN UP
		n0::windows::CleanUp(true);
	}
	else
	{
		n0::windows::CleanUp(false);
		return 1;
	}

	return 0;
}


u32 Hash(const char *inputStr)
{
	if(!inputStr)
		return 0;

	const char* str = inputStr;
	u32 hashVal = BASEHASH;

	while(*str)
	{
		hashVal = ((hashVal << 5) + hashVal) + (u32)*str;
		str++;
	}

	return hashVal;
}
