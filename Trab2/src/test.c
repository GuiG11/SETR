#include "unity.h"
#include "sensor.h"

// expected data = real-time data (file's last entry)

const char expected_frame_A[] = "# A +46 17 14420 569 !\n";

const char expected_frame_Pt[] = "# P t +46 345 !\n";
const char expected_frame_Ph[] = "# P h 17 288 !\n";
const char expected_frame_Pc[] = "# P c 14420 430 !\n";
const char expected_frame_Px[] = "";

const char expected_frame_L[] =  "# L +46 17 14420 580 !\n# L -15 63 798 496 !\n"
                                "# L -4 24 1011 470 !\n# L +43 42 19460 584 !\n"
                                "# L +19 27 1560 534 !\n# L -9 29 624 441 !\n"
                                "# L +39 21 12300 572 !\n# L -15 99 714 493 !\n"
                                "# L +8 21 751 431 !\n# L -34 91 1298 542 !\n"
                                "# L +13 72 539 485 !\n# L -47 80 793 495 !\n"
                                "# L -32 95 749 496 !\n# L +30 13 16350 573 !\n"
                                "# L +22 38 1423 528 !\n# L -30 95 1042 529 !\n"
                                "# L +29 62 508 487 !\n# L -3 11 674 431 !\n"
                                "# L +43 11 9800 529 !\n# L -50 90 465 486 !\n"; 


const char expected_frame_R[] = ""; 

void setUp(void) 
{
    init_buffer();
}

void tearDown(void)
{

}

// Test case for putc (filling tx buffer)
void test_putc(void)
{
    buffer_putc(SOF_SYM);
    buffer_putc(' ');
    buffer_putc('P'); buffer_putc(' '); buffer_putc('t');
    buffer_putc(' ');
    buffer_putc('+'); buffer_putc('4'); buffer_putc('6');
    buffer_putc(' ');
    buffer_putc('3'); buffer_putc('4'); buffer_putc('5');
    buffer_putc(' ');
    buffer_putc(EOF_SYM);
    buffer_putc('\n');
    TEST_ASSERT_EQUAL_STRING("# P t +46 345 !\n", txb.data);
}

// Test case for getc (retrieving values from rx buffer)
void test_getc(void)
{
    buffer_putc(SOF_SYM);
    buffer_putc(' ');
    buffer_putc('P'); buffer_putc(' '); buffer_putc('t');
    buffer_putc(' ');
    buffer_putc('+'); buffer_putc('4'); buffer_putc('6');
    buffer_putc(' ');
    buffer_putc('3'); buffer_putc('4'); buffer_putc('5');
    buffer_putc(' ');
    buffer_putc(EOF_SYM);
    buffer_putc('\n');
    TEST_ASSERT_EQUAL_STRING("# P t +46 345 !\n", txb.data);

    uart_handler();
    unsigned char received_chars[17];
    int i = 0;
    while (received_chars[i++] = buffer_getc());
    TEST_ASSERT_EQUAL_STRING("# P t +46 345 !\n", received_chars);
}

void test_calc_checksum(void)
{
    TEST_ASSERT_EQUAL_INT(465, calc_checksum('A', '\0', "+25 60 800"));
    TEST_ASSERT_EQUAL_INT(338, calc_checksum('P', 't', "-10"));
    TEST_ASSERT_EQUAL_INT(76, calc_checksum('L', '\0', ""));
}

// Test case for uart_handler
void test_uart_handler(void)
{
    buffer_putc(SOF_SYM);
    buffer_putc(' ');
    buffer_putc('P'); buffer_putc(' '); buffer_putc('t');
    buffer_putc(' ');
    buffer_putc('+'); buffer_putc('4'); buffer_putc('6');
    buffer_putc(' ');
    buffer_putc('2'); buffer_putc('2'); buffer_putc('9');
    buffer_putc(' ');
    buffer_putc(EOF_SYM);
    buffer_putc('\n');
    TEST_ASSERT_EQUAL_STRING("# P t +46 229 !\n", txb.data); // Verify tx buffer was filled properly

    uart_handler();
    TEST_ASSERT_EQUAL_STRING(txb.data, rxb.data); // Verify if tx and rx buffers are equal
}

// Test case for process_command function with 'A' command
void test_process_command_A(void)
{
    process_command('A', 0);
    TEST_ASSERT_EQUAL_STRING(expected_frame_A, txb.data); // Verify if tx buffer has expected data
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_frame_A, rxb.data); // Verify if rx buffer has expected data
}

// Test case for process_command function with 'Pt' commands
void test_process_command_Pt(void)
{
    process_command('P', 't');
    TEST_ASSERT_EQUAL_STRING(expected_frame_Pt, txb.data);
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_frame_Pt, rxb.data);
}

// Test case for process_command function with 'Ph' commands
void test_process_command_Ph(void)
{
    process_command('P', 'h');
    TEST_ASSERT_EQUAL_STRING(expected_frame_Ph, txb.data);
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_frame_Ph, rxb.data);
}

// Test case for process_command function with 'Pc' command
void test_process_command_Pc(void)
{
    process_command('P', 'c');
    TEST_ASSERT_EQUAL_STRING(expected_frame_Pc, txb.data);
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_frame_Pc, rxb.data);
}

// Test case for process_command function with 'P' command and invalid sub-command
void test_process_command_Px(void)
{
    process_command('P', 'x');
    TEST_ASSERT_EQUAL_STRING(expected_frame_Px, txb.data);
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_frame_Px, rxb.data);
}

// Test case for process_command function with 'L' command
void test_process_command_L(void)
{
    process_command('L', 0); // Assuming the second argument is not used for command 'L'
    TEST_ASSERT_EQUAL_STRING(expected_frame_L, txb.data);
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_frame_L, rxb.data);
}

// Test case for process_command function with 'R' command
void test_process_command_R(void)
{
    process_command('R', 0);
    TEST_ASSERT_EQUAL_STRING(expected_frame_R, txb.data);
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_frame_R, rxb.data);

    // Check if buffer was cleared after having it filled by A command
    process_command('A', 0);
    uart_handler();
    process_command('R', 0);
    TEST_ASSERT_EQUAL_STRING(expected_frame_R, txb.data);
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_frame_R, rxb.data);
}


int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_calc_checksum);

    RUN_TEST(test_putc);

    RUN_TEST(test_uart_handler);

    RUN_TEST(test_getc);

    RUN_TEST(test_process_command_A);
    
    RUN_TEST(test_process_command_Pt);
    RUN_TEST(test_process_command_Ph);
    RUN_TEST(test_process_command_Pc);
    RUN_TEST(test_process_command_Px);

    RUN_TEST(test_process_command_L);
    
    RUN_TEST(test_process_command_R);
    
    UNITY_END();

    return 0;
}