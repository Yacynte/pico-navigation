#include <stdio.h>
#include <iostream>
#include <string>
#include "pico/stdlib.h"
//#include "pico/cyw43_arch.h"
#include "functions.h"
// #include "pico/stdio_usb.h"
//#include "tusb.h"
#include <cstdio>
#include <bits/stdc++.h>
#include <vector>

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments

const uint LED_PIN = 25;

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9




int main()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    initialize_uart();
    stdio_init_all();
    sleep_ms(2500);
    printf("USB Serial Communication Initialized\n");


    //cyw43_arch_enable_sta_mode();

    gpio_put(LED_PIN, 1);
    sleep_ms(1500);
    uint previous_speed = 0;
    uint previous_angular_speed = 0;
    char motion_info_[MAX_LINE_LENGTH];
    char buffer[MAX_LINE_LENGTH];
    //std::string motion_info;
    gpio_put(LED_PIN, 0);
    sleep_ms(1500);
    while (true) {
        sleep_ms(500);
        gpio_put(LED_PIN, 1);
        printf("LED on\n");
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        printf("LED off\n");
        sleep_ms(500);
        //motion_info = (motion_info_);
        receive_input(motion_info_);
        std::string motion_info(motion_info_);
        //std::string motion_info;
        //motion_info = receive_uart_message();
        printf ("our data: %s \n", motion_info.c_str());
        gpio_put(LED_PIN, 1);
        std::vector<std::string> splitted_data = split_received_data(motion_info);
        std::string direction = splitted_data[0];
    
        printf ("direction: %s \n", direction.c_str());
        float speed = std::stof(splitted_data[1].c_str());
        printf ("speed: %s \n", splitted_data[1].c_str());
        float angular_speed = std::stof(splitted_data[2].c_str());
        printf ("angular_speed: %s \n", splitted_data[2].c_str());
        if((previous_speed - speed ) > 0.02){ 
            // Apply brakes
            brake_robot(direction, previous_speed-speed, previous_angular_speed-angular_speed);
        }
        else{
            move_robot(direction, speed, angular_speed);
        }
        previous_speed = speed;
        previous_angular_speed = angular_speed;
        
        
        
    }

    return 0;

}

/*
/ SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
    // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c
    */