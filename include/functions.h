#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
// #include "pico/cyw43_arch.h"
#include "hardware/vreg.h"
#include "hardware/clocks.h"
#include <cctype> 
#include "hardware/adc.h"
#include "hardware/pwm.h"

// UART configuration
#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// UART pins
#define UART_TX_PIN 0
#define UART_RX_PIN 1

// Motor pins

#define Motor_INLeft 2
#define Motor_INRight 3
#define Motor_PWMLeft 4     // PWM pin for motor Left
#define Motor_PWMRight 5   // PWM pin for motor Right
#define Motor_BrakeLeft 6
#define Motor_BrakeRight 7
#define Motor_PWMBrake 8
#define Brake_FEEDBACK_PIN 9  // Potentiometer or encoder

const int  MAX_LINE_LENGTH = 256;
const float radius = 0.2;  // m
const float speed_diff = 0.1; // Km/h
const float ang_speed_diff = 1; // deg/s
const float max_speed = 3.6; // Km/h
const float mass = 125; // kg
const float rho = 1062; // kg/m3
const float g = 9.81; // m/s2
const float A_brakePad = 0.005; // m2 adjustable
const float actuator_speed = 0.06; // m/s adjustable
const float time_to_brake = 2; // s, time to brake

// Motors initialization
void init_motor_pins();

// Initialize UART
void initialize_uart();

std::vector<std::string>  split_received_data(std::string motion_info);

void receive_input(char motion_info_[MAX_LINE_LENGTH], int index = 0);

std::string receive_uart_message();

//move Robot
void move_robot_non_L298N( std::string motion_info);

//brake robot
void brake();

//std::vector<uint> get_current_speeds();