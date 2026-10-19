/**
 * ============================================================================
 * Program 02: Reverse an Integer (with 32-bit Overflow Protection)
 * ============================================================================
 *
 * 1. Problem Statement:
 *    Write a C program to reverse the digits of a 32-bit signed integer.
 *    Ensure that negative numbers retain their sign and arithmetic overflow
 *    is prevented before multiplication.
 *
 * 2. Logic Explanation:
 *    - In each iteration, extract the last digit using modulo: rem = n % 10.
 *    - Before multiplying reversed by 10, check for overflow against INT32_MAX / 10
 *      and INT32_MIN / 10.
 *    - Accumulate into the reversed number: reversed = (reversed * 10) + rem.
 *    - Divide the original number by 10: n = n / 10.
 *    - Repeat until n becomes 0.
 *
 * 3. Expected Input & Output:
 *    - Input:  12345   -> Output:  54321
 *    - Input: -9876    -> Output: -6789
 *    - Input:  1200    -> Output:  21
 *    - Input:  1000000009 (overflows 32-bit on reverse) -> Returns 0 (or error indicator)
 *
 * 4. Time Complexity:  O(log10 N) — proportional to the number of digits.
 * 5. Space Complexity: O(1)       — purely register-based.
 *
 * 6. Sample Output:
 *    --- Reverse Integer Demonstration ---
 *    Original:  12345        -> Reversed:  54321 (Status: OK)
 *    Original: -9876         -> Reversed: -6789 (Status: OK)
 *    Original:  1200         -> Reversed:  21 (Status: OK)
 *    Original:  1000000009   -> Reversed:  0 (Status: OVERFLOW DETECTED)
 *
 * 7. Interview Follow-Up Question:
 *    Q: "Why is reversing numbers without converting to a string critical in embedded firmware?"
 *    A: Converting to a string requires character buffer allocation (`char buf[12]`)
 *       and formatted I/O like `snprintf`, which carries substantial flash and stack
 *       overhead. Mathematical digit reversal runs entirely in CPU core registers
 *       without touching memory buffers.
 * ============================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define INT32_MAX_VAL   (2147483647)
#define INT32_MIN_VAL  (-2147483648)

/* Reverses signed integer; returns true on success, false on overflow */
static bool reverse_integer(int32_t num, int32_t *result)
{
    int32_t reversed = 0;
    int32_t current = num;

    if (result == NULL)
    {
        return false;
    }

    while (current != 0)
    {
        int32_t rem = current % 10;

        /* Guard against positive 32-bit overflow */
        if ((reversed > (INT32_MAX_VAL / 10)) ||
            ((reversed == (INT32_MAX_VAL / 10)) && (rem > 7)))
        {
            *result = 0;
            return false;
        }

        /* Guard against negative 32-bit underflow */
        if ((reversed < (INT32_MIN_VAL / 10)) ||
            ((reversed == (INT32_MIN_VAL / 10)) && (rem < -8)))
        {
            *result = 0;
            return false;
        }

        reversed = (reversed * 10) + rem;
        current /= 10;
    }

    *result = reversed;
    return true;
}

int main(void)
{
    int32_t test_cases[] = {12345, -9876, 1200, 0, 1000000009};
    int count = (int)(sizeof(test_cases) / sizeof(test_cases[0]));

    printf("--- Reverse Integer Demonstration ---\n");

    for (int i = 0; i < count; i++)
    {
        int32_t original = test_cases[i];
        int32_t reversed = 0;
        bool ok = reverse_integer(original, &reversed);

        if (ok)
        {
            printf("Original: %11d -> Reversed: %11d (Status: OK)\n", original, reversed);
        }
        else
        {
            printf("Original: %11d -> Reversed: %11d (Status: OVERFLOW DETECTED)\n", original, reversed);
        }
    }

    return 0;
}
