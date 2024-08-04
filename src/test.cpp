/**
 * Jon Durrant.
 *
 * Blink LED on Raspberry PICO W
 */

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#include <iostream>

#define DELAY 500 // in microseconds
const uint LED_PIN = 22;


int main() {
	cyw43_arch_init();
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) { // Loop forever
    	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        gpio_put(LED_PIN, 1);
        printf("LED On\n");
        std::cout<<"LED on"<<std::endl;
		sleep_ms(DELAY);
		cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        gpio_put(LED_PIN, 0);
        printf("LED Off\n");
		sleep_ms(DELAY);
    }

}