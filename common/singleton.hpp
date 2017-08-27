#pragma once


// Meyer's Singleton class template
template <typename T>
class singleton
{
protected:
	singleton() = default;

public:
	static T& instance()
	{
		static T singleton_instance{};
		return singleton_instance;
	}
};
