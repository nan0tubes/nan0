#include "n0/n0.h"

namespace n0
{
	double frameRate = 60;
	ULONGLONG lastFrame = 0;
	double timeStamp = 0.16;
	// Handles for the two shaders used to draw the triangle, and the program handle which combines them.
	GLuint fragmentShader = 0, vertexShader = 0;
	GLuint shaderProgram = 0, textureShader = 0;

	// A vertex buffer object to store our model data.
	GLuint	vertexBuffer = 0;

	GLuint VERTEX_ARRAY = 0;
	GLuint COLOR_ARRAY= 1;

	GLuint UV_ARRAY = 2;
	GLuint TEX_UNI = 3;

	float *transformationMatrix;

	Vertex *vertexData;

	namespace windows
	{
		static HINSTANCE g_appInstance = NULL;
		static bool g_hasUserQuit = false;

		static GLuint windowWidth;
		static GLuint windowHeight;

		static HWND				nativeWindow = NULL;
		static HDC					deviceContext = NULL;

		// EGL variables
		static EGLDisplay			eglDisplay = NULL;
		static EGLConfig			eglConfig = NULL;
		static EGLSurface			eglSurface = NULL;
		static EGLContext			eglContext = NULL;

		
		void SetHInstance(HINSTANCE appInstance)
		{
			g_appInstance = appInstance;
		}

		LRESULT CALLBACK HandleWindowMessages(HWND nativeWindow, UINT message, WPARAM windowParameters, LPARAM longWindowParameters)
		{
			POINT pt; GetCursorPos(&pt); ScreenToClient(nativeWindow,&pt);
			switch (message)
			{
			case WM_SYSCOMMAND:
				// Handle 2 system messages: screen saving and monitor power. We need to prevent them whilst we're rendering for a short time.
				{
					switch (windowParameters)
					{
					case SC_SCREENSAVE:
					case SC_MONITORPOWER:
						{
							// Return 0 to let Windows know we don't want to sleep or turn the monitor off right now.
							return 0;
						}
					}
					break;
				}
			case WM_CLOSE:
				// Handle the close message when a user clicks the quit icon of the window
				{
					// Tell the demo that it should stop rendering.
					g_hasUserQuit = true;

					// Post a quit message
					PostQuitMessage(0);

					// Return 1 to let Windows know the message has been successfully handled
					return 1;
				}
			case WM_MBUTTONDOWN:
				{
					SMouseEventData data; data.x = pt.x; data.y = pt.y;
					SMouseEvent evt(SMouseEvent::kEvent_MiddleMBDown,&data);
					n0InputEvents::GetInstance()->OnEvent(&evt);
				}
				break;
			case WM_MBUTTONUP:
				{
					SMouseEventData data; data.x = pt.x; data.y = pt.y;
					SMouseEvent evt(SMouseEvent::kEvent_MiddleMBUp,&data);
					n0InputEvents::GetInstance()->OnEvent(&evt);
				}
				break;

			case WM_MOUSEMOVE:
				{
					SMouseEventData data; data.x = pt.x; data.y = pt.y;
					SMouseEvent evt(SMouseEvent::kEvent_MouseMove,&data);
					n0InputEvents::GetInstance()->OnEvent(&evt);
				}
				break;
			case WM_LBUTTONDOWN:
				{
					SMouseEventData data; data.x = pt.x; data.y = pt.y;
					SMouseEvent evt(SMouseEvent::kEvent_LeftMBDown,&data);
					n0InputEvents::GetInstance()->OnEvent(&evt);
				}
				break;
			case WM_LBUTTONUP:
				{
					SMouseEventData data; data.x = pt.x; data.y = pt.y;
					SMouseEvent evt(SMouseEvent::kEvent_LeftMBUp,&data);
					n0InputEvents::GetInstance()->OnEvent(&evt);
				}
				break;

			case WM_RBUTTONDOWN:
				{
					SMouseEventData data; data.x = pt.x; data.y = pt.y;
					SMouseEvent evt(SMouseEvent::kEvent_RightMBDown,&data);
					n0InputEvents::GetInstance()->OnEvent(&evt);
				}
				break;

			case WM_RBUTTONUP:
				{
					SMouseEventData data; data.x = pt.x; data.y = pt.y;
					SMouseEvent evt(SMouseEvent::kEvent_RightMBUp,&data);
					n0InputEvents::GetInstance()->OnEvent(&evt);
				}
				break;

			case WM_KEYDOWN:
				{
					u32 wasDown = (longWindowParameters & (1 << 29));
					SKeyEvent evt((wasDown != 0) ? SKeyEvent::kEvent_KeyRepeat : SKeyEvent::kEvent_KeyDown, windowParameters);
					n0InputEvents::GetInstance()->OnEvent(&evt);
				}
				break;
			case WM_KEYUP:
				{
					SKeyEvent evt(SKeyEvent::kEvent_KeyUp,windowParameters);
					n0InputEvents::GetInstance()->OnEvent(&evt);
				}
				break;
			}

			

			// Calls the default window procedure for messages we did not handle
			return DefWindowProc(nativeWindow, message, windowParameters, longWindowParameters);
		}

