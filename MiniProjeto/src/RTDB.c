#include "RTDB.h"

// Define mutex to protect access to shared code section 
K_MUTEX_DEFINE(test_mutex);

// Initialize the RTDB
rtdb io_data = {0};

void rtdb_init(void) {
    // Initialization if needed
}

// Function to read button states
void read_button_states(uint32_t *states) {
    k_mutex_lock(&test_mutex, K_FOREVER);
    for (int i = 0; i < 4; i++) {
        states[i] = io_data.button_state[i];
    }
    k_mutex_unlock(&test_mutex);
}

// Function to write button states
void write_button_states(uint32_t *states) {
    k_mutex_lock(&test_mutex, K_FOREVER);
    for (int i = 0; i < 4; i++) {
        io_data.button_state[i] = states[i];
    }
    k_mutex_unlock(&test_mutex);
}

// Function to read LED states
void read_led_states(uint32_t *states) {
    k_mutex_lock(&test_mutex, K_FOREVER);
    for (int i = 0; i < 4; i++) {
        states[i] = io_data.led_state[i];
    }
    k_mutex_unlock(&test_mutex);
}

// Function to write LED states
/*void write_led_states(uint32_t *states) {
    k_mutex_lock(&test_mutex, K_FOREVER);
    for (int i = 0; i < 4; i++) {
        io_data.led_state[i] = states[i];
    }
    k_mutex_unlock(&test_mutex);
}*/
/*
// Function to read analog sensor value
float read_analog_value(void) {
    float value;
    k_mutex_lock(&test_mutex, K_FOREVER);
    value = io_data.analog_value;
    k_mutex_unlock(&test_mutex);
    return value;
}

// Function to write analog sensor value
void write_analog_value(uint16_t raw, float value) {
    k_mutex_lock(&test_mutex, K_FOREVER);
    io_data.analog_value_raw = raw;
    io_data.analog_value = value;
    k_mutex_unlock(&test_mutex);
}
*/