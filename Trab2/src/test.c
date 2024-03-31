#include "unity.h"
#include "sensor.h"

void setUp(void) 
{

}

void tearDown(void)
{

}

void test_calc_checksum()
{
    TEST_ASSERT_EQUAL_INT(465, calc_checksum('A', "+25 60 800"));
    TEST_ASSERT_EQUAL_INT(222, calc_checksum('P', "-10"));
    TEST_ASSERT_EQUAL_INT(0, calc_checksum('L', ""));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_calc_checksum);

    UNITY_END();

    return 0;
}