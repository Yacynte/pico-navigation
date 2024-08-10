# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
   set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(PICO_SDK_PATH ${USERHOME}/.pico-sdk/sdk/1.5.1)
set(PICO_TOOLCHAIN_PATH ${USERHOME}/.pico-sdk/toolchain/13_2_Rel1)
if(WIN32)
    set(pico-sdk-tools_DIR ${USERHOME}/.pico-sdk/tools/1.5.1)
    include(${pico-sdk-tools_DIR}/pico-sdk-tools-config.cmake)
    include(${pico-sdk-tools_DIR}/pico-sdk-tools-config-version.cmake)
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)


if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(agrobot C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(${PROJECT_NAME} 
                src/agrobot.cpp
                src/functions.cpp)

pico_set_program_name(agrobot "agrobot")
pico_set_program_version(agrobot "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(agrobot 0)
pico_enable_stdio_usb(agrobot 1)

# Add the standard library to the build
target_link_libraries(agrobot 
        #usb_serial 
        #tinyusb_device 
        #tinyusb_board
        pico_stdio_usb
        hardware_gpio
        hardware_pio
        hardware_pwm
        pico_stdlib
        hardware_i2c
        hardware_spi
        #pico_cyw43_arch_none
        #pico_cyw43_arch_lwip_threadsafe_background
        #pico_cyw43_arch_lwip_poll
        )


# Add the standard include files to the build
target_include_directories(agrobot PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
#target_link_libraries(agrobot 
#        hardware_spi
#        hardware_i2c
#        pico_cyw43_arch_none
#        )

# Enable USB CDC in TinyUSB
#target_compile_definitions(agrobot PRIVATE
#    PICO_STDIO_USB=1
#    PICO_STDIO_UART=0
#    CFG_TUD_CDC=1
#)

pico_add_extra_outputs(agrobot)


