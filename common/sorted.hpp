#pragma once
#include <algorithm>
#include <functional>
#include <vector>


template <typename T, typename Compare = std::less<typename T::value_type>>
decltype(auto) sorted(T& container, Compare comp = {})
{
	using view_t = std::vector<std::reference_wrapper<typename T::value_type>>;
	view_t view{ container.begin(), container.end() };
	std::sort(view.begin(), view.end(), comp);
	return view;
}
