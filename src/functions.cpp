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


/*
// Function to handle incoming data
void cdc_task() {
    if (tud_cdc_connected() && tud_cdc_available()) {
        char buf[64];
        uint32_t count = tud_cdc_read(buf, sizeof(buf));
        buf[count] = '\0'; // Null-terminate the received string
        printf("Received: %s\n", buf);
        tud_cdc_write(buf, count); // Echo back to the host
        tud_cdc_write_flush();
    }
}

void init_pwm(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice_num, 255); // Set the PWM period to 256 cycles (0-255)
    pwm_set_enabled(slice_num, true);
}

void init_motor_pins() {
    gpio_init(Left_Motor_IN1);
    gpio_set_dir(Left_Motor_IN1, GPIO_OUT);
    gpio_init(Left_Motor_IN2);
    gpio_set_dir(Left_Motor_IN2, GPIO_OUT);
    gpio_init(Right_Motor_IN3);
    gpio_set_dir(Right_Motor_IN3, GPIO_OUT);
    gpio_init(Right_Motor_IN4);
    gpio_set_dir(Right_Motor_IN4, GPIO_OUT);
    
    gpio_set_function(ENA_M, GPIO_FUNC_PWM);
    gpio_set_function(ENB_M, GPIO_FUNC_PWM);
}

void init_brake_pins() {
    gpio_init(Left_Brake_IN1);
    gpio_set_dir(Left_Brake_IN1, GPIO_OUT);
    gpio_init(Left_Brake_IN2);
    gpio_set_dir(Left_Brake_IN2, GPIO_OUT);
    gpio_init(Right_Brake_IN3);
    gpio_set_dir(Right_Brake_IN3, GPIO_OUT);
    gpio_init(Right_Brake_IN4);
    gpio_set_dir(Right_Brake_IN4, GPIO_OUT);
    
    gpio_set_function(ENA_B, GPIO_FUNC_PWM);
    gpio_set_function(ENB_B, GPIO_FUNC_PWM);
}

void move_robot_L298N( std::string direction, uint speed, uint angular_speed){
    brake_robot_L298N("stop", 0, 0);
    if (direction.empty()){
        std::cerr<<"No Moving state given";
        exit(0);
    }
    else if (direction == "forward" || direction == "backward"){
        uint speed_left = speed;
        uint speed_right = speed + angular_speed;
        bool forward = true;
        if (direction == "backward"){ forward = false;}
        
        gpio_put(Left_Motor_IN1, forward ? 1 : 0);
        gpio_put(Left_Motor_IN2, forward ? 0 : 1);
        gpio_put(Right_Motor_IN3, forward ? 1 : 0);
        gpio_put(Right_Motor_IN4, forward ? 0 : 1);
        uint slice_num = pwm_gpio_to_slice_num(ENA_M);
        pwm_set_gpio_level(ENA_M, speed_left);
        slice_num = pwm_gpio_to_slice_num(ENB_M);
        pwm_set_gpio_level(ENB_M, speed_right);
    }
    else if (direction == "stop"){
        uint speed_left = 0;
        uint speed_right = 0;
        gpio_put(Left_Motor_IN1, 0);
        gpio_put(Left_Motor_IN2, 0);
        gpio_put(Right_Motor_IN3, 0);
        gpio_put(Right_Motor_IN4, 0);
        uint slice_num = pwm_gpio_to_slice_num(ENA_M);
        pwm_set_gpio_level(ENA_M, speed_left);
        slice_num = pwm_gpio_to_slice_num(ENB_M);
        pwm_set_gpio_level(ENB_M, speed_right);
    }    
}

void brake_robot_L298N(std::string direction, uint speed, uint angular_speed){
    move_robot_L298N("stop", 0, 0);
    if (direction.empty()){
        std::cerr<<"No Moving state given";
        exit(0);
    }
    else if (direction == "forward" || direction == "backward"){
        uint speed_left = speed;
        uint speed_right = speed + angular_speed;
        bool forward = false;
        if (direction == "backward"){ forward = true;}
        
        gpio_put(Left_Brake_IN1, forward ? 1 : 0);
        gpio_put(Left_Brake_IN2, forward ? 0 : 1);
        gpio_put(Right_Brake_IN3, forward ? 1 : 0);
        gpio_put(Right_Brake_IN4, forward ? 0 : 1);
        uint slice_num = pwm_gpio_to_slice_num(ENA_B);
        pwm_set_gpio_level(ENA_B, speed_left);
        slice_num = pwm_gpio_to_slice_num(ENB_B);
        pwm_set_gpio_level(ENB_B, speed_right);
    }
    else if (direction == "stop"){
        uint speed_left = 0;
        uint speed_right = 0;
        gpio_put(Left_Brake_IN1, 0);
        gpio_put(Left_Brake_IN2, 0);
        gpio_put(Right_Brake_IN3, 0);
        gpio_put(Right_Brake_IN4, 0);
        uint slice_num = pwm_gpio_to_slice_num(ENA_B);
        pwm_set_gpio_level(ENA_B, speed_left);
        slice_num = pwm_gpio_to_slice_num(ENB_B);
        pwm_set_gpio_level(ENB_B, speed_right);
    }    
}
*/

void init_motor_pins() {
    gpio_init(Motor_IN1);
    gpio_set_dir(Motor_IN1, GPIO_OUT);
    gpio_init(Motor_IN2);
    gpio_set_dir(Motor_IN2, GPIO_OUT);
    gpio_init(Motor_PWM1);
    gpio_set_dir(Motor_PWM1, GPIO_OUT);
    gpio_init(Motor_PWM2);
    gpio_set_dir(Motor_PWM2, GPIO_OUT);

    // Set up PWM
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);  // Adjust clock divider as needed
    pwm_init(pwm_gpio_to_slice_num(Motor_PWM1), &config, true);
    pwm_init(pwm_gpio_to_slice_num(Motor_PWM2), &config, true);
}

void move_robot_non_L298N( std::string direction, uint speed, uint angular_speed){
    if (direction == "forward"){
        gpio_put(Motor_IN1, 1);
        gpio_put(Motor_IN2, 0);
    }
    else if (direction == "backward"){
        gpio_put(Motor_IN1, 0);
        gpio_put(Motor_IN2, 1);
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
