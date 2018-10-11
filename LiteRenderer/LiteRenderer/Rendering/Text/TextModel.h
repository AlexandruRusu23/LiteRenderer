#ifndef TEXT_TEXTMODEL_H
#define TEXT_TEXTMODEL_H

#include "Rendering/Models/Model.h"
#include "TextLoader.h"
#include "TextObject.h"

namespace LiteRenderer
{
	namespace Rendering
	{
		namespace Text
		{
			class TextModel : public Models::Model
			{
			public:
				TextModel();
				virtual ~TextModel();

				virtual void Create();

				void SetTextObject(const TextObject& textObject);
				void SetTextLoader(TextLoader*& textLoader);

				virtual void Update() override;
				virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) override;

			protected:
				TextObject m_textObject;
				TextLoader* m_textLoader = nullptr;
			};
		}
	}
}


#endif // !TEXT_TEXTMODEL_H