		/*!*****************************************************************************************************************************************
		 @Function		WinMain
		 @Input			applicationInstance         Application instance created by the Operating System
		 @Input			previousInstance            Always NULL
		 @Input			commandLineString           Command line string passed from the Operating System, ignored.
		 @Input			showCommand                 Specifies how the window is to be shown, ignored.
		 @Return		Result code to send to the Operating System
		 @Description	Main function of the program, executes other functions.
		*******************************************************************************************************************************************/
		bool  InitSystem(HINSTANCE applicationInstance, int width, int height)
		{
			// Windows variables
	
			windowWidth = width;
			windowHeight = height;

			float vtm[16] = {
			2.0f/(float)width,0,0.0f,0.0f,
			0,2.0f/(float)height,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			-1,-1,0.0f,1.0f };

			transformationMatrix = new float[16];
			memcpy(transformationMatrix,vtm,sizeof(vtm));

			// Setup the windowing system, getting a window and a display
			if (!windows::CreateWindowAndDisplay(applicationInstance, nativeWindow, deviceContext))
			{
				return false;
			}

			// Create and Initialise an EGLDisplay from the native display
			if (!windows::CreateEGLDisplay(deviceContext, eglDisplay))
			{
				return false;
			}

			// Choose an EGLConfig for the application, used when setting up the rendering surface and EGLContext
			if (!windows::ChooseEGLConfig(eglDisplay, eglConfig))
			{
				return false;
			}

			// Create an EGLSurface for rendering from the native window
			if (!windows::CreateEGLSurface(nativeWindow, eglDisplay, eglConfig, eglSurface))
			{
				return false;
			}

			// Setup the EGL Context from the other EGL constructs created so far, so that the application is ready to submit OpenGL ES commands
			if (!windows::SetupEGLContext(eglDisplay, eglConfig, eglSurface, eglContext, nativeWindow))
			{
				return false;
			}

			// Initialise the vertex data in the application
			if (!InitialiseBuffers(vertexBuffer, nativeWindow))
			{
				return false;
			}	
	
			// Initialise the fragment and vertex shaders used in the application

			if (!InitialiseShaders(fragmentShader, vertexShader, shaderProgram, nativeWindow))
			{
				return false;
			}

			// Init SDL
			if (SDL_Init(SDL_INIT_AUDIO) < 0)
			{
				n0_ASSERT(false, "SDL could not initialize! SDL Error: %s\v", SDL_GetError());
				return false;
			}
			// Init SDL_mixer
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				n0_ASSERT(false, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				return false;
			}

			return true;
		}

		/*!*****************************************************************************************************************************************
			@Function		TestEGLError
			@Input			nativeWindow                Handle to the window
			@Input			functionLastCalled          Function which triggered the error
			@Return		True if no EGL error was detected
			@Description	Tests for an EGL error and prints it in a message box.
		*******************************************************************************************************************************************/
		bool TestEGLError(HWND nativeWindow, const char* functionLastCalled)
		{
			/*	eglGetError returns the last error that occurred using EGL, not necessarily the status of the last called function. The user has to
				check after every single EGL call or at least once every frame. Usually this would be for debugging only, but for this example
				it is enabled always.
			*/
			EGLint lastError = eglGetError();
			if (lastError != EGL_SUCCESS)
			{
				TCHAR stringBuffer[256];
				_stprintf(stringBuffer, _T("%s failed (%x).\n"), functionLastCalled, lastError);
				MessageBox(nativeWindow, stringBuffer, ERROR_TITLE, MB_OK | MB_ICONEXCLAMATION);
				return false;
			}

			return true;
		}

		/*!*****************************************************************************************************************************************
			@Function		TestGLError
			@Input			nativeWindow                Handle to the window
			@Input			functionLastCalled          Function which triggered the error
			@Return		True if no EGL error was detected
			@Description	Tests for an EGL error and prints it in a message box.
		*******************************************************************************************************************************************/
		bool TestGLError(HWND nativeWindow, const char* functionLastCalled)
		{

			/*	glGetError returns the last error that occurred using OpenGL ES, not necessarily the status of the last called function. The user 
				has to check after every single OpenGL ES call or at least once every frame. Usually this would be for debugging only, but for this
				example it is enabled always
			*/
			GLenum lastError = glGetError();
			if (lastError != GL_NO_ERROR)
			{
				TCHAR stringBuffer[256];
				_stprintf(stringBuffer, _T("%s failed (%x).\n"), functionLastCalled, lastError);
				MessageBox(nativeWindow, stringBuffer, ERROR_TITLE, MB_OK | MB_ICONEXCLAMATION);
				return false;
			}

			return true;
		}

		/*******************************************************************************************************************************************
			Application Functions
		*******************************************************************************************************************************************/

