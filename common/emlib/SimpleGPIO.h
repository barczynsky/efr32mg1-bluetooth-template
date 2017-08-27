#pragma once
#include "em_gpio.h"


#ifdef EFR32MG1P232F256GM48
enum class Port
{
	A = gpioPortA,
	B = gpioPortB,
	C = gpioPortC,
	D = gpioPortD,
	// E = gpioPortE,
	F = gpioPortF,
};

using Port_t = GPIO_Port_TypeDef;
#else
#error unsupported or undefined MCU
#endif


class ActiveHighGPIO
{
	bool ok{ false };
	Port_t port;
	int pin;

public:
	ActiveHighGPIO() = default;
	ActiveHighGPIO(Port port, int pin): ActiveHighGPIO(static_cast<Port_t>(port), pin) {}
	ActiveHighGPIO(Port_t port, int pin): ok{ true }, port{ port }, pin{ pin }
	{
		init();
	}

	void init() const
	{
		GPIO_PinModeSet(port, pin, gpioModePushPull, 0);
	}

	void set(int level) const
	{
		if (ok)
		{
			if (level == 0) GPIO_PinOutClear(port, pin);
			else GPIO_PinOutSet(port, pin);
		}
	}

	void clear() const
	{
		if (ok) GPIO_PinOutClear(port, pin);
	}

	void set() const
	{
		if (ok) GPIO_PinOutSet(port, pin);
	}

	void toggle() const
	{
		if (ok) GPIO_PinOutToggle(port, pin);
	}

};

using SimpleGPIO = ActiveHighGPIO;


class ActiveLowGPIO
{
	bool ok{ false };
	Port_t port;
	int pin;

public:
	ActiveLowGPIO() = default;
	ActiveLowGPIO(Port port, int pin): ActiveLowGPIO(static_cast<Port_t>(port), pin) {}
	ActiveLowGPIO(Port_t port, int pin): ok{ true }, port{ port }, pin{ pin }
	{
		init();
	}

	void init() const
	{
		GPIO_PinModeSet(port, pin, gpioModePushPull, 1);
	}

	void set(int level) const
	{
		if (ok)
		{
			if (level == 0) GPIO_PinOutSet(port, pin);
			else GPIO_PinOutClear(port, pin);
		}
	}

	void clear() const
	{
		if (ok) GPIO_PinOutSet(port, pin);
	}

	void set() const
	{
		if (ok) GPIO_PinOutClear(port, pin);
	}

	void toggle() const
	{
		if (ok) GPIO_PinOutToggle(port, pin);
	}

};
