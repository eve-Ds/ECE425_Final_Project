# ECE425_Final_Project


# Introduction
This project was inspired by a ballerina music box. This project utilizes the Texas Instruments Tiva C Series TM4C123GH6PM
microcontroller to communicate with a BLE module, an Arduino MKR Zero board, and a stepper motor. The music box allows users to select any song available in the SD card via Bluetooth. When the user enters a song title, the Zero board plays the music and the stepper motor will begin to spin. The stepper motor stops when the song is paused and spins again when the song is resumed. 

# Background and Methodology
Hardware and software integration will be needed for this project. The embedded systems concepts applied include C programming, GPIO, timers, interrupts, SysTick Delay, and UART. UART facilitates communication between the TM4C123G LaunchPad, the BLE module, and the Arduino MKR Zero board. GPIO controls the stepper motor's direction and movement, while the timers and SysTick delays manage both the BLE module and the stepper motor's speed and timing.

# Block Diagram
![image](https://github.com/user-attachments/assets/31872491-df78-43a7-9c28-ebdff529e089)

# Components Used

|                        Description                     | Quantity |   Manufacturer   |
|:------------------------------------------------------:|:--------:|:----------------:|
|               Tiva C Series TM4C123G LaunchPad         |     1    | Texa Instruments |
|                  USB-A to Micro-USB Cable              |     1    |        N/A       |
|                28BYJ-48 Stepper Motor (5V)             |     1    |        N/A       |
|               ULN2003 Stepper Motor Driver             |     1    |        N/A       |
|           3.3V/5V Breadboard Power Supply Module       |     1    |        N/A       |
|                 Arduino MKR Zero Board                 |     1    |      Arduino     |
|                           SD card                      |     1    |        N/A       |
| Adafruit Bluefruit LE UART Friend Bluetooth Low Energy |     1    |     Adafruit     |
| Adafruit I2S 3W Class D Amplifier Breakout - MAX98357A |     1    |     Adafruit     |

# Pinout Plan

| Tiva TM4C123G Launch Pad |      BLE         | 
|:-------------------------|:----------------:| 
|           PB7            | UART MOD (Pin 1) |
|           GND            | UART CTS (Pin 2) |
|         PB0 (U1RX)       | UART TXO (Pin 3) |
|         PB1 (U1TX)       | UART RXI (Pin 4) |
|         VCC (3.3V)       | UART Vin (Pin 5) |
|           GND            | UART GND (Pin 7) |

| Tiva TM4C123G Launch Pad | Arduino MKR Zero | 
|:-------------------------|:----------------:|
|       PC6 (U3TX)         |        RX        |
|       PC7 (U3RX)         |        TX        |

|     Arduino MKR Zero     |     Amplifier    | 
|:-------------------------|:----------------:|
|           GND            |        GND       |
|           5V             |        Vin       |
|         Pin 3            |        LRC       |
|         Pin 2            |        BCLK      |
|         Pin A6           |        DIN       |

| Tiva TM4C123G Launch Pad | ULN2003 Stepper Motor Drive | 
|:-------------------------|:---------------------------:|
|            PA2           |             IN1             |
|            PA3           |             IN2             |
|            PA4           |             IN3             |
|            PA5           |             IN4             |

# Analysis and Results
[<img src = "https://www.canva.com/design/DAGm7YwPNNw/MNcKtzlYKJV5YfbCSA-QCQ/watch?utm_content=DAGm7YwPNNw&utm_campaign=designshare&utm_medium=link2&utm_source=uniquelinks&utlId=h0fc30edceb" width = "500" height = "200" />](https://www.canva.com/design/DAGm7YwPNNw/MNcKtzlYKJV5YfbCSA-QCQ/watch?utm_content=DAGm7YwPNNw&utm_campaign=designshare&utm_medium=link2&utm_source=uniquelinks&utlId=h0fc30edceb)


# Conclusion







