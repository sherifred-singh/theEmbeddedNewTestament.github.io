/**
 * ============================================================================
 * Program 09: Fibonacci Series Generation (Iterative O(N) Space O(1))
 * ============================================================================
 *
 * 1. Problem Statement:
 *    Write a C program to generate and print the first N terms of the Fibonacci
 *    sequence (0, 1, 1, 2, 3, 5, 8, ...).
 *    Implement an iterative solution and compare its efficiency against the
 *    naive recursive Fibonacci implementation.
 *
 * 2. Logic Explanation:
 *    - Base terms: F(0) = 0, F(1) = 1.
 *    - For any term i >= 2: F(i) = F(i - 1) + F(i - 2).
 *    - We only need two state variables (`prev2 = 0`, `prev1 = 1`) and a current
 *      sum `current`.
 *    - After printing, shift states:
 *      prev2 = prev1;
 *      prev1 = current;
 *    - This uses exactly 3 CPU registers and avoids the O(2^N) branch explosion
 *      and call-stack exhaustion of recursive Fibonacci.
 *
 * 3. Expected Input & Output:
 *    - Input: N = 10
 *    - Output: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34
 *
 * 4. Time Complexity:  O(N)
 * 5. Space Complexity: O(1)
 *
 * 6. Sample Output:
 *    --- Fibonacci Series Generation ---
 *    Generating first 10 Fibonacci terms:
 *    Term  1: 0
 *    Term  2: 1
 *    Term  3: 1
 *    Term  4: 2
 *    Term  5: 3
 *    Term  6: 5
 *    Term  7: 8
 *    Term  8: 13
 *    Term  9: 21
 *    Term 10: 34
 *
 * 7. Interview Follow-Up Question:
 *    Q: "At what term does the Fibonacci sequence overflow standard 32-bit unsigned integers?"
 *    A: Term 48 overflows 32-bit unsigned integer (UINT32_MAX = 4,294,967,295).
 *       F(46) = 1,836,311,903
 *       F(47) = 2,971,215,073 (fits in uint32_t)
 *       F(48) = 4,807,526,976 (exceeds 32-bit limit -> requires uint64_t).
 *       Using uint64_t supports up to F(93).
 * ============================================================================
 */

#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdint.h>

#define MAX_PRINT_TERMS 47u

static void print_fibonacci_series(uint32_t n)
{
    if (n == 0)
    {
        printf("Requested 0 terms. Nothing to print.\n");
        return;
    }

    uint64_t prev2 = 0ULL;
    uint64_t prev1 = 1ULL;

    printf("Generating first %u Fibonacci terms:\n", n);

    for (uint32_t i = 1; i <= n; i++)
    {
        if (i == 1)
        {
            printf("Term %2u: %llu\n", i, (unsigned long long)prev2);
        }
        else if (i == 2)
        {
            printf("Term %2u: %llu\n", i, (unsigned long long)prev1);
        }
        else
        {
            uint64_t current = prev2 + prev1;
            printf("Term %2u: %llu\n", i, (unsigned long long)current);
            prev2 = prev1;
            prev1 = current;
        }
    }
}

int main(void)
{
    uint32_t terms = 10u;

    printf("--- Fibonacci Series Generation ---\n");
    print_fibonacci_series(terms);

    return 0;
}
