#pragma once


namespace reversed_detail
{
	template <typename T>
	struct reversed_wrapper
	{
		T& t;
		decltype(auto) begin() { return t.rbegin(); }
		decltype(auto) begin() const { return t.rbegin(); }
		decltype(auto) cbegin() const { return t.crbegin(); }
		decltype(auto) end() { return t.rend(); }
		decltype(auto) end() const { return t.rend(); }
		decltype(auto) cend() const { return t.crend(); }
		decltype(auto) rbegin() { return t.begin(); }
		decltype(auto) rbegin() const { return t.begin(); }
		decltype(auto) crbegin() const { return t.cbegin(); }
		decltype(auto) rend() { return t.end(); }
		decltype(auto) rend() const { return t.end(); }
		decltype(auto) crend() const { return t.cend(); }
	};
}


template <typename T>
decltype(auto) reversed(T& container)
{
	return reversed_detail::reversed_wrapper<T>{ container };
}
