#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include "../src/sc_types.h"
#include "../src-gen/assignment3.h"
#include "main.h"


#define SW0_NODE	DT_ALIAS(sw0)
#define SW1_NODE	DT_ALIAS(sw1)
#define SW2_NODE	DT_ALIAS(sw2)
#define SW3_NODE	DT_ALIAS(sw3)

static const struct gpio_dt_spec button0 = GPIO_DT_SPEC_GET(SW0_NODE, gpios);
static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET(SW1_NODE, gpios);
static const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET(SW2_NODE, gpios);
static const struct gpio_dt_spec button3 = GPIO_DT_SPEC_GET(SW3_NODE, gpios);

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)	
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

static struct gpio_callback button0_cb_data;
static struct gpio_callback button1_cb_data;
static struct gpio_callback button2_cb_data;
static struct gpio_callback button3_cb_data;

static bool button3_pressed_once = false;

// Initialize the state machine
Assignment3 vendingMachine;

void print_status(){
	// Print current credit and product information
	printk("\n==============================\n");
    printk("Current credit: %d\n", vendingMachine.internal.Credit);
	printk("Selected product: %d\n", vendingMachine.internal.Product);
	printk("Price of selected product: %d\n", vendingMachine.internal.Price);
	printk("==============================\n");
}

void button0_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	if (assignment3_is_state_active(&vendingMachine, Assignment3_main_region_Return_Credit) || assignment3_is_state_active(&vendingMachine, Assignment3_main_region_Dispense))
		return;

    assignment3_but1_raise_insert(&vendingMachine);
    printk("\nInserted 1 credit\n");

	print_status();
}

void button1_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	if (assignment3_is_state_active(&vendingMachine, Assignment3_main_region_Return_Credit) || assignment3_is_state_active(&vendingMachine, Assignment3_main_region_Dispense))
		return;

    assignment3_but2_raise_insert(&vendingMachine);
    printk("\nInserted 2 credits\n");

	print_status();
}

void button2_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	if (assignment3_is_state_active(&vendingMachine, Assignment3_main_region_Return_Credit) || assignment3_is_state_active(&vendingMachine, Assignment3_main_region_Dispense))
		return;
		
    assignment3_but3_raise_browse(&vendingMachine);
    printk("\nBrowsing products...\n");

	if (assignment3_led1_get_power(&vendingMachine) == 1) {
		gpio_pin_set_dt(&led0, 1);
	} else {
		gpio_pin_set_dt(&led0, 0);
	}

	if (assignment3_led2_get_power(&vendingMachine) == 1) {
		gpio_pin_set_dt(&led1, 1);
	} else {
		gpio_pin_set_dt(&led1, 0);
	}

	print_status();
}

void button3_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	if (vendingMachine.internal.Credit < vendingMachine.internal.Price && vendingMachine.internal.Product > 0) {
		printk("\nProduct costs %d credit. Please insert credit.\n", vendingMachine.internal.Price);
		print_status();
		return;
	}

	if (vendingMachine.internal.Product == 0 && vendingMachine.internal.Credit <= 0) {
		printk("\nThere is no credit to refund!\n");
		print_status();
		return;
	}

    printk("\nSelected product.\n");
	
	if (!button3_pressed_once) {
		printk("\nPress again to confirm.\n");
		button3_pressed_once = true;
	} else {
		if (vendingMachine.internal.Credit >= vendingMachine.internal.Price && vendingMachine.internal.Product > 0)
			printk("\nProduct bought for %d credit.\n", vendingMachine.internal.Price);

		if (vendingMachine.internal.Product == 0 && vendingMachine.internal.Credit > 0)
			printk("\nRefunded %d credit!\n", vendingMachine.internal.Credit);

		button3_pressed_once = false;
	}

	assignment3_but4_raise_enter(&vendingMachine);

	if (assignment3_led3_get_power(&vendingMachine) == 1) {
		gpio_pin_set_dt(&led2, 1);
	} else {
		gpio_pin_set_dt(&led2, 0);
	}

	if (assignment3_led4_get_power(&vendingMachine) == 1) {
		gpio_pin_set_dt(&led3, 1);
	} else {
		gpio_pin_set_dt(&led3, 0);
	}

	print_status();
}

int leds_configure()
{
	int ret;

	if (!device_is_ready(led0.port)) {
		return -1;
	}

    if (!device_is_ready(led1.port)) {
		return -1;
	}

    if (!device_is_ready(led2.port)) {
		return -1;
	}

    if (!device_is_ready(led3.port)) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&led3, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return -1;
	}

	return 0;
}

int buttons_configure()
{
	int ret;

	if (!device_is_ready(button0.port)) {
		return -1;
	}

	if (!device_is_ready(button1.port)) {
		return -1;
	}

	if (!device_is_ready(button2.port)) {
		return -1;
	}

	if (!device_is_ready(button3.port)) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&button0, GPIO_INPUT);
	if (ret < 0) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&button1, GPIO_INPUT);
	if (ret < 0) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&button2, GPIO_INPUT);
	if (ret < 0) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&button3, GPIO_INPUT);
	if (ret < 0) {
		return -1;
	}

	return 0;
}

int interrupts_configure()
{
	int ret;
	ret = gpio_pin_interrupt_configure_dt(&button0, GPIO_INT_EDGE_TO_ACTIVE );
    ret = gpio_pin_interrupt_configure_dt(&button1, GPIO_INT_EDGE_TO_ACTIVE );
    ret = gpio_pin_interrupt_configure_dt(&button2, GPIO_INT_EDGE_TO_ACTIVE );
    ret = gpio_pin_interrupt_configure_dt(&button3, GPIO_INT_EDGE_TO_ACTIVE );
	return 0;
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

int main(void)
{
	leds_configure();
	buttons_configure();
	interrupts_configure();

	init_callback();

	add_callback();

	assignment3_init(&vendingMachine);
	assignment3_enter(&vendingMachine);
    return 0;
}