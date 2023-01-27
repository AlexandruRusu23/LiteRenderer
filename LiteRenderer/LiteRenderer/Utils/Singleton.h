#ifndef UTILS_SINGLETON_H
#define UTILS_SINGLETON_H

#include <memory>

namespace LiteRenderer
{
	namespace Utils
	{
		template <typename T>
		class Singleton
		{
		public:
			static T& Instance()
			{
				static T instance;
				return instance;
			}

		protected:
			Singleton() = default;
			Singleton(Singleton&&) = delete;
			Singleton(const Singleton&) = delete;
			Singleton& operator=(Singleton&&) = delete;
			Singleton& operator=(const Singleton&) = delete;
			~Singleton() = default;
		};
	}
}

#endif // !UTILS_SINGLETON_H

