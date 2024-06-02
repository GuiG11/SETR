#include "unity.h"
#include "IoT.c"  //mudar isto

void setUp(void) {

}

void tearDown(void) {

}

void test_process_command_set_led(void) {
    const char *cmd = "L";
    const char *data = "1010";
    
    process_command(cmd, data);

    TEST_ASSERT_EQUAL_UINT32(1, led_states[0]);
    TEST_ASSERT_EQUAL_UINT32(0, led_states[1]);
    TEST_ASSERT_EQUAL_UINT32(1, led_states[2]);
    TEST_ASSERT_EQUAL_UINT32(0, led_states[3]);
}

void test_process_command_read_buttons(void) {
    button_states[0] = 1;
    button_states[1] = 0;
    button_states[2] = 1;
    button_states[3] = 0;
    
    const char *cmd = "R";
    const char *data = "B";
    
    process_command(cmd, data);
    
    //TEST_ASSERT_EQUAL_STRING("Button states: 1 0 1 0\n\r", uart_output_buffer);
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_process_command_set_led);
    RUN_TEST(test_process_command_read_buttons);


    return UNITY_END();
}
