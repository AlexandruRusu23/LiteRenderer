#ifndef ILISTENER_H
#define ILISTENER_H

namespace Core
{
	class IListener
	{
	public:
		virtual ~IListener() = 0;

		//drawing functions
		virtual void NotifyBeginFrame() = 0;
		virtual void NotifyDisplayFrame() = 0;
		virtual void NotifyEndFrame() = 0;
		virtual void NotifyReshape(int width, int height, int previousWidth, int previousHeight) = 0;
	};

	inline IListener::~IListener()
	{

	}
}

#endif
