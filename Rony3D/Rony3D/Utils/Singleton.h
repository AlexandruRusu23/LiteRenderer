#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>

template <typename T>
class Singleton
{
public:
	static T& Instance();

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton) = delete;

protected:
	inline explicit Singleton() { }
};

template<typename T>
T& Singleton<T>::Instance()
{
	static const std::unique_ptr<T> instance{ new T{} };
	return *instance;
}

#endif // !SINGLETON_H


