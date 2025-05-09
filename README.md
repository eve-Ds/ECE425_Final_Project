# ECE425_Final_Project


# Introduction
This project was inspired by a ballerina music box. This project utilizes the Texas Instruments Tiva C Series TM4C123GH6PM
microcontroller to communicate with a BLE module, an Arduino MKR Zero board, and a stepper motor. The music box allows users to select any song available in the SD card via Bluetooth. When the user enters a song title, the Zero board plays the music and the stepper motor will begin to spin. The stepper motor stops when the song is paused and spins again when the song is resumed. 

# Background and Methodology



# Block Diagram
![image](https://github.com/user-attachments/assets/31872491-df78-43a7-9c28-ebdff529e089)

# Components Used


# Pinout Plan
| Tiva TM4C123G Launch Pad |      BLE         | 
|:-------------------------|:----------------:|
|           PB7            | UART MOD (Pin 1) |
|           GND            | UART CTS (Pin 2) |
|         PB0 (U1RX)       | UART TXO (Pin 3) |
|         PB1 (U1TX)       | UART RXI (Pin 4) |
|         VCC (3.3V)       | UART Vin (Pin 5) |
|           GND            | UART GND (Pin 7) |
 