		/*!*****************************************************************************************************************************************
			@Function		CreateWindowAndDisplay
			@Input			applicationInstance		    Specific instance of the application
			@Output		nativeWindow			    Native window type to create
			@Output		deviceContext			    Native device context to create
			@Return		Whether the function succeeded or not.
			@Description	Creates a native window and display for the application to render into.
		*******************************************************************************************************************************************/
		bool CreateWindowAndDisplay( HINSTANCE applicationInstance, HWND &nativeWindow, HDC &deviceContext ) 
		{
			// Describe the native window in a window class structure
			WNDCLASS nativeWindowDescription;
			nativeWindowDescription.style = CS_HREDRAW | CS_VREDRAW;
			nativeWindowDescription.lpfnWndProc = HandleWindowMessages;
			nativeWindowDescription.cbClsExtra = 0;
			nativeWindowDescription.cbWndExtra = 0;
			nativeWindowDescription.hInstance = applicationInstance;
			nativeWindowDescription.hIcon = 0;
			nativeWindowDescription.hCursor = 0;
			nativeWindowDescription.lpszMenuName = 0;
			nativeWindowDescription.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
			nativeWindowDescription.lpszClassName = WINDOW_CLASS_NAME;

			// Register the windows class with the OS.
			ATOM registerClass = RegisterClass(&nativeWindowDescription);
			if (!registerClass)
			{
				MessageBox(0, _T("Failed to register the window class"), ERROR_TITLE, MB_OK | MB_ICONEXCLAMATION);
			}

			// Create a rectangle describing the area of the window
			RECT windowRectangle;
			SetRect(&windowRectangle, 0, 0, windowWidth, windowHeight);
			AdjustWindowRectEx(&windowRectangle, WS_CAPTION | WS_SYSMENU, false, 0);

			// Create the window from the available information
			nativeWindow = CreateWindow( WINDOW_CLASS_NAME, APPLICATION_NAME, WS_VISIBLE | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 
											windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top,
											NULL, NULL, applicationInstance, NULL);
			if (!nativeWindow)
			{
				MessageBox(0, _T("Failed to create the window"), ERROR_TITLE, MB_OK|MB_ICONEXCLAMATION);
				return false;
			}

			// Get the associated device context from the window
			deviceContext = GetDC(nativeWindow);
			if (!deviceContext)
			{
				MessageBox(nativeWindow, _T("Failed to create the device context"), ERROR_TITLE, MB_OK|MB_ICONEXCLAMATION);
				return false;
			}

			return true;
		}

		/*!*****************************************************************************************************************************************
			@Function		CreateEGLDisplay
			@Input			deviceContext               The device context used by the application
			@Output		eglDisplay				    EGLDisplay created from deviceContext
			@Return		Whether the function succeeded or not.
			@Description	Creates an EGLDisplay from a native device context, and initialises it.
		*******************************************************************************************************************************************/
		bool CreateEGLDisplay( HDC deviceContext, EGLDisplay &eglDisplay ) 
		{
			/*	Get an EGL display.
				EGL uses the concept of a "display" which in most environments corresponds to a single physical screen. After creating a native
				display for a given windowing system, EGL can use this handle to get a corresponding EGLDisplay handle to it for use in rendering.
				Should this fail, EGL is usually able to provide access to a default display.
			*/
			eglDisplay = eglGetDisplay(deviceContext);
			if (eglDisplay == EGL_NO_DISPLAY)
			{
				eglDisplay = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY);
			}

			// If a display still couldn't be obtained, return an error.
			if (eglDisplay == EGL_NO_DISPLAY)
			{
				MessageBox(0, _T("Failed to get an EGLDisplay"), ERROR_TITLE, MB_OK | MB_ICONEXCLAMATION);
				return false;
			}

			/*	Initialize EGL.
				EGL has to be initialized with the display obtained in the previous step. All EGL functions other than eglGetDisplay 
				and eglGetError need an initialised EGLDisplay. 
				If an application is not interested in the EGL version number it can just pass NULL for the second and third parameters, but they 
				are queried here for illustration purposes.
			*/
			EGLint eglMajorVersion, eglMinorVersion;
			if (!eglInitialize(eglDisplay, &eglMajorVersion, &eglMinorVersion))
			{
				MessageBox(0, _T("Failed to initialise the EGLDisplay"), ERROR_TITLE, MB_OK | MB_ICONEXCLAMATION);
				return false;
			}

			return true;
		}

		/*!*****************************************************************************************************************************************
			@Function		ChooseEGLConfig
			@Input			eglDisplay                  The EGLDisplay used by the application
			@Output		eglConfig                   The EGLConfig chosen by the function
			@Return		Whether the function succeeded or not.
			@Description	Chooses an appropriate EGLConfig and return it.
		*******************************************************************************************************************************************/
		bool ChooseEGLConfig( EGLDisplay eglDisplay, EGLConfig& eglConfig ) 
		{
			/*	Specify the required configuration attributes.
				An EGL "configuration" describes the capabilities an application requires and the type of surfaces that can be used for drawing.
				Each implementation exposes a number of different configurations, and an application needs to describe to EGL what capabilities it
				requires so that an appropriate one can be chosen. The first step in doing this is to create an attribute list, which is an array
				of key/value pairs which describe particular capabilities requested. In this application nothing special is required so we can query
				the minimum of needing it to render to a window, and being OpenGL ES 2.0 capable.
			*/
			const EGLint configurationAttributes[] =
			{
				EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
				EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
				EGL_NONE
			};

			/*	Find a suitable EGLConfig
				eglChooseConfig is provided by EGL to provide an easy way to select an appropriate configuration. It takes in the capabilities
				specified in the attribute list, and returns a list of available configurations that match or exceed the capabilities requested.
				Details of all the possible attributes and how they are selected for by this function are available in the EGL reference pages here:
				http://www.khronos.org/registry/egl/sdk/docs/man/xhtml/eglChooseConfig.html
				It is also possible to simply get the entire list of configurations and use a custom algorithm to choose a suitable one, as many
				advanced applications choose to do. For this application however, taking the first EGLConfig that the function returns suits
				its needs perfectly, so we limit it to returning a single EGLConfig.
			*/
			EGLint configsReturned;
			if (!eglChooseConfig(eglDisplay, configurationAttributes, &eglConfig, 1, &configsReturned) || (configsReturned != 1))
			{
				MessageBox(0, _T("eglChooseConfig() failed."), ERROR_TITLE, MB_OK|MB_ICONEXCLAMATION);
				return false;
			}

			return true;
		}

