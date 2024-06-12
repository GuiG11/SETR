/**
 * @file IoT.c
 * @brief Implementation file for the "smart" I/O module.
 * 
 * This file contains the main implementation for an IIoT device using Zephyr RTOS.
 * It handles UART communication, button states, LED control, and analog sensor readings.
 *
 * \authors Guilherme Guarino 104154, Simão Pinto 102776 - 06/2024
 *
 */
 
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>
#include "RTDB.h"

LOG_MODULE_REGISTER(IoT, LOG_LEVEL_DBG);

// 1000 msec = 1 sec 
#define SLEEP_TIME_MS   100

// Define the size of the receive buffer 
#define RECEIVE_BUFF_SIZE 128

// Define the receiving timeout period 
#define RECEIVE_TIMEOUT 100

// Define stack size and scheduling priority used by each thread 
#define STACKSIZE 1024

// Commands definitions
#define S_O_Frame '#'
#define E_O_Frame '!'

#define THREAD0_PRIORITY 7
#define THREAD1_PRIORITY 7

#define SW0_NODE    DT_ALIAS(sw0)   // Button 0 node
#define SW1_NODE    DT_ALIAS(sw1)   // Button 1 node
#define SW2_NODE    DT_ALIAS(sw2)   // Button 2 node
#define SW3_NODE    DT_ALIAS(sw3)   // Button 3 node

#define LED0_NODE DT_ALIAS(led0)    // LED 0 node
#define LED1_NODE DT_ALIAS(led1)    // LED 1 node
#define LED2_NODE DT_ALIAS(led2)    // LED 2 node
#define LED3_NODE DT_ALIAS(led3)    // LED 3 node

// Get the device pointers of the buttons through gpio_dt_spec
static const struct gpio_dt_spec button0 = GPIO_DT_SPEC_GET(SW0_NODE, gpios);   // GPIO specification for button 0
static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET(SW1_NODE, gpios);   // GPIO specification for button 1
static const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET(SW2_NODE, gpios);   // GPIO specification for button 2
static const struct gpio_dt_spec button3 = GPIO_DT_SPEC_GET(SW3_NODE, gpios);   // GPIO specification for button 3

// Get the device pointers of the LEDs through gpio_dt_spec
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios); // GPIO specification for LED 0
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios); // GPIO specification for LED 1
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios); // GPIO specification for LED 2
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios); // GPIO specification for LED 3

// Get the device pointer of the UART hardware 
const struct device *uart= DEVICE_DT_GET(DT_NODELABEL(uart0));

static struct gpio_callback button0_cb_data;    // Callback data for button 0
static struct gpio_callback button1_cb_data;    // Callback data for button 1
static struct gpio_callback button2_cb_data;    // Callback data for button 2
static struct gpio_callback button3_cb_data;    // Callback data for button 3

// Define a variable of type adc_dt_spec for each channel
static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));

// Define a variable of type adc_sequence and a buffer of type uint16_t 
int16_t buf;
struct adc_sequence sequence = {
	.buffer = &buf,
	// buffer size in bytes, not number of samples 
	.buffer_size = sizeof(buf),
	// Optional
	//.calibrate = true,
};

// Define the transmission buffer, which is a buffer to hold the data to be sent over UART
static uint8_t tx_buf[] =   {"\nEnter a command in this format #CMDDATA!\n\r"
                             "\tCMD:\t'L' for LEDs\t'R' for Readings\n\r"
                             "\tDATA:\tL: 4 binaries\tR: 'A' for ADC, 'B' for Buttons\n\r"};

// Define the receive buffer 
static uint8_t rx_buf[RECEIVE_BUFF_SIZE] = {0};
static size_t rx_buf_index = 0;

uint32_t button_states[4];
uint32_t led_states[4];

/**
 * @brief Function to send data via UART.
 * 
 * @param data Pointer to the data to be sent.
 */
static void uart_send(const char *data) {
    int ret = uart_tx(uart, data, strlen(data), SYS_FOREVER_MS);
    //printk("%s", &tx_buf);
    if (ret)
        LOG_ERR("Failed to send data via UART: %d", ret);
}

/**
 * @brief Function to process received command.
 * 
 * @param cmd The command character.
 * @param data The data string.
 */
static void process_command(const char *cmd, const char *data) {
    if (strcmp(cmd, "L") == 0) {
        for (int i = 0; i < 4; i++) {
            led_states[i] = data[i] - '0';
        }
        write_led_states(led_states);
    } else if (strcmp(cmd, "R") == 0) {
        if (strcmp(data, "A") == 0) {
            int value = read_analog_value();
            char buf[32];
            snprintf(buf, sizeof(buf), "\n\rAnalog value: %d mV", value);
            //printk("\n%s\n", buf);
            uart_send(buf);
        } else if (strcmp(data, "B") == 0) {
            read_button_states(button_states);
            char buf[64];
            snprintf(buf, sizeof(buf), "\n\rButton states: %d %d %d %d",
                     button_states[0], button_states[1], button_states[2], button_states[3]);
            //printk("\n%s\n", buf);
            uart_send(buf);
        }
    } else {
        uart_send("\n\rInvalid command");
    }
}

