/**
 * \file config.h
 * \brief Configuration file.
 * \details This file contains configuration parameters and function prototypes for the vending machine project.
 * 
 * It defines GPIO pins, initializes callback functions for button presses, and configures LEDs and buttons.
 *
 * \authors Guilherme Guarino 104154, Simão Pinto 102776
 * \date 05/2024
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include "../src/sc_types.h"
#include "../src-gen/VendingMachine.h"

/** @{ */

#define CONFIG_FAILURE 0    // Configuration failure status
#define CONFIG_SUCCESS 1    // Configuration success status

#define SW0_NODE	DT_ALIAS(sw0)   // Button 0 node
#define SW1_NODE	DT_ALIAS(sw1)   // Button 1 node
#define SW2_NODE	DT_ALIAS(sw2)   // Button 2 node
#define SW3_NODE	DT_ALIAS(sw3)   // Button 3 node

#define LED0_NODE DT_ALIAS(led0)    // LED 0 node
#define LED1_NODE DT_ALIAS(led1)    // LED 1 node
#define LED2_NODE DT_ALIAS(led2)	// LED 2 node
#define LED3_NODE DT_ALIAS(led3)	// LED 3 node

static const struct gpio_dt_spec button0 = GPIO_DT_SPEC_GET(SW0_NODE, gpios);   // GPIO specification for button 0
static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET(SW1_NODE, gpios);   // GPIO specification for button 1
static const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET(SW2_NODE, gpios);   // GPIO specification for button 2
static const struct gpio_dt_spec button3 = GPIO_DT_SPEC_GET(SW3_NODE, gpios);   // GPIO specification for button 3

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios); // GPIO specification for LED 0
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios); // GPIO specification for LED 1
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios); // GPIO specification for LED 2
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios); // GPIO specification for LED 3

static struct gpio_callback button0_cb_data;    // Callback data for button 0
static struct gpio_callback button1_cb_data;    // Callback data for button 1
static struct gpio_callback button2_cb_data;    // Callback data for button 2
static struct gpio_callback button3_cb_data;    // Callback data for button 3

static bool button3_pressed_once = false; /**< Flag to track if button 3 was pressed */

// Initialize the state machine
VendingMachine vm; /**< Vending machine state machine */

/**
 * \brief Prints current credit and product information.
 */
void print_status();

/**
 * \brief Callback function triggered when button 1 is pressed.
 * \details This function is invoked when button 1 is pressed. It raises an event to indicate 
 * that credit should be inserted into the vending machine, and updates the status accordingly.
 *
 * \param dev Pointer to the device structure representing the button.
 * \param cb Pointer to the callback structure associated with the button.
 * \param pins Bitmask representing the pin(s) associated with the button.
 */
void button0_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins);

/**
 * \brief Callback function triggered when button 2 is pressed.
 * \details This function is invoked when button 2 is pressed. It raises an event to indicate 
 * that 2 credits should be inserted into the vending machine, and updates the status accordingly.
 *
 * \param dev Pointer to the device structure representing the button.
 * \param cb Pointer to the callback structure associated with the button.
 * \param pins Bitmask representing the pin(s) associated with the button.
 */
void button1_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins);

/**
 * \brief Callback function triggered when button 3 is pressed.
 * \details This function is invoked when button 3 is pressed. It raises an event to indicate 
 * that the user wants to browse products, and updates the status accordingly.
 *
 * \param dev Pointer to the device structure representing the button.
 * \param cb Pointer to the callback structure associated with the button.
 * \param pins Bitmask representing the pin(s) associated with the button.
 */
void button2_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins);

/**
 * \brief Callback function triggered when button 4 is pressed.
 * \details This function is invoked when button 4 is pressed. It raises an event to indicate 
 * that the user has selected a product, and updates the status accordingly.
 *
 * \param dev Pointer to the device structure representing the button.
 * \param cb Pointer to the callback structure associated with the button.
 * \param pins Bitmask representing the pin(s) associated with the button.
 */
void button3_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins);


/**
 * \brief Configures LEDs.
 * \return \c CONFIG_SUCCESS if configuration succeeds, \c CONFIG_FAILURE otherwise.
 */
int leds_configure();

/**
 * \brief Configures buttons.
 * \return \c CONFIG_SUCCESS if configuration succeeds, \c CONFIG_FAILURE otherwise.
 */
int buttons_configure();

/**
 * \brief Initializes callback functions.
 */
void init_callback();

/**
 * \brief Adds callback functions to buttons.
 */
void add_callback(); 

/** @} */ // End of sensor module

#endif /* CONFIG_H */