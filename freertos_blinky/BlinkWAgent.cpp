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
#if defined(PICO_DEFAULT_LED_PIN)
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // For Pico W devices we need to initialise the driver etc
    return cyw43_arch_init();
#endif
}

// Turn the led on or off
void pico_set_led(bool led_on)
{
#if defined(PICO_DEFAULT_LED_PIN)
    // Just set the GPIO on or off
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Ask the wifi "driver" to set the GPIO on or off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
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
    return 150;
}
