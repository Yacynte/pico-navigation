#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pwm.h"
//#include "pico/cyw43_arch.h"
#include "functions.h"
//#include "tusb.h"
#include <cstdio>
#include <bits/stdc++.h>
#include <vector>
#include <typeinfo>



void init_motor_pins() {
    gpio_init(Motor_INLeft);
    gpio_set_dir(Motor_INLeft, GPIO_OUT);
    gpio_init(Motor_INRight);
    gpio_set_dir(Motor_INRight, GPIO_OUT);
    gpio_init(Motor_PWMLeft);
    gpio_set_dir(Motor_PWMLeft, GPIO_OUT);
    gpio_init(Motor_PWMRight);
    gpio_set_dir(Motor_PWMRight, GPIO_OUT);

    // Set up PWM
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);  // Adjust clock divider as needed
    pwm_init(pwm_gpio_to_slice_num(Motor_PWMLeft), &config, true);
    pwm_init(pwm_gpio_to_slice_num(Motor_PWMRight), &config, true);
}

void move_robot_non_L298N(std::string motion_info_ ){
    std::vector<std::string> motion_info = split_received_data(motion_info_);
    //std::vector<uint> current_speeds = get_current_speeds();
    std::string direction = motion_info[0];
    std::string orientation = motion_info[1];
    float target_speed = std::stof(motion_info[2]);
    float target_ang_speed = std::stof(motion_info[3]);
    float current_speed = std::stof(motion_info[4]);
    float current_ang_speed = std::stof(motion_info[5]);
    if (direction == "forward"){
        gpio_put(Motor_INLeft, 1);
        gpio_put(Motor_INRight, 0);
    }
    else if (direction == "backward"){
        gpio_put(Motor_INLeft, 0);
        gpio_put(Motor_INRight, 1);
    }

    if(orientation == "Left"){
        uint speedLeft = std::ceil((target_speed/max_speed)*1023);
        uint targetspeedRight = radius * (target_ang_speed * M_PI / 180.0) * 3.6; // Km/h
        if(targetspeedRight > max_speed){ targetspeedRight = max_speed;}
        uint speedRight = std::ceil((targetspeedRight/max_speed)*1023);
        pwm_set_gpio_level(Motor_PWMLeft, speedLeft);
        pwm_set_gpio_level(Motor_PWMRight, speedRight);
        sleep_ms(10);
        }
    if(orientation == "Right"){
        uint speedRight = std::ceil((target_speed/max_speed)*1023);
        uint targetspeedLeft = radius * (target_ang_speed * M_PI / 180.0) * 3.6; // Km/h
        if(targetspeedLeft > max_speed){ targetspeedLeft = max_speed;}
        uint speedLeft = std::ceil((targetspeedLeft/max_speed)*1023);
        pwm_set_gpio_level(Motor_PWMLeft, speedLeft);
        pwm_set_gpio_level(Motor_PWMRight, speedRight);
        sleep_ms(10);
        }
    if(orientation == "Straight"){
        uint speed = std::ceil((target_speed/max_speed)*1023);
        pwm_set_gpio_level(Motor_PWMLeft, speed);
        pwm_set_gpio_level(Motor_PWMRight, speed);
        sleep_ms(10);
        }
    

}

void initialize_uart(){
    // Initialize chosen serial port
    uart_init(UART_ID, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(UART_ID, false, false);

    // Set data format
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(UART_ID, false);
}

void receive_input(char motion_info_[MAX_LINE_LENGTH], int index){

    while (true) {
        char input = getchar_timeout_us(10000); // Non-blocking read with timeout
        if (input != PICO_ERROR_TIMEOUT) {
            if (input == '\n') {
                // Null-terminate the received string
                motion_info_[MAX_LINE_LENGTH-1] = '\0';
                printf("Received message: %s\n", motion_info_); // Print the received line
                index = 0; // Reset the index for the next line
                break;
            } else {
                if (index < MAX_LINE_LENGTH - 1) {
                    motion_info_[index++] = input; // Store the character in the buffer
                    // printf ("no xter: %s \n", input);
                    // printf("Entering xter\n");
                } else {
                    // Buffer overflow, reset the index
                    printf("Error: Input line too long\n");
                    index = 0;
                    break;
                }
            }
        }
        sleep_ms(10); // Delay to prevent overwhelming the CPU
        // printf("no character\n");
    }
     // Ensure the char array is null-terminated
    // printf("no character\n");
    // printf ("no character: %s \n", motion_info_);
    //motion_info_[MAX_LINE_LENGTH-1] = '\0';
}

std::string receive_uart_message(){
    char buffer[MAX_LINE_LENGTH];
    int index = 0;
    // Read data from UART
    std::string message;
    while (uart_is_readable(UART_ID)) {

        char ch = uart_getc(UART_ID);
        // Add the character to the buffer if it is not the end of message character
        if (ch == '\n' || index >= sizeof(buffer) - 1) {
            buffer[index] = '\0'; // Null-terminate the string
            break;
        }
        buffer[index++] = ch;
        printf ("our data 1-: %s \n", buffer[index]);
    }

    // Process the received message if it's non-empty
    if (index > 0) {
        std::string message(buffer);
        std::cout << "Received message: " << message << std::endl;

        // Reset buffer index for the next message
        index = 0;
            }
    return message;
    }



std::vector<std::string> split_received_data( std::string motion_info){
    //char motion_info_[MAX_LINE_LENGTH]
    //printf ("our data 1: %s \n", motion_info.c_str());
    std::stringstream stream(motion_info);
    //printf ("our data 2: %s \n", s);
    std::vector<std::string> words;
    std::string word;

    // Extract words separated by spaces
    while (stream >> word) {
        words.push_back(word);
    }
    /*
    printf ("our data splitted: %s \n", words[0]);
    // Print the results
    for (const auto& w : words) {
        // std::cout << word << std::endl;
        printf ("our data splitted: %s \n", w.c_str());
    }
    */
    return words;
}