		/*!*****************************************************************************************************************************************
			@Function		CreateEGLSurface
			@Input			nativeWindow                A native window that's been created
			@Input			eglDisplay                  The EGLDisplay used by the application
			@Input			eglConfig                   An EGLConfig chosen by the application
			@Output		eglSurface					The EGLSurface created from the native window.
			@Return		Whether the function succeeds or not.
			@Description	Creates an EGLSurface from a native window
		*******************************************************************************************************************************************/
		bool CreateEGLSurface( HWND nativeWindow, EGLDisplay eglDisplay, EGLConfig eglConfig, EGLSurface& eglSurface) 
		{
			/*	Create an EGLSurface for rendering.
				Using a native window created earlier and a suitable eglConfig, a surface is created that can be used to render OpenGL ES calls to.
				There are three main surface types in EGL, which can all be used in the same way once created but work slightly differently:
					- Window Surfaces  - These are created from a native window and are drawn to the screen.
					- Pixmap Surfaces  - These are created from a native windowing system as well, but are offscreen and are not displayed to the user.
					- PBuffer Surfaces - These are created directly within EGL, and like Pixmap Surfaces are offscreen and thus not displayed.
				The offscreen surfaces are useful for non-rendering contexts and in certain other scenarios, but for most applications the main
				surface used will be a window surface as performed below.
			*/
			eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, nativeWindow, NULL);
			if(eglSurface == EGL_NO_SURFACE)
			{
				eglGetError(); // Clear error
				eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, NULL, NULL);
			}

			// Check for any EGL Errors
			if (!TestEGLError(nativeWindow, "eglCreateWindowSurface"))
			{
				return false;
			}

			return true;
		}

		/*!*****************************************************************************************************************************************
			@Function		SetupEGLContext
			@Input			eglDisplay                  The EGLDisplay used by the application
			@Input			eglConfig                   An EGLConfig chosen by the application
			@Input			eglSurface					The EGLSurface created from the native window.
			@Output		eglContext                  The EGLContext created by this function
			@Input			nativeWindow                A native window, used to display error messages
			@Return		Whether the function succeeds or not.
			@Description	Sets up the EGLContext, creating it and then installing it to the current thread.
		*******************************************************************************************************************************************/
		bool SetupEGLContext( EGLDisplay eglDisplay, EGLConfig eglConfig, EGLSurface eglSurface, EGLContext& eglContext, HWND nativeWindow ) 
		{
			/*	Create a context.
				EGL has to create what is known as a context for OpenGL ES. The concept of a context is OpenGL ES's way of encapsulating any
				resources and state. What appear to be "global" functions in OpenGL actually only operate on the current context. A context
				is required for any operations in OpenGL ES.
				Similar to an EGLConfig, a context takes in a list of attributes specifying some of its capabilities. However in most cases this
				is limited to just requiring the version of the OpenGL ES context required - In this case, OpenGL ES 2.0.
			*/
			EGLint contextAttributes[] = 
			{
				EGL_CONTEXT_CLIENT_VERSION, 2, 
				EGL_NONE
			};

			// Create the context with the context attributes supplied
			eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, contextAttributes);
			if (!TestEGLError(nativeWindow, "eglCreateContext"))
			{
				return false;
			}

			/*	Make OpenGL ES the current API.
				After creating the context, EGL needs a way to know that any subsequent EGL calls are going to be affecting OpenGL ES,
				rather than any other API (such as OpenVG).
			*/
			eglBindAPI(EGL_OPENGL_ES_API);
			if (!TestEGLError(nativeWindow, "eglBindAPI"))
			{
				return false;
			}

			/*	Bind the context to the current thread.
				Due to the way OpenGL uses global functions, contexts need to be made current so that any function call can operate on the correct
				context. Specifically, make current will bind the context to the thread it's called from, and unbind it from any others. To use
				multiple contexts at the same time, users should use multiple threads and synchronise between them.
			*/
			eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
			if (!TestEGLError(nativeWindow, "eglMakeCurrent"))
			{
				return false;
			}

			return true;
		}
		
		void CleanUp(bool didInit)
		{

			Mix_Quit();
			SDL_Quit();

			if(didInit)
				DeInitialiseGLState(fragmentShader, vertexShader, shaderProgram, vertexBuffer);


			// Release the EGL State
			ReleaseEGLState(eglDisplay);

			// Release the windowing system resources
			ReleaseWindowAndDisplay(nativeWindow, deviceContext);

		}
		
		/*!*****************************************************************************************************************************************
		 @Function		ReleaseWindowAndDisplay
		 @Input			nativeWindow                The native window to release
		 @Input			deviceContext               The native display to release
		 @Description	Releases all resources allocated by the windowing system
		*******************************************************************************************************************************************/
		void ReleaseWindowAndDisplay(HWND nativeWindow, HDC deviceContext) 
		{
			// Release the device context.
			if (deviceContext)
			{
				ReleaseDC(nativeWindow, deviceContext);
			}

			// Destroy the window
			if (nativeWindow)
			{
				DestroyWindow(nativeWindow);
			}
		}

		bool UserQuitMsg()
		{
			return g_hasUserQuit;
		}

		/*!*****************************************************************************************************************************************
		 @Function		ReleaseEGLState
		 @Input			eglDisplay                   The EGLDisplay used by the application
		 @Description	Releases all resources allocated by EGL
		*******************************************************************************************************************************************/
		void ReleaseEGLState(EGLDisplay eglDisplay) 
		{
			// To release the resources in the context, first the context has to be released from its binding with the current thread.
			eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

			// Terminate the display, and any resources associated with it (including the EGLContext)
			eglTerminate(eglDisplay);
		}


	}; // namespace windows

