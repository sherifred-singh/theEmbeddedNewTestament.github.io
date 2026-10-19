/**
 * ============================================================================
 * Program 03: Check if a Number is a Palindrome
 * ============================================================================
 *
 * 1. Problem Statement:
 *    Write a C program to check whether a given integer is a palindrome.
 *    A palindrome number reads identical forward and backward (e.g., 121, 1331).
 *    Solve it mathematically without using extra string buffers or heap allocation.
 *
 * 2. Logic Explanation:
 *    - Edge cases:
 *      * Negative numbers are never palindromes (e.g., -121 reversed is 121-).
 *      * Numbers ending in 0 (except 0 itself) cannot be palindromes because
 *        no positive integer starts with a leading zero.
 *    - Optimization: We only need to reverse the second half of the number!
 *      When the original number becomes less than or equal to the reversed half,
 *      we stop.
 *      * Even length (e.g., 1221): original == reversed (12 == 12).
 *      * Odd length  (e.g., 12321): original == reversed / 10 (12 == 123 / 10).
 *
 * 3. Expected Input & Output:
 *    - Input:  121    -> Output: True  (Palindrome)
 *    - Input: -121    -> Output: False (Not a Palindrome)
 *    - Input:  10     -> Output: False (Not a Palindrome)
 *    - Input:  12321  -> Output: True  (Palindrome)
 *
 * 4. Time Complexity:  O(log10 N) — processes only half the digits.
 * 5. Space Complexity: O(1)       — purely register-based.
 *
 * 6. Sample Output:
 *    --- Palindrome Number Test ---
 *    Number:   121   -> Palindrome: YES
 *    Number:  -121   -> Palindrome: NO
 *    Number:    10   -> Palindrome: NO
 *    Number: 12321   -> Palindrome: YES
 *    Number:     0   -> Palindrome: YES
 *
 * 7. Interview Follow-Up Question:
 *    Q: "What is the advantage of reversing only half the integer instead of the whole number?"
 *    A: Reversing the full integer can trigger an integer overflow if the reversed
 *       number exceeds INT32_MAX. Reversing only half guarantees the accumulator
 *       never exceeds the size of the original number, completely eliminating
 *       overflow risk without requiring 64-bit types.
 * ============================================================================
 */

#include <stdio.h>
#include <stdbool.h>

static bool is_palindrome(int num)
{
    /* Negative numbers and non-zero numbers ending in 0 are never palindromes */
    if ((num < 0) || ((num % 10 == 0) && (num != 0)))
    {
        return false;
    }

    int reversed_half = 0;

    /* Loop until we reach the middle of the number */
    while (num > reversed_half)
    {
        reversed_half = (reversed_half * 10) + (num % 10);
        num /= 10;
    }

    /* For even length: num == reversed_half
     * For odd length : num == reversed_half / 10 (discards middle digit) */
    return ((num == reversed_half) || (num == (reversed_half / 10)));
}

int main(void)
{
    int test_cases[] = {121, -121, 10, 12321, 0, 1221, 12345};
    int count = (int)(sizeof(test_cases) / sizeof(test_cases[0]));

    printf("--- Palindrome Number Test ---\n");

    for (int i = 0; i < count; i++)
    {
        int val = test_cases[i];
        printf("Number: %7d -> Palindrome: %s\n", val, is_palindrome(val) ? "YES" : "NO");
    }

    return 0;
}
