/**
 * \defgroup sensor Smart Sensor Module (sensor)
 *
 * \details This module implements the UART communication and command processing functionalities
 * for the smart sensor. It allows the sensor to interact with external devices and systems
 * by sending and receiving commands via UART interface.
 * 
 * The smart sensor module provides the following features:
 *   - Initialization of UART communication buffers.
 *   - Transmission and reception of commands and data via UART.
 *   - Processing of commands received from external sources.
 *   - Emulation of sensor readings for temperature, humidity, and CO2 levels.
 * 
 * The module supports the following operations:
 *   - Initialization of UART buffers and sensor emulation parameters.
 *   - Parsing and processing of UART commands.
 *   - Generation of appropriate responses to commands.
 *   - Handling of UART interrupts and data transmission.
 *   - Calculation of checksums for command validation.
 * 
 * \note All communications are ASCII-based, allowing full interaction with the sensor
 * via a terminal or serial communication interface.
 *
 * \authors Guilherme Guarino 104154, Simão Pinto 102776 - 03/2024
 *
 */


#ifndef SENSOR_H
#define SENSOR_H

#include <stdio.h>
#include <stdlib.h>

/** @{ */

// ================================================================================== //

#define LAST_SAMPLES 20 /**< Number of last samples to return */
#define BUF_SIZE 500   /**< Size of the circular buffer */
#define SOF_SYM '#' /**< Start of Frame symbol */
#define EOF_SYM '!' /**< End of Frame symbol */

/**
 * \brief Structure representing a circular buffer for UART communication.
 */
typedef struct {
    unsigned char data[BUF_SIZE];    /**< Buffer data */
    unsigned int head;  /**< Head index of the buffer */
    unsigned int tail;  /**< Tail index of the buffer */
    unsigned int count; /**< Number of elements in the buffer */
} circularBuffer;

/**
 * \brief Structure representing sensor data.
 */
typedef struct {
    int temp; /**< Temperature */
    unsigned int humidity; /**< Humidity */
    unsigned int co2; /**< CO2 level */
} Data;

extern circularBuffer rxb; /**< Reception buffer */
extern circularBuffer txb; /**< Transmission buffer */

/**
 * \brief Initializes the circular buffer for UART communication.
 * 
 * \details This function initializes the circular buffer used for UART reception and transmission.
 * 
 * The function sets the head, tail, and count of the circular buffer to zero, effectively clearing the buffer.
 */
void init_buffer();

/**
 * \brief Puts a character into the circular buffer for UART transmission.
 *
 * \details This function adds a character to the circular buffer for UART transmission.
 * 
 * If the buffer is not full, the character is appended to the buffer, and the tail index is updated accordingly.
 * If the buffer is full, the character is not added, and no action is taken.
 * 
 * \param c The character to be put into the buffer.
 */
void buffer_putc(unsigned char c);

/**
 * \brief Gets a character from the circular buffer.
 *
 * \details This function retrieves a character from the circular buffer for UART reception.
 * 
 * If the buffer is not empty, the function returns the character at the head index and updates the head index accordingly.
 * If the buffer is empty, the function returns \c NULL (0).
 * 
 * \return The character read from the buffer.
 */
unsigned char buffer_getc();

/**
 * \brief Processes the received command and generates appropriate responses.
 *
 * \details This function interprets the command character received via UART and generates appropriate responses.
 * 
 * The function processes the command character along with any additional arguments and performs the necessary actions.
 * It also checks if the command is valid and was successfully processed.
 * 
 * \param c The command character.
 * \param ch Additional argument for certain commands.
 * \return \c 0 if successful, \c -1 otherwise.
 */
int process_command(unsigned char cmd, unsigned char ch);

/**
 * \brief Handles UART "interrupts" and manages data transmission.
 *
 * \details This function is responsible for managing UART interrupts and transmitting data from the circular buffer.
 * 
 * When called, the function checks if there is data available in the transmission buffer.
 * If data is available, it moves the data from the transmission buffer to the UART transmission register.
 * This process continues until the transmission buffer is empty.
 */
void uart_handler();

/**
 * \brief Calculates the checksum for a command and its data.
 * 
 * \details This function calculates the checksum value for a command and its associated data.
 * 
 * The checksum is computed by summing the numerical values of the command character and each byte of the data array.
 *
 * \param cmd The command character.
 * \param data The data associated with the command.
 * \return The calculated checksum integer.
 */
int calc_checksum(unsigned char cmd, unsigned char ch, const char *data);

/** @} */ // End of sensor module

#endif /* SENSOR_H */