bool InitialiseBuffers(GLuint &vertexBuffer, HWND nativeWindow ) 
{
	/*	Concept: Vertices
		When rendering a polygon or model to screen, OpenGL ES has to be told where to draw the object, and more fundamentally what shape 
		it is. The data used to do this is referred to as vertices, points in 3D space which are usually collected into groups of three 
		to render as triangles. Fundamentally, any advanced 3D shape in OpenGL ES is constructed from a series of these vertices - each 
		vertex representing one corner of a polygon.
	*/

	/*	Concept: Buffer Objects
		To operate on any data, OpenGL first needs to be able to access it. The GPU maintains a separate pool of memory it uses independent
		of the CPU. Whilst on many embedded systems these are in the same physical memory, the distinction exists so that they can use and
		allocate memory without having to worry about synchronising with any other processors in the device.
		To this end, data needs to be uploaded into buffers, which are essentially a reserved bit of memory for the GPU to use. By creating
		a buffer and giving it some data we can tell the GPU how to render a triangle.
	*/

	// Vertex data containing the positions of each point of the triangle
	
	vertexData = new Vertex[MAX_VERTEX];

	// Generate a buffer object
	glGenBuffers(1, &vertexBuffer);

	// Bind buffer as an vertex buffer so we can fill it with data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	
	/*	Set the buffer's size, data and usage
		Note the last argument - GL_STATIC_DRAW. This tells the driver that we intend to read from the buffer on the GPU, and don't intend
		to modify the data until we're done with it.		
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*MAX_VERTEX, vertexData, GL_DYNAMIC_DRAW);

	if (!windows::TestGLError(nativeWindow, "glBufferData"))
	{
		return false;
	}

	return true;
}

/*!*****************************************************************************************************************************************
 @Function		InitialiseShaders
 @Output		fragmentShader              Handle to a fragment shader
 @Output		vertexShader                Handle to a vertex shader
 @Output		shaderProgram               Handle to a shader program containing the fragment and vertex shader
 @Input			nativeWindow                A native window, used to display error messages
 @Return		Whether the function succeeds or not.
 @Description	Initialises shaders, buffers and other state required to begin rendering with OpenGL ES
*******************************************************************************************************************************************/
bool InitialiseShaders( GLuint &fragmentShader, GLuint &vertexShader, GLuint &shaderProgram, HWND nativeWindow ) 
{
	/*	Concept: Shaders
		OpenGL ES 2.0 uses what are known as shaders to determine how to draw objects on the screen. Instead of the fixed function
		pipeline in early OpenGL or OpenGL ES 1.x, users can now programmatically define how vertices are transformed on screen, what
		data is used where, and how each pixel on the screen is coloured.
		These shaders are written in GL Shading Language ES: http://www.khronos.org/registry/gles/specs/2.0/GLSL_ES_Specification_1.0.17.pdf
		which is usually abbreviated to simply "GLSL ES".
		Each shader is compiled on-device and then linked into a shader program, which combines a vertex and fragment shader into a form 
		that the OpenGL ES implementation can execute.
	*/

	/*	Concept: Fragment Shaders
		In a final buffer of image data, each individual point is referred to as a pixel. Fragment shaders are the part of the pipeline
		which determine how these final pixels are coloured when drawn to the framebuffer. When data is passed through here, the positions
		of these pixels is already set, all that's left to do is set the final colour based on any defined inputs.
		The reason these are called "fragment" shaders instead of "pixel" shaders is due to a small technical difference between the two
		concepts. When you colour a fragment, it may not be the final colour which ends up on screen. This is particularly true when 
		performing blending, where multiple fragments can contribute to the final pixel colour.
	*/
	const char* const fragmentShaderSource = "\
											 precision mediump float;\
											 varying vec4 outColor;\
											 \
											 void main (void)\
											 {\
												 gl_FragColor = outColor;\
											 }";

	// Create a fragment shader object
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Load the source code into it
	glShaderSource(fragmentShader, 1, (const char**)&fragmentShaderSource, NULL);

	// Compile the source code
	glCompileShader(fragmentShader);

	// Check that the shader compiled
	GLint isShaderCompiled;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isShaderCompiled);
	if (!isShaderCompiled)
	{
		// If an error happened, first retrieve the length of the log message
		int infoLogLength, charactersWritten;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		// Allocate enough space for the message and retrieve it
		char* infoLog = new char[infoLogLength];
		glGetShaderInfoLog(fragmentShader, infoLogLength, &charactersWritten, infoLog);



		delete[] infoLog;
		return false;
	}
	
	/*	Concept: Vertex Shaders
		Vertex shaders primarily exist to allow a developer to express how to orient vertices in 3D space, through transformations like 
		Scaling, Translation or Rotation. Using the same basic layout and structure as a fragment shader, these take in vertex data and 
		output a fully transformed set of positions. Other inputs are also able to be used such as normals or texture coordinates, and can 
		also be transformed and output alongside the position data.
	*/
	// Vertex shader code
	const char* const vertexShaderSource = "\
										   attribute vec4	myVertex;\
										   attribute vec4 inColor;\
										   \
										   uniform mediump mat4	transformationMatrix;\
										   \
										   varying vec4 outColor;\
										   void main(void)\
										   {\
										   outColor = inColor;\
										   gl_Position = transformationMatrix*myVertex;\
										   }";

	// Create a vertex shader object
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Load the source code into the shader
	glShaderSource(vertexShader, 1, (const char**)&vertexShaderSource, NULL);

	// Compile the shader
	glCompileShader(vertexShader);

	// Check the shader has compiled
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isShaderCompiled);
	if (!isShaderCompiled)
	{
		// If an error happened, first retrieve the length of the log message
		int infoLogLength, charactersWritten;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		// Allocate enough space for the message and retrieve it
		char* infoLog = new char[infoLogLength];
		glGetShaderInfoLog(vertexShader, infoLogLength, &charactersWritten, infoLog);

		// Display the error in a dialog box

		delete[] infoLog;
		return false;
	}

	// Create the shader program
	shaderProgram = glCreateProgram();

	// Attach the fragment and vertex shaders to it
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	
	glBindAttribLocation(shaderProgram,VERTEX_ARRAY,"myVertex");
	glBindAttribLocation(shaderProgram,COLOR_ARRAY,"inColor");
	// Link the program
	glLinkProgram(shaderProgram);
	

	// Check if linking succeeded in the same way we checked for compilation success
	GLint isLinked;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);
	if (!isLinked)
	{
		// If an error happened, first retrieve the length of the log message
		int infoLogLength, charactersWritten;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		// Allocate enough space for the message and retrieve it
		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(shaderProgram, infoLogLength, &charactersWritten, infoLog);


		delete[] infoLog;
		return false;
	}
	
	/*	Use the Program
		Calling glUseProgram tells OpenGL ES that the application intends to use this program for rendering. Now that it's installed into
		the current state, any further glDraw* calls will use the shaders contained within it to process scene data. Only one program can
		be active at once, so in a multi-program application this function would be called in the render loop. Since this application only
		uses one program it can be installed in the current state and left there.
	*/
	glUseProgram(shaderProgram);

	if (!windows::TestGLError(nativeWindow, "glUseProgram"))
	{
		return false;
	}

	const char* const fragmentTexShaderSource = "\
											 precision mediump float;\
											 varying vec4 outColor;\
											 varying vec2 outUV;\
											 uniform sampler2D myTex;\
											 \
											 void main (void)\
											 {\
												  gl_FragColor = texture2D(myTex, outUV);\
											 }";

	// Create a fragment shader object
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Load the source code into it
	glShaderSource(fragmentShader, 1, (const char**)&fragmentTexShaderSource, NULL);

	// Compile the source code
	glCompileShader(fragmentShader);

	// Check that the shader compiled
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isShaderCompiled);
	if (!isShaderCompiled)
	{
		// If an error happened, first retrieve the length of the log message
		int infoLogLength, charactersWritten;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		// Allocate enough space for the message and retrieve it
		char* infoLog = new char[infoLogLength];
		glGetShaderInfoLog(fragmentShader, infoLogLength, &charactersWritten, infoLog);



		delete[] infoLog;
		return false;
	}
	
	/*	Concept: Vertex Shaders
		Vertex shaders primarily exist to allow a developer to express how to orient vertices in 3D space, through transformations like 
		Scaling, Translation or Rotation. Using the same basic layout and structure as a fragment shader, these take in vertex data and 
		output a fully transformed set of positions. Other inputs are also able to be used such as normals or texture coordinates, and can 
		also be transformed and output alongside the position data.
	*/
	// Vertex shader code
	const char* const vertexTexShaderSource = "\
										   attribute vec4	myVertex;\
										   attribute vec4 inColor;\
										   attribute vec2 uv;\
										   \
										   uniform mediump mat4	transformationMatrix;\
										   \
										   varying vec4 outColor;\
										   varying vec2 outUV;\
										   void main(void)\
										   {\
										   outUV = uv;\
										   outColor = inColor;\
										   gl_Position = transformationMatrix*myVertex;\
										   }";

	// Create a vertex shader object
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Load the source code into the shader
	glShaderSource(vertexShader, 1, (const char**)&vertexTexShaderSource, NULL);

	// Compile the shader
	glCompileShader(vertexShader);

	// Check the shader has compiled
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isShaderCompiled);
	if (!isShaderCompiled)
	{
		// If an error happened, first retrieve the length of the log message
		int infoLogLength, charactersWritten;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		// Allocate enough space for the message and retrieve it
		char* infoLog = new char[infoLogLength];
		glGetShaderInfoLog(vertexShader, infoLogLength, &charactersWritten, infoLog);

		// Display the error in a dialog box

		delete[] infoLog;
		return false;
	}

	// Create the shader program
	textureShader = glCreateProgram();

	// Attach the fragment and vertex shaders to it
	glAttachShader(textureShader, fragmentShader);
	glAttachShader(textureShader, vertexShader);
	
	glBindAttribLocation(textureShader,VERTEX_ARRAY,"myVertex");
	glBindAttribLocation(textureShader,COLOR_ARRAY,"inColor");
	glBindAttribLocation(textureShader,UV_ARRAY,"uv");
	// Link the program
	glLinkProgram(textureShader);
	

	// Check if linking succeeded in the same way we checked for compilation success
	glGetProgramiv(textureShader, GL_LINK_STATUS, &isLinked);
	if (!isLinked)
	{
		// If an error happened, first retrieve the length of the log message
		int infoLogLength, charactersWritten;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		// Allocate enough space for the message and retrieve it
		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(shaderProgram, infoLogLength, &charactersWritten, infoLog);


		delete[] infoLog;
		return false;
	}
	
	/*	Use the Program
		Calling glUseProgram tells OpenGL ES that the application intends to use this program for rendering. Now that it's installed into
		the current state, any further glDraw* calls will use the shaders contained within it to process scene data. Only one program can
		be active at once, so in a multi-program application this function would be called in the render loop. Since this application only
		uses one program it can be installed in the current state and left there.
	*/
	glUseProgram(textureShader);

	TEX_UNI = glGetUniformLocation(textureShader,"myTex");

	if (!windows::TestGLError(nativeWindow, "glUseProgram"))
	{
		return false;
	}

	return true;
}

