#ifndef RTDB_H
#define RTDB_H

#include <zephyr/kernel.h>
#include <stdint.h>

// Define the structure for the RTDB
typedef struct {
    uint32_t button_state[4];
    uint32_t led_state[4];
    //uint16_t analog_value_raw;
    //float analog_value;
    //struct k_mutex rtdb_mutex;  // Mutex to protect RTDB
}rtdb;

extern rtdb io_data;

// Function prototypes
void rtdb_init(void);

void read_button_states(uint32_t *states);
void write_button_states(uint32_t *states);

void read_led_states(uint32_t *states);
void write_led_states(uint32_t *states); 

//float read_analog_value(void);
//void write_analog_value(uint16_t raw, float value);

#endif // RTDB_H
