/**
 * \file main.c
 * \brief Main function for the vending machine project.
 * \details This main file initializes the vending machine and configures the buttons and LEDs.
 * It defines the callback functions for button presses and handles the corresponding actions. 
 * Additionally, it provides a function to print the current status of the vending machine.
 *
 * The vending machine can be controlled with four buttons and there are four status LEDs.
 * Button 1 is used to insert 1 credit, button 2 is used to insert 2 credits, button 3
 * is used to browse products, and button 4 is used to confirm a product selection.
 * LEDs indicate the status of the vending machine, such as product selected or product/refund availability.
 *
 * \authors Guilherme Guarino 104154, Simão Pinto 102776
 * \date 05/2024
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include "../src/sc_types.h"
#include "../src-gen/VendingMachine.h"
#include "config.h"


void print_status() {
	// Print current credit and product information
	printk("\n==============================\n");
    printk("Current credit: %d\n", vm.internal.Credit);
	printk("Selected product: %d\n", vm.internal.Product);
	printk("Price of selected product: %d\n", vm.internal.Price);
	printk("==============================\n");
}

void button0_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	// Check if vending machine is in states that should not respond to button 0 presses
	if (vendingMachine_is_state_active(&vm, VendingMachine_main_region_Return_Credit) || vendingMachine_is_state_active(&vm, VendingMachine_main_region_Dispense))
		return;

    vendingMachine_but1_raise_insert(&vm);
    printk("\nInserted 1 credit\n");

	print_status();
}

void button1_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	// Check if vending machine is in states that should not respond to button 1 presses
	if (vendingMachine_is_state_active(&vm, VendingMachine_main_region_Return_Credit) || vendingMachine_is_state_active(&vm, VendingMachine_main_region_Dispense))
		return;

    vendingMachine_but2_raise_insert(&vm);
    printk("\nInserted 2 credits\n");

	print_status();
}

void button2_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	// Check if vending machine is in states that should not respond to button 2 presses
	if (vendingMachine_is_state_active(&vm, VendingMachine_main_region_Return_Credit) || vendingMachine_is_state_active(&vm, VendingMachine_main_region_Dispense))
		return;
		
    vendingMachine_but3_raise_browse(&vm);
    printk("\nBrowsing products...\n");

	// Set LED 1 status
	if (vendingMachine_led1_get_power(&vm) == 1) {
		gpio_pin_set_dt(&led0, 1);  // LED 1 active
	} else {
		gpio_pin_set_dt(&led0, 0);  // LED 1 inactive
	}

	// Set LED 2 status
	if (vendingMachine_led2_get_power(&vm) == 1) {
		gpio_pin_set_dt(&led1, 1);  // LED 2 active
	} else {
		gpio_pin_set_dt(&led1, 0);  // LED 2 inactive
	}

	print_status();
}

void button3_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	// Check if there is not enough credit to buy the product
	if (vm.internal.Credit < vm.internal.Price && vm.internal.Product > 0) {
		printk("\nProduct costs %d credit. Please insert credit.\n", vm.internal.Price);
		print_status();
		return;
	}

	// Check if there is not any credit to refund
	if (vm.internal.Product == 0 && vm.internal.Credit <= 0) {
		printk("\nThere is no credit to refund!\n");
		print_status();
		return;
	}

    printk("\nSelected product.\n");
	
	// If button 3 was not pressed before, prompt to press again to confirm
	if (!button3_pressed_once) {
		printk("\nPress again to confirm.\n");
		button3_pressed_once = true;
	} else {
		if (vm.internal.Credit >= vm.internal.Price && vm.internal.Product > 0)
			printk("\nProduct bought for %d credit.\n", vm.internal.Price);

		if (vm.internal.Product == 0 && vm.internal.Credit > 0)
			printk("\nRefunded %d credit!\n", vm.internal.Credit);

		button3_pressed_once = false;
	}

	vendingMachine_but4_raise_enter(&vm);
	
	// Set LED 3 status
	if (vendingMachine_led3_get_power(&vm) == 1) {
		gpio_pin_set_dt(&led2, 1);  // LED 3 active
	} else {
		gpio_pin_set_dt(&led2, 0);  // LED 3 inactive
	}

	// Set LED 4 status
	if (vendingMachine_led4_get_power(&vm) == 1) {
		gpio_pin_set_dt(&led3, 1);  // LED 4 active
	} else {
		gpio_pin_set_dt(&led3, 0);  // LED 4 inactive
	}

	print_status();
}

int leds_configure()
{
	int ret;

	if (!device_is_ready(led0.port)) {
		return CONFIG_FAILURE;
	}

    if (!device_is_ready(led1.port)) {
		return CONFIG_FAILURE;
	}

    if (!device_is_ready(led2.port)) {
		return CONFIG_FAILURE;
	}

    if (!device_is_ready(led3.port)) {
		return CONFIG_FAILURE;
	}

	ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return CONFIG_FAILURE;
	}

	ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return CONFIG_FAILURE;
	}

	ret = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return CONFIG_FAILURE;
	}

	ret = gpio_pin_configure_dt(&led3, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return CONFIG_FAILURE;
	}

	return CONFIG_SUCCESS;
}

int buttons_configure()
{
	int ret;

	if (!device_is_ready(button0.port)) {
		return CONFIG_FAILURE;
	}

	if (!device_is_ready(button1.port)) {
		return CONFIG_FAILURE;
	}

	if (!device_is_ready(button2.port)) {
		return CONFIG_FAILURE;
	}

	if (!device_is_ready(button3.port)) {
		return CONFIG_FAILURE;
	}

	ret = gpio_pin_configure_dt(&button0, GPIO_INPUT);
	if (ret < 0) {
		return CONFIG_FAILURE;
	}

	ret = gpio_pin_configure_dt(&button1, GPIO_INPUT);
	if (ret < 0) {
		return CONFIG_FAILURE;
	}

	ret = gpio_pin_configure_dt(&button2, GPIO_INPUT);
	if (ret < 0) {
		return CONFIG_FAILURE;
	}

	ret = gpio_pin_configure_dt(&button3, GPIO_INPUT);
	if (ret < 0) {
		return CONFIG_FAILURE;
	}

	ret = gpio_pin_interrupt_configure_dt(&button0, GPIO_INT_EDGE_TO_ACTIVE );
    ret = gpio_pin_interrupt_configure_dt(&button1, GPIO_INT_EDGE_TO_ACTIVE );
    ret = gpio_pin_interrupt_configure_dt(&button2, GPIO_INT_EDGE_TO_ACTIVE );
    ret = gpio_pin_interrupt_configure_dt(&button3, GPIO_INT_EDGE_TO_ACTIVE );

	return CONFIG_SUCCESS;
}

void init_callback()
{
	gpio_init_callback(&button0_cb_data, button0_pressed, BIT(button0.pin));
    gpio_init_callback(&button1_cb_data, button1_pressed, BIT(button1.pin));
    gpio_init_callback(&button2_cb_data, button2_pressed, BIT(button2.pin)); 
    gpio_init_callback(&button3_cb_data, button3_pressed, BIT(button3.pin));
}

void add_callback()
{
	gpio_add_callback(button0.port, &button0_cb_data);
    gpio_add_callback(button1.port, &button1_cb_data);
    gpio_add_callback(button2.port, &button2_cb_data);
    gpio_add_callback(button3.port, &button3_cb_data); 
}

// Main function
int main(void) {

    // Check if LED configuration fails
    if (leds_configure() == CONFIG_FAILURE) {
        printk("\nLEDs configuration failed! Aborting...\n");
        return -1;
    }

    // Check if button configuration fails
    if (buttons_configure() == CONFIG_FAILURE) {
        printk("\nButtons configuration failed! Aborting...\n");
        return -1;
    }

    // Initialize button callback functions
    init_callback();

    // Add button callbacks to GPIO
    add_callback();

    // Initialize vending machine
    vendingMachine_init(&vm);

    // Enter initial state of the vending machine
    vendingMachine_enter(&vm);

    // Print initial status of the vending machine
    print_status();

    return 0;
}