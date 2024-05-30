#ifndef RTDB_H
#define RTDB_H

#include <zephyr/kernel.h>
#include <stdint.h>

// Define the structure for the RTDB
typedef struct {
    uint32_t button_state[4];
    uint32_t led_state[4];
    int16_t analog_value_raw;
    int analog_value;
}rtdb;

extern rtdb io_data;

// Function prototypes
void rtdb_init(void);

void read_button_states(uint32_t *states);
void write_button_states(uint32_t *states);

void read_led_states(uint32_t *states);
void write_led_states(uint32_t *states); 

int16_t read_raw_value(void);
int read_analog_value(void);
void write_raw_value(uint16_t raw) ;
void write_analog_value(int value);

#endif // RTDB_H
