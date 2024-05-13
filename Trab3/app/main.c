#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include "../src/sc_types.h"
#include "../src-gen/assignment3.h"


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

void button0_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    assignment3_but1_raise_insert(&vendingMachine);
    printk("\nInserted 1 credit\n");
	vendingMachine.internal.Credit += 1;

	// Print current credit and product information
    printk("\nCurrent credit: %d\n", vendingMachine.internal.Credit);
	printk("Selected product: %d\n", vendingMachine.internal.Product);
	printk("Price of selected product: %d\n", vendingMachine.internal.Price);
}

void button1_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    assignment3_but2_raise_insert(&vendingMachine);
    printk("\nInserted 2 credits\n");
	vendingMachine.internal.Credit += 2;

	// Print current credit and product information
    printk("\nCurrent credit: %d\n", vendingMachine.internal.Credit);
	printk("Selected product: %d\n", vendingMachine.internal.Product);
	printk("Price of selected product: %d\n", vendingMachine.internal.Price);
}

void button2_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    assignment3_but3_raise_browse(&vendingMachine);
    printk("\nBrowsing products...\n");
	if (vendingMachine.internal.Product < 3) {
		vendingMachine.internal.Product += 1;
		vendingMachine.internal.Price += 1;
	} else {
		vendingMachine.internal.Product = 0;
		vendingMachine.internal.Price = 0;
	}

	if (vendingMachine.internal.Product == 1) {
		gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
		gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
	} else if (vendingMachine.internal.Product == 2) {
		gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
		gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
	} else if (vendingMachine.internal.Product == 3) {
		gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
		gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
	} else if (vendingMachine.internal.Product == 0) {
		gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
		gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
	}

	// Print current credit and product information
    printk("\nCurrent credit: %d\n", vendingMachine.internal.Credit);
	printk("Selected product: %d\n", vendingMachine.internal.Product);
	printk("Price of selected product: %d\n", vendingMachine.internal.Price);
}

void button3_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    assignment3_but4_raise_enter(&vendingMachine);
    printk("\nSelected product.\n");

	if (!button3_pressed_once) {
		if (vendingMachine.internal.Credit >= vendingMachine.internal.Price && vendingMachine.internal.Product > 0) {
			gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);
		} else if (vendingMachine.internal.Credit < vendingMachine.internal.Price && vendingMachine.internal.Product > 0) {
			gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);
		}

		if (vendingMachine.internal.Product == 0 && vendingMachine.internal.Credit > 0) {
			gpio_pin_configure_dt(&led3, GPIO_OUTPUT_ACTIVE);
		} else if (vendingMachine.internal.Product == 0 && vendingMachine.internal.Credit <= 0) {
			gpio_pin_configure_dt(&led3, GPIO_OUTPUT_INACTIVE);
		}

		printk("\nPress again to confirm.\n");
		button3_pressed_once = true;
	} else {
		if (vendingMachine.internal.Credit >= vendingMachine.internal.Price && vendingMachine.internal.Product > 0) {
			printk("\nSale completed.\n");
			vendingMachine.internal.Credit = vendingMachine.internal.Credit - vendingMachine.internal.Price;
			gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);
		} else if (vendingMachine.internal.Credit < vendingMachine.internal.Price && vendingMachine.internal.Product > 0) {
			printk("\nInsufficient credit!\n");
			gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);
		}

		if (vendingMachine.internal.Product == 0 && vendingMachine.internal.Credit > 0) {
			vendingMachine.internal.Credit = 0;
			printk("\nRefunded credit!\n");
			gpio_pin_configure_dt(&led3, GPIO_OUTPUT_INACTIVE);
		} else if (vendingMachine.internal.Product == 0 && vendingMachine.internal.Credit <= 0) {
			printk("\nThere is no credit to refund!\n");
			gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);
		}

		button3_pressed_once = false;
	}

	// Print current credit and product information
    printk("\nCurrent credit: %d\n", vendingMachine.internal.Credit);
	printk("Selected product: %d\n", vendingMachine.internal.Product);
	printk("Price of selected product: %d\n", vendingMachine.internal.Price);
}

int main(void)
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

    ret = gpio_pin_interrupt_configure_dt(&button0, GPIO_INT_EDGE_TO_ACTIVE );
    ret = gpio_pin_interrupt_configure_dt(&button1, GPIO_INT_EDGE_TO_ACTIVE );
    ret = gpio_pin_interrupt_configure_dt(&button2, GPIO_INT_EDGE_TO_ACTIVE );
    ret = gpio_pin_interrupt_configure_dt(&button3, GPIO_INT_EDGE_TO_ACTIVE );

    gpio_init_callback(&button0_cb_data, button0_pressed, BIT(button0.pin));
    gpio_init_callback(&button1_cb_data, button1_pressed, BIT(button1.pin));
    gpio_init_callback(&button2_cb_data, button2_pressed, BIT(button2.pin)); 
    gpio_init_callback(&button3_cb_data, button3_pressed, BIT(button3.pin));

    gpio_add_callback(button0.port, &button0_cb_data);
    gpio_add_callback(button1.port, &button1_cb_data);
    gpio_add_callback(button2.port, &button2_cb_data);
    gpio_add_callback(button3.port, &button3_cb_data);   

	while (1)
	{
		k_msleep(1000);
	}

    return 0;
}