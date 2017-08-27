#pragma once
#include <cstdint>
#include <array>
#include <tuple>

#include "reversed.hpp"
#include "array_cast.hpp"


template <typename T, int DW = 4>
class Display47
{
private:
	using Seg = std::array<int, 8>;
	const std::array<Seg, 16> digit_to_seg{{
	// 	{ a, b, c, d, e, f, g, . }, // #
		{ 1, 1, 1, 1, 1, 1, 0, 0 }, // 0
		{ 0, 1, 1, 0, 0, 0, 0, 0 }, // 1
		{ 1, 1, 0, 1, 1, 0, 1, 0 }, // 2
		{ 1, 1, 1, 1, 0, 0, 1, 0 }, // 3
		{ 0, 1, 1, 0, 0, 1, 1, 0 }, // 4
		{ 1, 0, 1, 1, 0, 1, 1, 0 }, // 5
		{ 1, 0, 1, 1, 1, 1, 1, 0 }, // 6
		{ 1, 1, 1, 0, 0, 0, 0, 0 }, // 7
		{ 1, 1, 1, 1, 1, 1, 1, 0 }, // 8
		{ 1, 1, 1, 1, 0, 1, 1, 0 }, // 9

		{ 1, 1, 1, 0, 1, 1, 1, 0 }, // A
		{ 0, 0, 1, 1, 1, 1, 1, 0 }, // B
		{ 1, 0, 0, 1, 1, 1, 0, 0 }, // C
		{ 0, 1, 1, 1, 1, 0, 1, 0 }, // D
		{ 1, 0, 0, 1, 1, 1, 1, 0 }, // E
		{ 1, 0, 0, 0, 1, 1, 1, 0 }, // F
	}};

	const Seg empty_seg{ { 0, 0, 0, 0, 0, 0, 0, 0 } };
	const Seg zfill_seg{ digit_to_seg[0] };

	using SegX = std::tuple<char, Seg>;
	const std::array<SegX, 25> char_to_seg{{
	// 	{ '.', { a, b, c, d, e, f, g, . } }, // DP
		{  0 ,   empty_seg                }, // empty
		{ '0',   digit_to_seg[0x0]        }, // 0
		{ '1',   digit_to_seg[0x1]        }, // 1
		{ '2',   digit_to_seg[0x2]        }, // 2
		{ '3',   digit_to_seg[0x3]        }, // 3
		{ '4',   digit_to_seg[0x4]        }, // 4
		{ '5',   digit_to_seg[0x5]        }, // 5
		{ '6',   digit_to_seg[0x6]        }, // 6
		{ '7',   digit_to_seg[0x7]        }, // 7
		{ '8',   digit_to_seg[0x8]        }, // 8
		{ '9',   digit_to_seg[0x9]        }, // 9
		{ 'A',   digit_to_seg[0xA]        }, // A
		{ 'B',   digit_to_seg[0xB]        }, // B
		{ 'C',   digit_to_seg[0xC]        }, // C
		{ 'D',   digit_to_seg[0xD]        }, // D
		{ 'E',   digit_to_seg[0xE]        }, // E
		{ 'F',   digit_to_seg[0xF]        }, // F
		{ 'a',   digit_to_seg[0xA]        }, // A
		{ 'b',   digit_to_seg[0xB]        }, // B
		{ 'c',   digit_to_seg[0xC]        }, // C
		{ 'd',   digit_to_seg[0xD]        }, // D
		{ 'e',   digit_to_seg[0xE]        }, // E
		{ 'f',   digit_to_seg[0xF]        }, // F
		{ ' ',   empty_seg                }, // space
		{ '-', { 0, 0, 0, 0, 0, 0, 1, 0 } }, // -
	}};

public:
	using Digits = std::array<T, DW>;
	using Segments = std::array<T, 8>;
	using DirectValue = std::array<char, DW>;

private:
	Digits digs{};
	Segments segs{};

private:
	using DisplayValue = std::array<const Seg*, DW>;

private:
	DisplayValue current_value{};
	DisplayValue next_value{};
	size_t current_digit{ 0 };
	size_t current_dp{ DW };

public:
	Display47() = default;

	void init(const Digits& d, const Segments& s)
	{
		digs = d;
		segs = s;

		init();
	}

	void init()
	{
		current_digit = 0;
		current_dp = DW;
		for (auto&& d : digs)
		{
			d.clear();
		}
		for (auto&& s : segs)
		{
			s.clear();
		}
	}

public:
	void set(uint32_t val, size_t base = 10)
	{
		base = std::min(base, digit_to_seg.size());
		if (val < base)
		{
			for (size_t i = 0; i < DW - 1; ++i)
			{
				next_value[i] = getEmptySeg();
			}
			next_value[DW - 1] = getSegFromDigit(val);
		}
		else
		{
			for (auto&& next_elem : reversed(next_value))
			{
				if (val > 0)
				{
					auto d = val % base;
					next_elem = getSegFromDigit(d);
					val = val / base;
				}
				else
				{
					next_elem = getEmptySeg();
				}
			}
		}

		for (int i = current_dp; i < DW; ++i)
		{
			if (next_value[i] == getEmptySeg())
			{
				next_value[i] = getZFillSeg();
			}
		}
	}

	void set(DirectValue val)
	{
		current_dp = DW;
		for (size_t i = 0; i < DW; ++i)
		{
			next_value[i] = getSegFromChar(val[i]);
		}
	}

	void scale(int s)
	{
		if (s < 0)
		{
			current_dp = s + (DW - 1);
		}
		else
		{
			current_dp = DW;
		}
	}

public:
	void update()
	{
		display();
		next();
	}

private:
	void display()
	{
		// digs[(current_digit - 1) & 0x3].clear();
		for (size_t i = 0; i < DW; ++i)
		{
			digs[i].clear();
		}

		for (size_t i = 0; i < segs.size(); ++i)
		{
			auto&& d = *current_value[current_digit];
			segs[i].set(d[i]);
		}

		if (current_dp == current_digit && segs.size() > 0)
		{
			segs.back().set(1);
		}

		digs[current_digit].set();
	}

	void next()
	{
		if (DW == 4)
		{
			current_digit = (current_digit + 1) & 0x3;
		}
		else if (DW == 2)
		{
			current_digit = 1 - current_digit;
		}
		else
		{
			current_digit = (current_digit + 1) % DW;
		}

		if (current_digit == 0)
		{
			current_value = next_value;
		}
	}

private:
	constexpr const Seg* getSegFromDigit(int d)
	{
		if (d >= 0 && d <= 9)
		{
			return &digit_to_seg[d];
		}
		return &empty_seg;
	}

	constexpr const Seg* getSegFromChar(char c)
	{
		for (auto&& sx : char_to_seg)
		{
			if (std::get<0>(sx) == c)
			{
				return &std::get<1>(sx);
			}
		}
		return &empty_seg;
	}

	constexpr const Seg* getEmptySeg()
	{
		return &empty_seg;
	}

	constexpr const Seg* getZFillSeg()
	{
		return &zfill_seg;
	}

};


constexpr decltype(auto) operator""_D47(const char *s, size_t len)
{
	// return std::array<char, 4>{ 0, 0, ..., s[0], s[1], ... };
	return array_wrapper<char, 4>::rhs(s, len);
}
