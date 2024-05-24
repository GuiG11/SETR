#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/uart.h>


// 1000 msec = 1 sec 
#define SLEEP_TIME_MS   1000

// Define the size of the receive buffer 
#define RECEIVE_BUFF_SIZE 10

// Define the receiving timeout period 
#define RECEIVE_TIMEOUT 100

// Define stack size and scheduling priority used by each thread 
#define STACKSIZE 1024

#define THREAD0_PRIORITY 7
#define THREAD1_PRIORITY 7

#define SW0_NODE	DT_ALIAS(sw0)   // Button 0 node
#define SW1_NODE	DT_ALIAS(sw1)   // Button 1 node
#define SW2_NODE	DT_ALIAS(sw2)   // Button 2 node
#define SW3_NODE	DT_ALIAS(sw3)   // Button 3 node

#define LED0_NODE DT_ALIAS(led0)    // LED 0 node
#define LED1_NODE DT_ALIAS(led1)    // LED 1 node
#define LED2_NODE DT_ALIAS(led2)	// LED 2 node
#define LED3_NODE DT_ALIAS(led3)	// LED 3 node

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

// Define the transmission buffer, which is a buffer to hold the data to be sent over UART
static uint8_t tx_buf[] =   {"nRF Connect SDK Fundamentals Course\n\r"
                             "Press 1-3 on your keyboard to toggle LEDS 1-3 on your development kit\n\r"};

// Define the receive buffer 
static uint8_t rx_buf[RECEIVE_BUFF_SIZE] = {0};

// Define the callback function for UART 
static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
{
	switch (evt->type) {

	case UART_RX_RDY:
	if((evt->data.rx.len) == 1){

		if(evt->data.rx.buf[evt->data.rx.offset] == '1')
			gpio_pin_toggle_dt(&led0);
		else if (evt->data.rx.buf[evt->data.rx.offset] == '2')
			gpio_pin_toggle_dt(&led1);
		else if (evt->data.rx.buf[evt->data.rx.offset] == '3')
			gpio_pin_toggle_dt(&led2);					
		}
	break;
	case UART_RX_DISABLED:
		uart_rx_enable(dev ,rx_buf,sizeof rx_buf,RECEIVE_TIMEOUT);
		break;
		
	default:
		break;
	}
}

void button0_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	gpio_pin_toggle_dt(&led0);
}

void button1_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	gpio_pin_toggle_dt(&led1);
}

void button2_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	gpio_pin_toggle_dt(&led2);
}

void button3_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	gpio_pin_toggle_dt(&led3);
}

void thread_buttons(void)
{
	while (1) {
		uint32_t button0_state = gpio_pin_get_dt(&button0);
		uint32_t button1_state = gpio_pin_get_dt(&button1);
		uint32_t button2_state = gpio_pin_get_dt(&button2);
		uint32_t button3_state = gpio_pin_get_dt(&button3);

		// Call printk() to display a simple string "Hello, I am thread0" 
		printk("%d %d %d %d,\n", button0_state, button1_state, button2_state, button3_state);

		// Make the thread yield 
        //k_yield();

		// Put the thread to sleep 
		k_msleep(SLEEP_TIME_MS);
	}
}

void thread_leds(void)
{
	while (1) {
		uint32_t led0_state = gpio_pin_get_dt(&led0);
		uint32_t led1_state = gpio_pin_get_dt(&led1);
		uint32_t led2_state = gpio_pin_get_dt(&led2);
		uint32_t led3_state = gpio_pin_get_dt(&led3);

		// Call printk() to display a simple string "Hello, I am thread0" 
		printk("%d %d %d %d,\n", led0_state, led1_state, led2_state, led3_state);

		// Make the thread yield 
        //k_yield();

		// Put the thread to sleep 
		k_msleep(SLEEP_TIME_MS);
	}
}

// Define and initialize the two threads 
K_THREAD_DEFINE(thread0_id, STACKSIZE, thread_buttons, NULL, NULL, NULL,
		THREAD0_PRIORITY, 0, 0);
K_THREAD_DEFINE(thread1_id, STACKSIZE, thread_leds, NULL, NULL, NULL,
		THREAD1_PRIORITY, 0, 0);

int main (void)
{
    int ret;

	// Verify that the UART device is ready
	if (!device_is_ready(uart)){
		printk("UART device not ready\r\n");
		return 1 ;
	}

	// Verify that the LEDs devices are ready
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

	// Configure the GPIOs of the LEDs
	ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&led3, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return -1;
	}

	// // Verify that the buttons devices are ready
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

	// Configure the GPIOs of the buttons
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

	// Register the UART callback function 
	ret = uart_callback_set(uart, uart_cb, NULL);
		if (ret) {
			return 1;
		}

	// Send the data over UART by calling uart_tx()
	ret = uart_tx(uart, tx_buf, sizeof(tx_buf), SYS_FOREVER_MS);
	if (ret) {
		return 1;
	}

	// Start receiving by calling uart_rx_enable() and pass it the address of the receive  buffer 
	ret = uart_rx_enable(uart ,rx_buf,sizeof rx_buf,RECEIVE_TIMEOUT);
	if (ret) {
		return 1;
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
		k_msleep(SLEEP_TIME_MS);
	}
}