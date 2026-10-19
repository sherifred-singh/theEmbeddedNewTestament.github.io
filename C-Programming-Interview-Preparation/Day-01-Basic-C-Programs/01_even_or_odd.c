/**
 * ============================================================================
 * Program 01: Check Even or Odd (Bitwise vs Modulo)
 * ============================================================================
 *
 * 1. Problem Statement:
 *    Write a C program to determine whether a given integer is even or odd.
 *    Demonstrate both the standard arithmetic modulo method and the fast
 *    bitwise AND method preferred in embedded systems.
 *
 * 2. Logic Explanation:
 *    - Arithmetic approach: (num % 2 == 0) checks if remainder is zero.
 *    - Bitwise approach: In binary, all even numbers have their Least Significant
 *      Bit (LSB / Bit 0) as 0, and all odd numbers have Bit 0 as 1.
 *      Evaluating (num & 1) directly tests the LSB. If result is 0, it is even.
 *    - Embedded perspective: On low-power microcontrollers (e.g., ARM Cortex-M0)
 *      lacking a hardware division unit, integer division/modulo incurs a
 *      software routine overhead (~20-40 cycles). A bitwise AND executes in
 *      exactly 1 clock cycle.
 *
 * 3. Expected Input & Output:
 *    - Input:  42  -> Output: Even
 *    - Input:  17  -> Output: Odd
 *    - Input: -13  -> Output: Odd
 *
 * 4. Time Complexity:  O(1)
 * 5. Space Complexity: O(1)
 *
 * 6. Sample Output:
 *    --- Even or Odd Check ---
 *    Testing value: 42
 *      Modulo Method : 42 is Even
 *      Bitwise Method: 42 is Even
 *    Testing value: 17
 *      Modulo Method : 17 is Odd
 *      Bitwise Method: 17 is Odd
 *    Testing value: -13
 *      Modulo Method : -13 is Odd
 *      Bitwise Method: -13 is Odd
 *
 * 7. Interview Follow-Up Question:
 *    Q: "What subtle bug can occur when using (n % 2 == 1) for negative odd numbers in C99?"
 *    A: In C99, integer division truncates toward zero, meaning (-5 % 2) evaluates
 *       to -1, NOT 1. Therefore, an `if (n % 2 == 1)` check will evaluate to false
 *       for negative odd numbers. Using (n % 2 != 0) or (n & 1) avoids this bug.
 * ============================================================================
 */

#include <stdio.h>
#include <stdbool.h>

/* Check using standard modulo operator */
static bool is_even_modulo(int num)
{
    /* Use != 0 to properly handle negative odd integers */
    return (num % 2 == 0);
}

/* Check using bitwise AND (1 CPU cycle on all microcontrollers) */
static bool is_even_bitwise(int num)
{
    /* LSB = 0 means divisible by 2 (Even) */
    return ((num & 1) == 0);
}

int main(void)
{
    int test_values[] = {42, 17, 0, -13, -24};
    int total_tests = (int)(sizeof(test_values) / sizeof(test_values[0]));

    printf("--- Even or Odd Check ---\n");

    for (int i = 0; i < total_tests; i++)
    {
        int val = test_values[i];
        printf("Testing value: %d\n", val);
        printf("  Modulo Method : %d is %s\n", val, is_even_modulo(val) ? "Even" : "Odd");
        printf("  Bitwise Method: %d is %s\n", val, is_even_bitwise(val) ? "Even" : "Odd");
    }

    return 0;
}