/*!*****************************************************************************************************************************************
 @Function		RenderScene
 @Input			shaderProgram               The shader program used to render the scene
 @Input			eglDisplay                  The EGLDisplay used by the application
 @Input			eglSurface					The EGLSurface created from the native window.
 @Input			nativeWindow                A native window, used to display error messages
 @Return		Whether the function succeeds or not.
 @Description	Renders the scene to the framebuffer. Usually called within a loop.
*******************************************************************************************************************************************/
bool StartFrame( ) 
{
	ULONGLONG ticksNow = GetTickCount64();
	ULONGLONG delta = ticksNow - lastFrame;
	double diff = (double)delta;
	timeStamp = diff / 1000;
	lastFrame = ticksNow;


	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	glDisable(GL_CULL_FACE);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);
	int matrixLocation = glGetUniformLocation(shaderProgram, "transformationMatrix");
	glUniformMatrix4fv( matrixLocation, 1, GL_FALSE, transformationMatrix);

	if (!windows::TestGLError(windows::nativeWindow, "glUniformMatrix4fv"))
	{
		return false;
	}

	return true;
}

void DrawLine(float x1, float y1, float x2, float y2, Colour colour)
{
	DrawLine(x1, y1, x2, y2, colour, colour);
}

void DrawLine(float x1, float y1, float x2, float y2, Colour colour1, Colour colour2)
{
	vertexData[0].pos.x = x1; vertexData[0].pos.y = y1; vertexData[0].c.Set(colour1);
	vertexData[1].pos.x = x2; vertexData[1].pos.y = y2; vertexData[1].c.Set(colour2);

	glUseProgram(shaderProgram);

	// Bind buffer as an vertex buffer so we can fill it with data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*MAX_VERTEX, vertexData, GL_DYNAMIC_DRAW);

	// Enable the user-defined vertex array
	glEnableVertexAttribArray(VERTEX_ARRAY);

	// Sets the vertex data to this attribute index, with the number of floats in each position
	glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), 0);
	// Enable the user-defined vertex array
	glEnableVertexAttribArray(COLOR_ARRAY);
	// Sets the vertex data to this attribute index, with the number of floats in each position
	glVertexAttribPointer(COLOR_ARRAY, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)(sizeof(float)*3));




	glDrawArrays(GL_LINES, 0, 2);
	
	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(COLOR_ARRAY);
}
void DrawRect(float x, float y, float w, float h, Colour colour)
{
	DrawRect(x, y, w, h, colour, colour, colour, colour);
}

