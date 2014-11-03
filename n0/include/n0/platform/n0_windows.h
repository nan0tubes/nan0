
#ifndef __N0_WINDOWS_H__
#define __N0_WINDOWS_H__

#define n0_WIN32
#define N0_SIMPLE_MUTEX
#include "windows.h"
#include <tchar.h>

#include "GLES2\gl2.h"
#include "GLES2\gl2ext.h"

#include "EGL\egl.h"
#include "EGL\eglext.h"

// Windows class name to register
#define	WINDOW_CLASS_NAME _T("n0EngineClass")

// Name of the application
#define APPLICATION_NAME _T("n0 Game")

// Title to display for errors.
#define ERROR_TITLE _T("n0 Error")

namespace n0
{
	class n0Texture;

/*******************************************************************************************************************************************
 Global variables
*******************************************************************************************************************************************/
/*******************************************************************************************************************************************
 Helper Functions
*******************************************************************************************************************************************/
	namespace windows {
		void SetHInstance(HINSTANCE appInstance);
		bool InitSystem(HINSTANCE applicationInstance, int width, int height);
		LRESULT CALLBACK HandleWindowMessages(HWND nativeWindow, UINT message, WPARAM windowParameters, LPARAM longWindowParameters);

		bool TestEGLError(HWND nativeWindow, const char* functionLastCalled);
		bool TestGLError(HWND nativeWindow, const char* functionLastCalled);

		bool CreateWindowAndDisplay( HINSTANCE applicationInstance, HWND &nativeWindow, HDC &deviceContext );
		bool CreateEGLDisplay( HDC deviceContext, EGLDisplay &eglDisplay );
		bool ChooseEGLConfig( EGLDisplay eglDisplay, EGLConfig& eglConfig ) ;
		bool CreateEGLSurface( HWND nativeWindow, EGLDisplay eglDisplay, EGLConfig eglConfig, EGLSurface& eglSurface) ;
		bool SetupEGLContext( EGLDisplay eglDisplay, EGLConfig eglConfig, EGLSurface eglSurface, EGLContext& eglContext, HWND nativeWindow ) ;
		void ReleaseWindowAndDisplay(HWND nativeWindow, HDC deviceContext) ;
		void ReleaseEGLState(EGLDisplay eglDisplay) ;
		bool UserQuitMsg();
		
		void CleanUp(bool didInit);
	}
	bool InitialiseBuffers(GLuint &vertexBuffer, HWND nativeWindow ) ;\
	bool InitialiseShaders( GLuint &fragmentShader, GLuint &vertexShader, GLuint &shaderProgram, HWND nativeWindow ) ;
	void DeInitialiseGLState( GLuint fragmentShader, GLuint vertexShader, GLuint shaderProgram, GLuint vertexBuffer ) ;

	bool StartFrame();
	double GetTicks(); // Get number of seconds of the last frame.
	void SetFrameRate(u32 frameRate); // used to limit Framerate of the game.
	void DrawRect(float x, float y, float w, float h, Colour4f colour);
	void DrawRect(float x, float y, float w, float h, Colour4f colourNW, Colour4f colourNE, Colour4f colourSE, Colour4f colourSW);
	void DrawLine(float x1, float y1, float x2, float y2, Colour4f colour);
	void DrawLine(float x1, float y1, float x2, float y2, Colour4f colour1, Colour4f colour2);

	void DrawTexturedRect(float x, float y, float w, float h);
	void DrawTexturedRect(float x, float y, float w, float h, float u1, float v1, float u2, float v2);
	bool EndFrame();


}; // namespace nan0

#endif