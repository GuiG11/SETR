# Mini-Projeto

## Introduction

Welcome to the documentation for **Mini-Projeto**. This project implements a series of threads that interface with buttons, LEDs, and an analog sensor, managing their states via a Real-Time Database (RTDB). The primary aim is to demonstrate the integration of sensor data with real-time processing for IoT applications.

## Overview

The IoT Sensor Network project provides the following features:
- Real-time monitoring and updating of button states.
- Real-time control and updating of LED states.
- Real-time reading and processing of analog sensor values.
- Integration with a Real-Time Database (RTDB) for storing and retrieving sensor and actuator states.

## Documentation Structure

- [Modules](#modules)
- [Data Structures](#data-structures)
- [Files](#files)

## Modules

- **RTDB Module:** Manages the real-time database for storing and retrieving sensor and actuator states.
- **IoT Module:** Integrates with the RTDB to handle reading button states, managing LED states, and processing analog sensor values.


## Data Structures

- **button_states:** An array representing the states of multiple buttons.
- **led_states:** An array representing the states of multiple LEDs.
- **sequence:** Represents the configuration and data for an ADC read sequence.

## Files

- **IoT.c:** Main function file initializing the system and starting the threads.
- **RTDB.h:** Header file defining structures and function prototypes for the Real-Time Database (RTDB) module.
- **RTDB.c:** Implementation of the Real-Time Database (RTDB) module.


## Additional Information

For more details about the functions and usage of the IoT Sensor Network, refer to the documentation provided in the source code and the comments within the individual source files. Each module is designed to operate in a real-time environment, showcasing effective use of threading and database interaction in IoT systems.
