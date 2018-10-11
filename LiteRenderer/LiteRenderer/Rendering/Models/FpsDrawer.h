#ifndef MODELS_FPSDRAWER_H
#define MODELS_FPSDRAWER_H

#include "Rendering/Text/TextModel.h"

namespace LiteRenderer
{
	namespace Rendering
	{
		namespace Models
		{
			class FpsDrawer : public Text::TextModel
			{
			public:
				FpsDrawer();
				~FpsDrawer();

				virtual void Update() override final;
				void ChangeTimeToRefresh(float timeToRefresh);

			private:
				static const float TIME_TO_REFRESH; // = 150.f;

				float m_sumDeltaMS;
				float m_timeToRefresh;
			};
		}
	}
}

#endif // !MODELS_FPSDRAWER_H

