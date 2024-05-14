#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include "../src/sc_types.h"
#include "../src-gen/assignment3.h"

void print_status();
void button0_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins);
void button1_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins);
void button2_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins);
void button3_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins);

int leds_configure();
int buttons_configure();
int interrupts_configure();
void init_callback();
void add_callback(); 

/** @} */ // End of sensor module

#endif /* MAIN_H */