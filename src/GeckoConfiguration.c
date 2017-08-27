#include "GeckoConfiguration.h"

#include "aat.h"
#include "gatt_db.h"


#define MAX_CONNECTIONS 1
uint8_t bluetooth_stack_heap[DEFAULT_BLUETOOTH_HEAP(MAX_CONNECTIONS)];

const gecko_configuration_t config = {
	.config_flags               = GECKO_CONFIG_FLAG_LFXO_DISABLE,
	.sleep.flags                = 0,
	.bluetooth.max_connections  = MAX_CONNECTIONS,
	.bluetooth.heap             = bluetooth_stack_heap,
	.bluetooth.heap_size        = sizeof(bluetooth_stack_heap),
	.gattdb                     = &bg_gattdb_data,
	// .ota.flags                  = 0,
	// .ota.device_name_len        = 3,
	// .ota.device_name_ptr        = "OTA",
};
