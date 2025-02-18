#include <cstdio>

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include "lwip/ip4_addr.h"

#include "FreeRTOS.h"
#include "task.h"
#include "ping/ping.h"

// Standard Task priority
#define TASK_PRIORITY (tskIDLE_PRIORITY + 1UL)

#ifndef PING_ADDR
#define PING_ADDR "10.99.33.254"
#endif




/***
 * Debug function to look at Task Stats
 */
void runTimeStats()
{
	TaskStatus_t *pxTaskStatusArray;
	volatile UBaseType_t uxArraySize, x;
	unsigned long ulTotalRunTime;

	// Get number of takss
	uxArraySize = uxTaskGetNumberOfTasks();
	printf("Number of tasks %d\n", uxArraySize);

	// Allocate a TaskStatus_t structure for each task.
	pxTaskStatusArray = (TaskStatus_t *)pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));

	if (pxTaskStatusArray != NULL)
	{
		// Generate raw status information about each task.
		uxArraySize = uxTaskGetSystemState(pxTaskStatusArray,
										   uxArraySize,
										   &ulTotalRunTime);

		// Print stats
		for (x = 0; x < uxArraySize; x++)
		{
			printf("Task: %d \t cPri:%d \t bPri:%d \t hw:%d \t%s\n",
				   pxTaskStatusArray[x].xTaskNumber,
				   pxTaskStatusArray[x].uxCurrentPriority,
				   pxTaskStatusArray[x].uxBasePriority,
				   pxTaskStatusArray[x].usStackHighWaterMark,
				   pxTaskStatusArray[x].pcTaskName);
		}

		// Free array
		vPortFree(pxTaskStatusArray);
	}
	else
	{
		printf("Failed to allocate space for stats\n");
	}

	// Get heap allocation information
	HeapStats_t heapStats;
	vPortGetHeapStats(&heapStats);
	printf("HEAP avl: %d, blocks %d, alloc: %d, free: %d\n",
		   heapStats.xAvailableHeapSpaceInBytes,
		   heapStats.xNumberOfFreeBlocks,
		   heapStats.xNumberOfSuccessfulAllocations,
		   heapStats.xNumberOfSuccessfulFrees);
}

void pingTask(void *params)
{
	printf("Ping task started\n");

	if (cyw43_arch_init()) {
        printf("failed to initialise\n");
        return;
    }
    cyw43_arch_enable_sta_mode();
    printf("Connecting to Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("failed to connect.\n");
        exit(1);
    } else {
        printf("Connected.\n");
    }

    ip_addr_t ping_addr;
    ipaddr_aton(PING_ADDR, &ping_addr);
    ping_init((const ip_addr_t*)&ping_addr);

    while(true) {

        vTaskDelay(100);
    }

    cyw43_arch_deinit();


}

/***
 * Main task to boot the other Agents
 * @param params - unused
 */
void mainTask(void *params)
{


	printf("Main task started\n");


	for (;;)
	{
		vTaskDelay(2000);
		runTimeStats();
	}
}

/***
 * Launch the tasks and scheduler
 */
void vLaunch(void)
{


	TaskHandle_t task_main;
	xTaskCreate(mainTask, "MainThread", 1000, NULL, TASK_PRIORITY, &task_main);

	TaskHandle_t task_ping;
    xTaskCreate(pingTask, "pingThread", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY, &task_ping);

	/* Start the tasks and timer running. */
	vTaskStartScheduler();
}

int main()
{

	stdio_init_all();
	sleep_ms(1000);
	printf("Go\n");


	// Start tasks and scheduler
	const char *rtos_name;
#if (configNUMBER_OF_CORES > 1)
	rtos_name = "FreeRTOS SMP";
#else
	rtos_name = "FreeRTOS";
#endif

#if (configNUMBER_OF_CORES == 2)
	printf("Starting %s on both cores:\n", rtos_name);
	vLaunch();
#elif (RUN_FREERTOS_ON_CORE == 1)
	printf("Starting %s on core 1:\n", rtos_name);
	multicore_launch_core1(vLaunch);
	while (true)
		;
#else
	printf("Starting %s on core 0:\n", rtos_name);
	vLaunch();
#endif

	return 0;
}
