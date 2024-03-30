# Lab Assignment 2

## Introduction

Welcome to the documentation for **Lab Assignment 2**. This project implements a C module that processes commands received via UART, one character at a time. The module is part of a smart sensor that allows to read temperature, relative humidity and CO2.

## Overview

The Smart Sensor Module provides the following features:
- Initialization of UART communication buffers.
- Transmission and reception of commands and data via UART.
- Processing of commands received from external sources.
- Emulation of sensor readings for temperature, humidity, and CO2 levels.

## Documentation Structure

- [Modules](#modules)
- [Data Structures](#data-structures)
- [Files](#files)

## Modules

- **Sensor:** Implements UART communication and command processing functionalities for the smart sensor.

## Data Structures

- **circularBuffer:** Represents a circular buffer for UART communication.
- **Data:** Represents sensor data for temperature, humidity, and CO2 levels.

## Files

- **sensor.h:** Header file defining structures and function prototypes for the Smart Sensor Module.
- **sensor.c:** Implementation of the Smart Sensor Module.
- **main.c:** Main function file containing the menu-driven program to interact with the Smart Sensor Module.

## Additional Information

For more details about the functions and usage of the Smart Sensor Module, refer to the documentation provided in the source code and the comments within the `sensor.h` and `sensor.c` files.
