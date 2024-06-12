/**
 * @file RTDB.h
 * @brief Header file for Real-Time Database (RTDB) implementation.
 * 
 * This file contains the data structures and function prototypes for
 * managing the RTDB, which stores the state of buttons, LEDs, and
 * an analog sensor in a real-time embedded system.
 *
 * \authors Guilherme Guarino 104154, Simão Pinto 102776 - 06/2024
 *
 */

#ifndef RTDB_H
#define RTDB_H

#include <zephyr/kernel.h>
#include <stdint.h>

/**
 * @brief Structure for storing I/O data in RTDB.
 */
typedef struct {
    uint32_t button_state[4];	/**< Array to store the state of 4 buttons. */
    uint32_t led_state[4];	/**< Array to store the state of 4 LEDs. */
    int16_t analog_value_raw;	/**< Raw value from the analog sensor. */
    int analog_value;		/**< Processed value from the analog sensor. */
}rtdb;

extern rtdb io_data;	/**< Global RTDB instance. */


// Function prototypes:

/**
 * @brief Initialize the RTDB.
 */
void rtdb_init(void);

/**
 * @brief Read the state of the buttons from the RTDB.
 * 
 * @param states Pointer to an array where the button states will be stored.
 */
void read_button_states(uint32_t *states);

/**
 * @brief Write the state of the buttons to the RTDB.
 * 
 * @param states Pointer to an array containing the button states to be written.
 */
void write_button_states(uint32_t *states);

/**
 * @brief Read the state of the LEDs from the RTDB.
 * 
 * @param states Pointer to an array where the LED states will be stored.
 */
void read_led_states(uint32_t *states);

/**
 * @brief Write the state of the LEDs to the RTDB.
 * 
 * @param states Pointer to an array containing the LED states to be written.
 */
void write_led_states(uint32_t *states); 

/**
 * @brief Read the raw value of the analog sensor from the RTDB.
 * 
 * @return The raw value of the analog sensor.
 */
int16_t read_raw_value(void);

/**
 * @brief Read the processed value of the analog sensor from the RTDB.
 * 
 * @return The processed value of the analog sensor.
 */
int read_analog_value(void);

/**
 * @brief Write the raw value of the analog sensor to the RTDB.
 * 
 * @param raw The raw value to be written.
 */
void write_raw_value(uint16_t raw) ;

/**
 * @brief Write the processed value of the analog sensor to the RTDB.
 * 
 * @param value The processed value to be written.
 */
void write_analog_value(int value);

#endif // RTDB_H
