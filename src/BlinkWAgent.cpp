#include "BlinkWAgent.h"
#include "stdio.h"
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

// Blink Delay
#define DELAY 500

// Perform initialisation
int pico_led_init(void)
{

    // For Pico W devices we need to initialise the driver etc
    return cyw43_arch_init();
}

// Turn the led on or off
void pico_set_led(bool led_on)
{

    // Ask the wifi "driver" to set the GPIO on or off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
}

/***
 * Constructor

 */
BlinkWAgent::BlinkWAgent()
{
}

/***
 * Destructor
 */
BlinkWAgent::~BlinkWAgent()
{
    stop();
}

/***
 * Main Run Task for agent
 */
void BlinkWAgent::run()
{

    printf("Blink Started\n");
    printf("LED Pin: %d\n", CYW43_WL_GPIO_LED_PIN);
    vTaskDelay(1000);
    printf("poot\n");

    pico_set_led(false);
    while (true)
    {
        pico_set_led(true);
        vTaskDelay(DELAY);
        pico_set_led(false);
        vTaskDelay(DELAY);
    }
}

/***
 * Get the static depth required in words
 * @return - words
 */
configSTACK_DEPTH_TYPE BlinkWAgent::getMaxStackSize()
{
    return 200;
}