/**
 * @brief Function to validate and process received frame.
 * 
 * @param frame The received frame.
 */
static void process_frame(const char *frame) {
    char cmd[2] = {0};
    char data[5] = {0};
    int frame_len = strlen(frame);

    //LOG_INF("\nProcessing frame: %s", frame);

    if (frame[0] != S_O_Frame || frame[frame_len - 2] != E_O_Frame || frame[frame_len - 1] != '\r') {
        uart_send("\n\rInvalid frame");
        return;
    }

    // Extract command and data from the frame
    sscanf(frame, "#%1s", cmd);

    if (strcmp(cmd, "L") == 0){
        if (frame_len != 8){
            uart_send("\n\rInvalid frame");
            return;
        }
        // Extract data for 'L' command
        sscanf(frame, "#L%4s!", data);
        for(int i=0; i<4; i++){
            if (data[i] != '0' && data[i] != '1'){
                uart_send("\n\rInvalid frame");
                return;
            }
        }
    }
    else if (strcmp(cmd, "R") == 0){
        if (frame_len != 5){
        uart_send("\n\rInvalid frame");
        return;
        }
        // Extract data for 'R' command
        sscanf(frame, "#R%1s!", data);
        if (data[0] != 'A' && data[0] != 'B'){
            uart_send("\n\rInvalid frame");
            return;
        }
    }
    else {
        uart_send("\n\rInvalid frame");
        return;
    }


    //LOG_INF("Command: %s, Data: %s", cmd, data);

    // Process the valid command
    process_command(cmd, data);
}

/**
 * @brief UART interrupt callback function.
 * 
 * @param dev The UART device.
 * @param user_data User data.
 */
static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data) {
    static bool receiving_frame = false;
    switch (evt->type) {
        case UART_RX_RDY:
            for (size_t i = 0; i < evt->data.rx.len; i++) {
                char received_char = evt->data.rx.buf[evt->data.rx.offset + i];
                if (received_char != '\r')
                    printk("%c", received_char);
                else
                    printk("\n\r");

                if (received_char == S_O_Frame) {
                    receiving_frame = true;
                    rx_buf_index = 0;
                }

                if (receiving_frame && rx_buf_index < RECEIVE_BUFF_SIZE - 1) {
                    rx_buf[rx_buf_index++] = received_char;
                }

                if (received_char == '\r') {
                    rx_buf[rx_buf_index] = '\0';
                    process_frame(rx_buf);
                    receiving_frame = false;  // Reset frame receiving flag after processing
                    rx_buf_index = 0;  // Reset buffer index after processing
                }
            }
            break;
        case UART_RX_DISABLED:
            uart_rx_enable(dev, rx_buf, sizeof(rx_buf), RECEIVE_TIMEOUT);
            break;
        default:
            break;
    }
}

void button0_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {}
void button1_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {}
void button2_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {}
void button3_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {}

/**
 * @brief Thread for reading button states and storing them in RTDB.
 * 
 * This function reads the states of the buttons connected to the GPIO pins
 * and stores these states in the real-time database (RTDB).
 */
void thread_buttons(void) {
    while (1) {
        button_states[0] = gpio_pin_get_dt(&button0);
        button_states[1] = gpio_pin_get_dt(&button1);
        button_states[2] = gpio_pin_get_dt(&button2);
        button_states[3] = gpio_pin_get_dt(&button3);

        write_button_states(button_states);

        k_msleep(SLEEP_TIME_MS);
    }
}

/**
 * @brief Thread for reading LED states and updating the LEDs.
 * 
 * This function reads the states of the LEDs from the real-time database (RTDB)
 * and updates the LEDs connected to the GPIO pins according to these states.
 */
void thread_leds(void) {
    while (1) {
        read_led_states(led_states);

        gpio_pin_set_dt(&led0, led_states[0]);
        gpio_pin_set_dt(&led1, led_states[1]);
        gpio_pin_set_dt(&led2, led_states[2]);
        gpio_pin_set_dt(&led3, led_states[3]);

        k_msleep(SLEEP_TIME_MS);
    }
}

/**
 * @brief Thread for reading and processing the analog sensor value.
 * 
 * This function reads the raw value from the analog sensor using the ADC,
 * converts this value to millivolts, and stores both values in the real-time
 * database (RTDB).
 */
void thread_analog_sensor(void) {
    int val_mv, raw;
    int err;
    while (1) {

        // Read a sample from the ADC 
		err = adc_read(adc_channel.dev, &sequence);
		if (err < 0) {
			LOG_ERR("Could not read (%d)", err);
			continue;
		}

        raw = (int)buf;
        write_raw_value(raw);

        // Convert raw value to mV
        val_mv = raw;
		err = adc_raw_to_millivolts_dt(&adc_channel, &val_mv);
		// conversion to mV may not be supported, skip if not 
		if (err < 0) {
			LOG_WRN(" (value in mV not available)\n");
		} else {
            write_analog_value(val_mv);
		}

        k_msleep(SLEEP_TIME_MS);
    }
}