void DrawRect(float x, float y, float w, float h, Colour colourNW, Colour colourNE, Colour colourSE, Colour colourSW)
{
	memset(vertexData,0,sizeof(Vertex)*MAX_VERTEX);
	glUseProgram(shaderProgram);
	windows::TestGLError(windows::nativeWindow,"glUseProgram");
	//botleft
	vertexData[0].pos.x = x; vertexData[0].pos.y = y; vertexData[0].c.Set(colourSW);
	vertexData[1].pos.x = x; vertexData[1].pos.y = y + h; vertexData[1].c.Set(colourNW);
	vertexData[2].pos.x = x + w; vertexData[2].pos.y = y + h; vertexData[2].c.Set(colourNE);
	//TopRight
	vertexData[3].pos.x = x; vertexData[3].pos.y = y; vertexData[3].c.Set(colourSW);
	vertexData[4].pos.x = x + w; vertexData[4].pos.y = y; vertexData[4].c.Set(colourSE);
	vertexData[5].pos.x = x + w; vertexData[5].pos.y = y + h; vertexData[5].c.Set(colourNE);



	//glUseProgram(shaderProgram);

	// Bind buffer as an vertex buffer so we can fill it with data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*MAX_VERTEX, vertexData, GL_DYNAMIC_DRAW);

	// Enable the user-defined vertex array
	glEnableVertexAttribArray(VERTEX_ARRAY);

	// Sets the vertex data to this attribute index, with the number of floats in each position
	glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), 0);
	// Enable the user-defined vertex array
	glEnableVertexAttribArray(COLOR_ARRAY);
	// Sets the vertex data to this attribute index, with the number of floats in each position
	glVertexAttribPointer(COLOR_ARRAY, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)(sizeof(float)*3));




	glDrawArrays(GL_TRIANGLES, 0, 6);



	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(COLOR_ARRAY);

}

void DrawTexturedRect(float x, float y, float w, float h)
{
	DrawTexturedRect(x,y,w,h,0.f,0.f,1.f,1.f);
}

