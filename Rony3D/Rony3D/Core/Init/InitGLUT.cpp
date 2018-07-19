#include "InitGLUT.h"
#include "InitGLEW.h"
#include "../Logging/DebugOutput.h"
#include "Logger.h"

using namespace Core;
using namespace Init;

IListener* InitGLUT::m_listener = nullptr;
WindowInfo InitGLUT::m_windowInformation("Rony3D", 300, 300, 960, 540, true);

void InitGLUT::Init(int argc, char **argv, const WindowInfo& windowInfo, const ContextInfo& contextInfo, const FrameBufferInfo& frameBufferInfo)
{
	Logger::Init();

	glutInit(&argc, argv);

	if (contextInfo.useCoreProfile)
	{
		glutInitContextVersion(contextInfo.majorVersion, contextInfo.minorVersion);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(frameBufferInfo.flags);
	glutInitWindowPosition(windowInfo.positionX, windowInfo.positionY);
	glutInitWindowSize(windowInfo.width, windowInfo.height);

	glutCreateWindow(windowInfo.name.c_str());

	m_windowInformation = windowInfo;

	Logger::Log("GLUT: Initialized");

	glEnable(GL_DEBUG_OUTPUT);

	// register callbacks
	glutIdleFunc(IdleCallback);
	glutCloseFunc(CloseCallback);
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);

	glutKeyboardFunc(NULL);
	glutKeyboardUpFunc(NULL);
	glutSpecialFunc(NULL); // special keyboard
	glutSpecialUpFunc(NULL); // special keyboard
	glutMouseFunc(NULL);
	glutMouseWheelFunc(NULL);
	glutMotionFunc(NULL); // mouse moves within window while mouse buttons are pressed
	glutPassiveMotionFunc(NULL); // mouse moves within window while no mouse buttons are pressed

	InitGLEW::Init();
	glDebugMessageCallback(Logging::DebugOutput::RegisterDebugError, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	PrintOpenGLInfo(windowInfo, contextInfo);
}

void InitGLUT::SetListener(IListener* iListener)
{
	m_listener = iListener;
}

void InitGLUT::Run()
{
	Logger::Log("GLUT:\t Start Running");
	glutMainLoop();
}

void InitGLUT::Close()
{
	Logger::Log("GLUT:\t Finished");
	Logger::Close();
	glutLeaveMainLoop();
}

void InitGLUT::EnterFullscreen()
{
	glutFullScreen();
}

void InitGLUT::ExitFullscreen()
{
	glutLeaveFullScreen();
}

void InitGLUT::PrintOpenGLInfo(const WindowInfo& windowInfo, const ContextInfo& contextInfo)
{
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	Logger::Log("***************************************************");
	Logger::Log("GLUT: Initialise");
	Logger::Log(LogType::MESSAGE, "GLUT:\tVendor : %s", vendor);
	Logger::Log(LogType::MESSAGE, "GLUT:\tRenderer : %s", renderer);
	Logger::Log(LogType::MESSAGE, "GLUT:\tVersion : %s", version);
}

void InitGLUT::IdleCallback(void)
{
	glutPostRedisplay();
}

void InitGLUT::DisplayCallback()
{
	//check for NULL
	if (m_listener)
	{
		m_listener->NotifyBeginFrame();
		m_listener->NotifyDisplayFrame();

		glutSwapBuffers();

		m_listener->NotifyEndFrame();
	}
}

void InitGLUT::ReshapeCallback(int width, int height)
{
	if (m_windowInformation.isReshapable == true)
	{
		if (m_listener)
			m_listener->NotifyReshape(width, height, m_windowInformation.width, m_windowInformation.height);
		
		m_windowInformation.width = width;
		m_windowInformation.height = height;
	}
}

void InitGLUT::CloseCallback()
{
	Close();
}
