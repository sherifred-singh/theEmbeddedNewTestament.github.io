/**
 * ============================================================================
 * Program 04: Compute Factorial (Iterative Approach & Type Limits)
 * ============================================================================
 *
 * 1. Problem Statement:
 *    Write a C program to calculate the factorial of a non-negative integer N.
 *    Implement an iterative solution and explain why recursion is strictly
 *    discouraged in embedded systems.
 *
 * 2. Logic Explanation:
 *    - Factorial definition:
 *      * 0! = 1
 *      * 1! = 1
 *      * N! = N * (N - 1) * ... * 1
 *    - Factorials grow exponentially fast:
 *      * 32-bit unsigned int overflows at 13! (13! = 6,227,020,800 > 2^32 - 1).
 *      * 64-bit uint64_t overflows at 21! (20! = 2,432,902,008,176,640,000).
 *    - Using uint64_t permits accurate calculation up to N = 20.
 *
 * 3. Expected Input & Output:
 *    - Input:  0  -> Output: 1
 *    - Input:  5  -> Output: 120
 *    - Input: 10  -> Output: 3628800
 *    - Input: 20  -> Output: 2432902008176640000
 *    - Input: 25  -> Output: Returns error / indicates overflow
 *
 * 4. Time Complexity:  O(N)
 * 5. Space Complexity: O(1)
 *
 * 6. Sample Output:
 *    --- Factorial Calculation ---
 *     0! = 1
 *     1! = 1
 *     5! = 120
 *    10! = 3628800
 *    15! = 1307674368000
 *    20! = 2432902008176640000
 *    21! = OVERFLOW (Exceeds 64-bit capacity)
 *
 * 7. Interview Follow-Up Question:
 *    Q: "Why do automotive and safety-critical standards like MISRA-C Rule 17.2 forbid recursion?"
 *    A: Embedded systems have severely constrained physical stack memory (often 1 KB to 8 KB).
 *       Recursive calls continuously push return addresses, stack frames, and local
 *       variables onto the stack. An unbounded or deep recursion leads directly to
 *       a silent stack overflow, overwriting adjacent global variables or triggering
 *       an unrecoverable microcontroller HardFault exception.
 * ============================================================================
 */

#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_SUPPORTED_FACTORIAL 20u

/* Iterative factorial returning success status and 64-bit result */
static bool calculate_factorial(uint32_t n, uint64_t *result)
{
    if (result == NULL)
    {
        return false;
    }

    /* 64-bit unsigned integer capacity limit check */
    if (n > MAX_SUPPORTED_FACTORIAL)
    {
        *result = 0;
        return false;
    }

    uint64_t fact = 1ULL;

    for (uint32_t i = 2u; i <= n; i++)
    {
        fact *= (uint64_t)i;
    }

    *result = fact;
    return true;
}

int main(void)
{
    uint32_t test_inputs[] = {0, 1, 5, 10, 15, 20, 21};
    int count = (int)(sizeof(test_inputs) / sizeof(test_inputs[0]));

    printf("--- Factorial Calculation ---\n");

    for (int i = 0; i < count; i++)
    {
        uint32_t n = test_inputs[i];
        uint64_t ans = 0;
        bool ok = calculate_factorial(n, &ans);

        if (ok)
        {
            printf("%2u! = %llu\n", n, (unsigned long long)ans);
        }
        else
        {
            printf("%2u! = OVERFLOW (Exceeds 64-bit capacity)\n", n);
        }
    }

    return 0;
}
