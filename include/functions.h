#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
// #include "pico/cyw43_arch.h"
#include "hardware/vreg.h"
#include "hardware/clocks.h"
#include <cctype> 


// UART configuration
#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// UART pins
#define UART_TX_PIN 0
#define UART_RX_PIN 1


const int  MAX_LINE_LENGTH = 256;
// Motor pins
#define Left_Motor_IN1 2
#define Left_Motor_IN2 3
#define Right_Motor_IN3 4
#define Right_Motor_IN4 5
#define ENA_M 16  // PWM pin for motor A
#define ENB_M 17  // PWM pin for motor B

// Brake pins
#define Left_Brake_IN1 10
#define Left_Brake_IN2 11
#define Right_Brake_IN3 12
#define Right_Brake_IN4 13
#define ENA_B 14  // PWM pin for motor A
#define ENB_B 15  // PWM pin for motor B


// Motors initialization
void init_brake_pins();
void init_motor_pins();

// PWM initialization
void init_motor_pins();

// Initialize UART
void initialize_uart();

//move Robot
void move_robot( std::string direction, uint speed, uint angular_speed);

//Brake Robot
void brake_robot( std::string direction, uint speed, uint angular_speed);

// USB Communication 
void cdc_task();

std::vector<std::string>  split_received_data(std::string motion_info);

void receive_input(char motion_info_[MAX_LINE_LENGTH], int index = 0);

std::string receive_uart_message();
