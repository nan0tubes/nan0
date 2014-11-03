
#include "global.h"

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768



int main()
{

	int bitDepth = 24;
	int screenW = WIN_WIDTH;
	int screenH = WIN_HEIGHT;
	n0::windows::InitSystem(NULL,screenW,screenH);

	n0::SetFrameRate(30);
	GameEvents *evtListener = new GameEvents();
	n0::n0Texture * pTex = n0::n0TextureManager::GetInstance()->GenerateTexture(1,256,256);

	while(! n0::windows::UserQuitMsg())
	{
		n0::StartFrame();

		n0::DrawTexturedRect(200,200,400,400);
		// draw the UI

		n0::EndFrame();
	}
	delete evtListener;
	return 0;

}


int  APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	n0::windows::SetHInstance(hInstance);
	int bitDepth = 24;
	int screenW = WIN_WIDTH;
	int screenH = WIN_HEIGHT;

	GameEvents *evtListener = new GameEvents();
	if(n0::InitGraphics(screenW,screenH,bitDepth))
	{
		// audio engine
		//		irrklang::ISoundEngine * pSoundEngine = irrklang::createIrrKlangDevice();

		n0::n0Texture * pTex = n0::n0TextureManager::GetInstance()->GenerateTexture(1,256,256);


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
	delete evtListener;
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
		hashVal = (hashVal << 5) + (u32)*str;
		str++;
	}

	return hashVal;
}
