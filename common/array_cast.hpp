#pragma once
#include <array>


template <typename T, size_t N, typename... Args>
struct array_wrapper
{
	template <typename P>
	static constexpr std::array<T, N + sizeof...(Args)> rhs(const P *ptr, size_t len, Args... args)
	{
		if (len > 0)
		{
			return array_wrapper<T, N - 1, T, Args...>::rhs(ptr, len - 1, static_cast<T>(ptr[len - 1]), args...);
		}
		else
		{
			return array_wrapper<T, N - 1, T, Args...>::rhs(ptr, 0, T{}, args...);
		}
	}

	template <typename P>
	static constexpr std::array<T, N + sizeof...(Args)> lhs(const P *ptr, size_t len, Args... args)
	{
		if (len > 0)
		{
			return array_wrapper<T, N - 1, T, Args...>::lhs(ptr, len - 1, static_cast<T>(ptr[len - 1]), args...);
		}
		else
		{
			return array_wrapper<T, N - 1, T, Args...>::lhs(ptr, 0, args..., T{});
		}
	}
};

template <typename T, typename... Args>
struct array_wrapper<T, 0, Args...>
{
	template <typename P>
	static constexpr std::array<T, 0 + sizeof...(Args)> rhs(const P */**/, size_t /**/, Args... args)
	{
		return{{ args... }};
	}

	template <typename P>
	static constexpr std::array<T, 0 + sizeof...(Args)> lhs(const P */**/, size_t /**/, Args... args)
	{
		return{{ args... }};
	}
};


template <typename T, size_t N, typename P>
constexpr std::array<T, N> array_cast(const P* ptr, size_t len)
{
	return array_wrapper<T, N>::lhs(ptr, len);
}
