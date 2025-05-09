# Introduction
This project was inspired by a ballerina music box. This project utilizes the Texas Instruments Tiva C Series TM4C123GH6PM
microcontroller to communicate with a BLE module, an Arduino MKR Zero board, and a stepper motor. The music box allows users to select any song available in the SD card via Bluetooth. When the user enters a song title, the Zero board plays the music and the stepper motor will begin to spin. The stepper motor stops when the song is paused and spins again when the song is resumed. 

# Background and Methodology
Hardware and software integration will be needed for this project. The embedded systems concepts applied include C programming, GPIO, timers, interrupts, SysTick Delay, and UART. UART facilitates communication between the TM4C123G LaunchPad, the BLE module, and the Arduino MKR Zero board. GPIO controls the stepper motor's direction and movement, while the timers and SysTick delays manage both the BLE module and the stepper motor's speed and timing.

# Block Diagram
<img src = "https://github.com/user-attachments/assets/31872491-df78-43a7-9c28-ebdff529e089" width = "600" />

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

| Tiva TM4C123G LaunchPad  |      BLE         |  
|:-------------------------|:----------------:|      
|           PB7            | UART MOD (Pin 1) |  
|           GND            | UART CTS (Pin 2) |   
|         PB0 (U1RX)       | UART TXO (Pin 3) |
|         PB1 (U1TX)       | UART RXI (Pin 4) |
|         VCC (3.3V)       | UART Vin (Pin 5) |
|           GND            | UART GND (Pin 7) |

| Tiva TM4C123G LaunchPad  | Arduino MKR Zero | 
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

| Tiva TM4C123G LaunchPad  | ULN2003 Stepper Motor Drive | 
|:-------------------------|:---------------------------:|
|            PA2           |             IN1             |
|            PA3           |             IN2             |
|            PA4           |             IN3             |
|            PA5           |             IN4             |

# Analysis and Results
The music box can connect to the BLE through the Bluefruit Connect app when the Arduino MKR Zero board is powered on. Users can enter a song name, which will then be checked to determine if it is a valid WAV file on the SD card. Once a valid WAV file is found, the music begins to play and the motor starts to spin. Users can also adjust the volume and pause or resume the song. If the user enters "PAUSE," the music will stop and the motor will come to a halt. When the user enters "RESUME," the music and motor will continue from where they left off. Video Demonstration is shown below: 

[Music Box Results](https://www.canva.com/design/DAGm7YwPNNw/MNcKtzlYKJV5YfbCSA-QCQ/watch?utm_content=DAGm7YwPNNw&utm_campaign=designshare&utm_medium=link2&utm_source=uniquelinks&utlId=h0fc30edceb)

Inside the music box:

<img src = "https://github.com/user-attachments/assets/281a8b80-f496-4449-b6a1-682572280bcb" width = "200"> <img src = "https://github.com/user-attachments/assets/d72f9a73-b11b-4b2c-b418-24d5b7dfa0b5" width = "200" >

Some challenges I encountered included synchronizing the start of the motor and the song. I had to experiment with the delays to ensure that the motor starts as soon as the song begins to play. While I was able to synchronize the pause function for both the motor and the song, there is still a slight delay between their start times. I also faced issues with the Arduino IDE. When I connected the MKR Zero board to my laptop, there were times where the IDE did not recognize the port, even though the board was connected and powered on. 

Although the main objective was achieved, which was playing music while having the motor spin along with it, there are a few areas for improvement. Currently, the motor starts spinning when a character is sent to the BLE module, rather than only spinning when a valid WAV file is detected. Another improvement would be to have the motor stop once the song ends; right now, the motor continues spinning even after the music has finished playing. 








