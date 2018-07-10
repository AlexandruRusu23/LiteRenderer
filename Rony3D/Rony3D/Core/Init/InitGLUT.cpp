#include "InitGLUT.h"
#include "InitGLEW.h"
#include "DebugOutput.h"

using namespace Core;
using namespace Init;

IListener* InitGLUT::m_listener = nullptr;
WindowInfo InitGLUT::m_windowInformation;

void InitGLUT::Init(int argc, char **argv, const WindowInfo& windowInfo, const ContextInfo& contextInfo, const FrameBufferInfo& frameBufferInfo)
{
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

	std::cout << "GLUT: Initialized" << std::endl;

	glEnable(GL_DEBUG_OUTPUT);

	// register callbacks
	glutIdleFunc(IdleCallback);
	glutCloseFunc(CloseCallback);
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);

	InitGLEW::Init();
	glDebugMessageCallback(DebugOutput::RegisterDebugError, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	PrintOpenGLInfo(windowInfo, contextInfo);
}

void InitGLUT::Run()
{
	std::cout << "GLUT:\t Start Running" << std::endl;
	glutMainLoop();
}

void InitGLUT::Close()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
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

void InitGLUT::EnterFullscreen()
{
	glutFullScreen();
}

void InitGLUT::ExitFullscreen()
{
	glutLeaveFullScreen();
}

void InitGLUT::SetListener(IListener* iListener)
{
	m_listener = iListener;
}

void InitGLUT::PrintOpenGLInfo(const WindowInfo& windowInfo, const ContextInfo& contextInfo)
{
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "***************************************************" << std::endl;
	std::cout << "GLUT: Initialise" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tVersion : " << version << std::endl;
}
