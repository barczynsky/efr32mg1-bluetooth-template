#pragma once
#include <cstdint>


class Clock4D
{
private:
	uint8_t h{};
	uint8_t m{};
	uint8_t s{};

public:
	Clock4D() = default;
	Clock4D(uint8_t h, uint8_t m, uint8_t s): h{ h }, m{ m }, s{ s } {}

	void add_1s()
	{
		s = s + 1;
		m = m + s / 60;
		h = h + m / 60;
		s = s % 60;
		m = m % 60;
		h = h % 24;
	}

public:
	uint8_t get_h()
	{
		return h;
	}

	uint8_t get_m()
	{
		return m;
	}

	uint8_t get_s()
	{
		return s;
	}

	uint32_t get_time()
	{
		return h * 3600 + m * 60 + s;
	}

public:
	uint16_t get_h_m_4D()
	{
		return h * 100 + m;
	}

	uint16_t get_m_s_4D()
	{
		return m * 100 + s;
	}

	uint32_t get_h_m_s_4D()
	{
		return h * 10000 + m * 100 + s;
	}

};
