#include "unity.h"
#include "sensor.h"

// expected data = real-time data (file's last entry)

const char expected_data_A[] = "+46 17 14420 569";

const char expected_data_Pt[] = "+46 229";
const char expected_data_Ph[] = "17 184";
const char expected_data_Pc[] = "14420 331";
const char expected_data_Px[] = "";

const char expected_data_L[] = ""; 
// BOA SORTE A FAZER ESTA STRING SIMAO :) eu faria este teste tb se n tivesse o bug do label no caso L
// talvez haja uma maneira melhor de testar para isto sem ser comparar strings idk


const char expected_data_R[] = ""; // acho q reset history é ao csv n ao buffer
// se for ao csv é facil de fazer no sensor.c mas n tenho certeza como se testava aqui
// diria q é fazer TEST_ASSERT_EQUAL_STRING("", leitura do csv);
// se fizermos o reset ser ao csv, depois reaproveita-se a funçao fill q eu tinha feito
// ou ent faz se uma nova para encher o csv com os mesmos valores q agr para estes testes continuaremm possiveis sem ter de mudar a expected data

void setUp(void) 
{
    init_buffer();
}

void tearDown(void)
{

}

void test_calc_checksum()
{
    TEST_ASSERT_EQUAL_INT(465, calc_checksum('A', "+25 60 800"));
    TEST_ASSERT_EQUAL_INT(222, calc_checksum('P', "-10"));
    TEST_ASSERT_EQUAL_INT(76, calc_checksum('L', ""));
}

// Test case for process_command function with 'A' command
void test_process_command_A(void)
{
    process_command('A', 0);
    TEST_ASSERT_EQUAL_STRING(expected_data_A, txb.data); // Verify if tx buffer has expected data
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_data_A, rxb.data); // Verify if rx buffer has expected data
}

// Test case for process_command function with 'Pt' commands
void test_process_command_Pt(void)
{
    process_command('P', 't');
    TEST_ASSERT_EQUAL_STRING(expected_data_Pt, txb.data);
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_data_Pt, rxb.data);
}

// Test case for process_command function with 'Ph' commands
void test_process_command_Ph(void)
{
    process_command('P', 'h');
    TEST_ASSERT_EQUAL_STRING(expected_data_Ph, txb.data);
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_data_Ph, rxb.data);
}

// Test case for process_command function with 'Pc' command
void test_process_command_Pc(void)
{
    process_command('P', 'c');
    TEST_ASSERT_EQUAL_STRING(expected_data_Pc, txb.data);
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_data_Pc, rxb.data);
}

// Test case for process_command function with 'P' command and invalid sub-command
void test_process_command_Px(void)
{
    process_command('P', 'x');
    TEST_ASSERT_EQUAL_STRING(expected_data_Px, txb.data);
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_data_Px, rxb.data);
}

/*
// Test case for process_command function with 'L' command
void test_process_command_L(void)
{
    process_command('L', 0); // Assuming the second argument is not used for command 'L'
    // Check the content of the buffer and verify if it contains expected data
    TEST_ASSERT_EQUAL_STRING(expected_data_L, buffer);
}
*/

// Test case for process_command function with 'R' command
void test_process_command_R(void)
{
    process_command('R', 0);
    TEST_ASSERT_EQUAL_STRING(expected_data_R, txb.data);
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_data_R, rxb.data);

    // checkar se limpou o buf em seguida a um comando o encher
    process_command('A', 0);
    uart_handler();
    process_command('R', 0);
    TEST_ASSERT_EQUAL_STRING(expected_data_R, txb.data);
    uart_handler();
    TEST_ASSERT_EQUAL_STRING(expected_data_R, rxb.data);
}


int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_calc_checksum);

    RUN_TEST(test_process_command_A);
    
    RUN_TEST(test_process_command_Pt);
    RUN_TEST(test_process_command_Ph);
    RUN_TEST(test_process_command_Pc);
    RUN_TEST(test_process_command_Px);
    /*
    RUN_TEST(test_process_command_L);
    */
    RUN_TEST(test_process_command_R);
    
    UNITY_END();

    return 0;
}