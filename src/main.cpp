#include <cstdint>
#include <cstring>

#include "infrastructure.h"
#include "gatt_db.h"

#include "em_cmu.h"
#include "em_gpio.h"
#include "em_timer.h"

#include "InitDevice.h"
#include "GeckoConfiguration.h"


constexpr int EVENT_SECOND_ELAPSED = 0x11;
constexpr int EVENT_1_SECOND = 32768; // one second on LFRCO

constexpr int EVENT_BLUETOOTH_NOTIFY = 0x12;
constexpr int EVENT_BLUETOOTH_NOTIFY_RATE = EVENT_1_SECOND;



void bluetooth_notify_example(uint16_t value)
{
	uint8_t raw_data[8];
	uint8_t *p = nullptr;

	p = raw_data;
	UINT16_TO_BITSTREAM(p, value);
	// gecko_cmd_gatt_server_send_characteristic_notification(
	// 	0xFF, gattdb_<characteristic>, 2, raw_data);
}


/*******************************************************************************
 * @brief
 *   Hardware initialization
 * @param
 *   None
 * @return
 *   None
 ******************************************************************************/

void hardware_init()
{
}

//void SWO_Init()
//{
//	// /* Enable GPIO clock. */
//	// CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
//	CMU_ClockEnable(cmuClock_GPIO, true);
//
//	/* Set up SWO (SWV) */
//	GPIO->ROUTEPEN = GPIO->ROUTEPEN | GPIO_ROUTEPEN_SWVPEN;
//	GPIO->ROUTELOC0 = (GPIO->ROUTELOC0 & (~_GPIO_ROUTELOC0_SWVLOC_MASK))
//			| GPIO_ROUTELOC0_SWVLOC_LOC0;
//
//	// /* Enable output on pin - GPIO Port F, Pin 2 */
//	// GPIO->P[5].MODEL &= ~(_GPIO_P_MODEL_MODE2_MASK);
//	// GPIO->P[5].MODEL |= GPIO_P_MODEL_MODE2_PUSHPULL;
//
//	/* Enable output on pin - GPIO Port F, Pin 2 */
//	GPIO_PinModeSet(gpioPortF, 2, gpioModePushPull, 0);
//
//	// /* Enable debug clock AUXHFRCO */
//	// CMU->OSCENCMD = CMU_OSCENCMD_AUXHFRCOEN;
//	// /* Wait until clock is ready */
//	// while (!(CMU->STATUS & CMU_STATUS_AUXHFRCORDY));
//
//	/* Enable AUXHFRCO oscillator, and wait for it to be stable */
//	CMU_OscillatorEnable(cmuOsc_AUXHFRCO, true, true);
//
//	/* Enable trace in core debug */
//	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
//	ITM->LAR  = 0xC5ACCE55;
//	ITM->TER  = 0x0;
//	ITM->TCR  = 0x0;
//	TPI->SPPR = 2;
//	TPI->ACPR = 0xf;
//	ITM->TPR  = 0x0;
//	DWT->CTRL = 0x400003FE;
//	ITM->TCR  = 0x0001000D;
//	TPI->FFCR = 0x00000100;
//	ITM->TER  = 0x1;
//}

// void SWO_print(std::string s)
// {
// 	for (auto&& c : s)
// 	{
// 		ITM_SendChar(c);
// 	}
// }

/*******************************************************************************
 * @brief
 *   BLE service initialization
 * @param
 *   None
 * @return
 *   None
 ******************************************************************************/

void services_init()
{
}

/*******************************************************************************
 * @brief
 *   Main()
 * @param
 *   None
 * @return
 *   None
 ******************************************************************************/
int main()
{
	enter_DefaultMode_from_RESET();

	gecko_init(&config);

	// hardware_init();

	// services_init();

	for (;;)
	{
		gecko_cmd_packet* evt = gecko_wait_event();

		switch (BGLIB_MSG_ID(evt->header))
		{
			/* This boot event is generated when the system boots up after reset.
			 * Here the system is set to start advertising immediately after boot procedure. */
			case gecko_evt_system_boot_id:
			{
				hardware_init();

				gecko_cmd_system_set_tx_power(195);

				/* Set advertising parameters. 100ms advertisement interval. All channels used.
				 * The first two parameters are minimum and maximum advertising interval, both in
				 * units of (milliseconds * 1.6). The third parameter '7' sets advertising on all channels. */
				gecko_cmd_le_gap_set_adv_parameters(160, 160, 7);

				/* Start general advertising and enable connections. */
				gecko_cmd_le_gap_set_mode(le_gap_general_discoverable, le_gap_undirected_connectable);

				// System events
				gecko_cmd_hardware_set_soft_timer(EVENT_1_SECOND, EVENT_SECOND_ELAPSED, 0);
			}
			break;
			/* This event is generated when a connected client has either
			 * 1) changed a Characteristic Client Configuration, meaning that they have enabled
			 * or disabled Notifications or Indications, or
			 * 2) sent a confirmation upon a successful reception of the indication. */
			case gecko_evt_gatt_server_characteristic_status_id:
			{
				/* Check that the characteristic in question is temperature - its ID is defined
				 * in gatt.xml as "temperature". Also check that status_flags = 1, meaning that
				 * the characteristic client configuration was changed (notifications or indications
				 * enabled or disabled). */
				// if (evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_temp_measurement
				// &&  evt->data.evt_gatt_server_characteristic_status.status_flags == 0x01)
				if (evt->data.evt_gatt_server_characteristic_status.status_flags == 0x01)
				{
					auto notify_flag = evt->data.evt_gatt_server_characteristic_status.client_config_flags & 0x01;
					switch (evt->data.evt_gatt_server_characteristic_status.characteristic)
					{
						// case gattdb_<characteristic>:
						case 0x0:
						{
							switch (notify_flag)
							{
								case 0x01:
								{
									gecko_cmd_hardware_set_soft_timer(EVENT_BLUETOOTH_NOTIFY_RATE, EVENT_BLUETOOTH_NOTIFY, 0);
								}
								break;
								case 0x00:
								{
									gecko_cmd_hardware_set_soft_timer(0, EVENT_BLUETOOTH_NOTIFY, 0);
								}
								break;
							}
						}
						break;
					}
					switch (evt->data.evt_gatt_server_characteristic_status.characteristic)
					{
						case 0x0:
							// handle characteristic change
							break;
					}
				}
			}
			break;
			case gecko_evt_le_connection_closed_id:
			{
				gecko_cmd_hardware_set_soft_timer(0, EVENT_BLUETOOTH_NOTIFY, 0);

				gecko_cmd_le_gap_set_mode(le_gap_general_discoverable, le_gap_undirected_connectable);
			}
			break;
			case gecko_evt_hardware_soft_timer_id:
			{
				switch (evt->data.evt_hardware_soft_timer.handle)
				{
					case EVENT_SECOND_ELAPSED:
					{
						// processed every single second
					}
					break;
					case EVENT_BLUETOOTH_NOTIFY:
					{
						// processed before bluetooth notification
						// bluetooth_notify_example(0xFFFF);
					}
					break;
				}
			}
			break;
			case gecko_evt_gatt_server_user_read_request_id:
			{
				// handle user read request
			}
			break;
			case gecko_evt_gatt_server_user_write_request_id:
			{
				// handle characteristic user write request
				// auto&& req = evt->data.evt_gatt_server_user_write_request;
				// if (req.characteristic == gattdb_<characteristic> && req.value.len == 1)
				// {
				// 	// gecko_cmd_gatt_server_send_user_write_response(0xFF, gattdb_<characteristic>, 0);
				// }
			}
			break;
		}
	}
}