void DrawTexturedRect(float x, float y, float w, float h,float u1, float v1, float u2, float v2)
{
	memset(vertexData,0,sizeof(Vertex)*MAX_VERTEX);
	while(glGetError());
	glUseProgram(textureShader);
	windows::TestEGLError(windows::nativeWindow,"glUseProgram");

	int matrixLocation = glGetUniformLocation(textureShader, "transformationMatrix");
	glUniformMatrix4fv( matrixLocation, 1, GL_FALSE, transformationMatrix);
	windows::TestEGLError(windows::nativeWindow,"");

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(TEX_UNI,0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ZERO);

//	glEnable(GL_TEXTURE_2D);
	//botleft
	vertexData[0].pos.x = x; vertexData[0].pos.y = y; vertexData[0].c.Set(1.f,1.f,1.f,1.f); vertexData[0].uv1.x = u1; vertexData[0].uv1.y = v1;
	vertexData[1].pos.x = x; vertexData[1].pos.y = y + h; vertexData[1].c.Set(1.f,1.f,1.f,1.f); vertexData[1].uv1.x = u1; vertexData[1].uv1.y = v2;
	vertexData[2].pos.x = x + w; vertexData[2].pos.y = y + h; vertexData[2].c.Set(1.f,1.f,1.f,1.f); vertexData[2].uv1.x = u2; vertexData[2].uv1.y = v2;
	//TopRight
	vertexData[3].pos.x = x; vertexData[3].pos.y = y; vertexData[3].c.Set(1.f,1.f,1.f,1.f); vertexData[3].uv1.x = u1; vertexData[3].uv1.y = v1;
	vertexData[4].pos.x = x + w; vertexData[4].pos.y = y; vertexData[4].c.Set(1.f,1.f,1.f,1.f); vertexData[4].uv1.x = u2; vertexData[4].uv1.y = v1;
	vertexData[5].pos.x = x + w; vertexData[5].pos.y = y + h; vertexData[5].c.Set(0.f,0.f,0.f,0.f); vertexData[5].uv1.x = u2; vertexData[5].uv1.y = v2;
	 
	// Bind buffer as an vertex buffer so we can fill it with data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*MAX_VERTEX, vertexData, GL_DYNAMIC_DRAW);

	// Enable the user-defined vertex array
	glEnableVertexAttribArray(VERTEX_ARRAY);

	// Sets the vertex data to this attribute index, with the number of floats in each position
	glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), 0);
	// Enable the user-defined vertex array
	glEnableVertexAttribArray(COLOR_ARRAY);
	// Sets the vertex data to this attribute index, with the number of floats in each position
	glVertexAttribPointer(COLOR_ARRAY, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)(sizeof(float)*3));


	glEnableVertexAttribArray(UV_ARRAY);
	// Sets the vertex data to this attribute index, with the number of floats in each position
	glVertexAttribPointer(UV_ARRAY, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)(sizeof(float)*7));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(COLOR_ARRAY);
	glDisableVertexAttribArray(UV_ARRAY);

	//glDisable(GL_BLEND);
	//glDisable(GL_TEXTURE_2D);
}
bool EndFrame()
{
		/*	Present the display data to the screen.
		When rendering to a Window surface, OpenGL ES is double buffered. This means that OpenGL ES renders directly to one frame buffer, 
		known as the back buffer, whilst the display reads from another - the front buffer. eglSwapBuffers signals to the windowing system
		that OpenGL ES 2.0 has finished rendering a scene, and that the display should now draw to the screen from the new data. At the same
		time, the front buffer is made available for OpenGL ES 2.0 to start rendering to. In effect, this call swaps the front and back 
		buffers.
	*/
	if (!eglSwapBuffers(windows::eglDisplay, windows::eglSurface) )
	{
		windows::TestEGLError(windows::nativeWindow, "eglSwapBuffers");
		return false;
	}

	// Check for messages from the windowing system. These will pass through the callback registered earlier.
	MSG eventMessage;	//Always process at LEAST one message per frame
	PeekMessage(&eventMessage, windows::nativeWindow, NULL, NULL, PM_REMOVE);
	TranslateMessage(&eventMessage);
	DispatchMessage(&eventMessage);

	ULONGLONG ticksNow = GetTickCount64();
	ULONGLONG delta = ticksNow - lastFrame;

	double frameTime = 1000 / frameRate;

	while(delta < frameTime && PeekMessage(&eventMessage, windows::nativeWindow, NULL, NULL, PM_REMOVE))
	{ //Process as much as possible while there is time remaining in a frame
		TranslateMessage(&eventMessage);
		DispatchMessage(&eventMessage);
		ticksNow = GetTickCount64();
		delta = ticksNow - lastFrame;
	}

	if(delta < frameTime)
	{ //And sleep whatever is remaining
		Sleep(frameTime - delta);

	}
	return true;
}


double GetTicks()
{
	return timeStamp;
}
void SetFrameRate(u32 _frameRate)
{
	frameRate = _frameRate;
}

/*!*****************************************************************************************************************************************
 @Function		DeInitialiseGLState
 @Input			fragmentShader              Handle to a fragment shader
 @Input			vertexShader                Handle to a vertex shader
 @Input			shaderProgram               Handle to a shader program containing the fragment and vertex shader
 @Input			vertexBuffer                Handle to a vertex buffer object
 @Description	Releases the resources created by "InitialiseGLState"
*******************************************************************************************************************************************/
void DeInitialiseGLState( GLuint fragmentShader, GLuint vertexShader, GLuint shaderProgram, GLuint vertexBuffer ) 
{
	// Frees the OpenGL handles for the program and the 2 shaders
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteProgram(shaderProgram);

	// Delete the VBO as it is no longer needed
	glDeleteBuffers(1, &vertexBuffer);
}



bool InitGraphics(int &width, int &height, int &bitdepth)
{
	bitdepth = 24;
	return windows::InitSystem(windows::g_appInstance,width,height);

}



}; // n0 engine