// Define and initialize the threads
K_THREAD_DEFINE(thread0_id, STACKSIZE, thread_buttons, NULL, NULL, NULL, THREAD0_PRIORITY, 0, 0);
K_THREAD_DEFINE(thread1_id, STACKSIZE, thread_leds, NULL, NULL, NULL, THREAD1_PRIORITY, 0, 0);
K_THREAD_DEFINE(thread2_id, STACKSIZE, thread_analog_sensor, NULL, NULL, NULL, THREAD1_PRIORITY, 0, 0);

int main(void) {
    // Initialize RTDB
    rtdb_init();

    int ret, err;

	// Verify that the UART device is ready
	if (!device_is_ready(uart)){
		printk("UART device not ready\r\n");
		return 1 ;
	}

    // Validate that the ADC peripheral (SAADC) is ready 
	if (!adc_is_ready_dt(&adc_channel)) {
		LOG_ERR("ADC controller devivce %s not ready", adc_channel.dev->name);
		return 0;
	}

    // Setup the ADC channel 
	err = adc_channel_setup_dt(&adc_channel);
	if (err < 0) {
		LOG_ERR("Could not setup channel #%d (%d)", 0, err);
		return 0;
	}

    // Initialize the ADC sequence 
	err = adc_sequence_init_dt(&adc_channel, &sequence);
	if (err < 0) {
		LOG_ERR("Could not initalize sequnce");
		return 0;
	}

    // Check if the buttons are ready
    if (!device_is_ready(button0.port) || !device_is_ready(button1.port) || !device_is_ready(button2.port) || !device_is_ready(button3.port)) {
        printk("Error: Buttons device not ready.\n");
        return 1;
    }

    // Configure button pins
    ret = gpio_pin_configure_dt(&button0, GPIO_INPUT);
	if (ret < 0) {
		return 1;
	}
	ret = gpio_pin_configure_dt(&button1, GPIO_INPUT);
	if (ret < 0) {
		return 1;
	}
	ret = gpio_pin_configure_dt(&button2, GPIO_INPUT);
	if (ret < 0) {
		return 1;
	}
	ret = gpio_pin_configure_dt(&button3, GPIO_INPUT);
	if (ret < 0) {
		return 1;
	}

    // Check if the LEDs are ready
    if (!device_is_ready(led0.port) || !device_is_ready(led1.port) || !device_is_ready(led2.port) || !device_is_ready(led3.port)) {
        printk("Error: LED device not ready.\n");
        return -1;
    }

    // Configure LED pins
    ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 1;
	}
	ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 1;
	}
	ret = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 1;
	}
	ret = gpio_pin_configure_dt(&led3, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 1;
	}

    // Initialize UART with the callback function
    ret = uart_callback_set(uart, uart_cb, NULL);
	if (ret) {
        LOG_ERR("Failed to set UART callback: %d", ret);
		return 1;
	}
	// Send the data over UART by calling uart_tx()
	ret = uart_tx(uart, tx_buf, sizeof(tx_buf), SYS_FOREVER_MS);
	if (ret) {
        LOG_ERR("Failed to set UART TX %d", ret);
		return 1;
	}
	// Start receiving by calling uart_rx_enable() and pass it the address of the receive  buffer 
	ret = uart_rx_enable(uart ,rx_buf,sizeof rx_buf,RECEIVE_TIMEOUT);
	if (ret) {
        LOG_ERR("Failed to set UART RX: %d", ret);
		return 1;
	}

    // Setup button callbacks
    gpio_init_callback(&button0_cb_data, button0_pressed, BIT(button0.pin));
    gpio_add_callback(button0.port, &button0_cb_data);
    ret = gpio_pin_interrupt_configure_dt(&button0, GPIO_INT_EDGE_TO_ACTIVE);

    gpio_init_callback(&button1_cb_data, button1_pressed, BIT(button1.pin));
    gpio_add_callback(button1.port, &button1_cb_data);
    ret = gpio_pin_interrupt_configure_dt(&button1, GPIO_INT_EDGE_TO_ACTIVE);

    gpio_init_callback(&button2_cb_data, button2_pressed, BIT(button2.pin));
    gpio_add_callback(button2.port, &button2_cb_data);
    ret = gpio_pin_interrupt_configure_dt(&button2, GPIO_INT_EDGE_TO_ACTIVE);

    gpio_init_callback(&button3_cb_data, button3_pressed, BIT(button3.pin));
    gpio_add_callback(button3.port, &button3_cb_data);
    ret = gpio_pin_interrupt_configure_dt(&button3, GPIO_INT_EDGE_TO_ACTIVE);

	return 0;
}
