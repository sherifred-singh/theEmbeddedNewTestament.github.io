/**
 * ============================================================================
 * Program 05: Check if a Number is Prime (Optimized O(sqrt(N)))
 * ============================================================================
 *
 * 1. Problem Statement:
 *    Write a C program to check if an integer N is a prime number.
 *    Optimize the divisor search to O(sqrt(N)) without calling floating-point
 *    library functions like sqrt().
 *
 * 2. Logic Explanation:
 *    - A prime number is greater than 1 and has no positive divisors other than
 *      1 and itself.
 *    - Boundary conditions:
 *      * If n <= 1: Not prime.
 *      * If n == 2 or n == 3: Prime.
 *      * If n is divisible by 2 or 3: Not prime.
 *    - All primes greater than 3 can be expressed in the form 6k ± 1.
 *    - We only need to test divisors up to sqrt(n).
 *      Instead of calling `sqrt(n)` from `<math.h>`, we use the integer
 *      condition `(i * i <= n)` stepping by 6 (checking `i` and `i + 2`).
 *
 * 3. Expected Input & Output:
 *    - Input:  1  -> Output: Not Prime
 *    - Input:  2  -> Output: Prime
 *    - Input: 17  -> Output: Prime
 *    - Input: 49  -> Output: Not Prime (7 * 7)
 *    - Input: 97  -> Output: Prime
 *
 * 4. Time Complexity:  O(sqrt(N))
 * 5. Space Complexity: O(1)
 *
 * 6. Sample Output:
 *    --- Prime Number Check ---
 *    Number:   1 -> Prime: NO
 *    Number:   2 -> Prime: YES
 *    Number:  17 -> Prime: YES
 *    Number:  25 -> Prime: NO
 *    Number:  49 -> Prime: NO
 *    Number:  97 -> Prime: YES
 *
 * 7. Interview Follow-Up Question:
 *    Q: "Why should you avoid using `i <= sqrt(n)` in the loop header on an MCU?"
 *    A: First, calling `sqrt(n)` inside the loop header causes `sqrt()` to be
 *       re-evaluated every iteration unless the compiler hoists it. Second,
 *       `sqrt()` is a floating-point function from `libm`. On microcontrollers
 *       without a hardware FPU (e.g. Cortex-M0/M3), linking `sqrt()` pulls in
 *       several kilobytes of software floating-point emulation code into Flash
 *       and consumes hundreds of CPU cycles. `(i * i <= n)` uses pure integer math.
 * ============================================================================
 */

#include <stdio.h>
#include <stdbool.h>

static bool is_prime(int n)
{
    /* Numbers <= 1 are not prime */
    if (n <= 1)
    {
        return false;
    }

    /* 2 and 3 are prime */
    if ((n == 2) || (n == 3))
    {
        return true;
    }

    /* Multiples of 2 and 3 are composite */
    if (((n % 2) == 0) || ((n % 3) == 0))
    {
        return false;
    }

    /* Test divisors of form 6k ± 1 up to sqrt(n) */
    for (int i = 5; (i * i) <= n; i += 6)
    {
        if (((n % i) == 0) || ((n % (i + 2)) == 0))
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int test_numbers[] = {1, 2, 3, 4, 17, 25, 49, 97, 100, 101};
    int count = (int)(sizeof(test_numbers) / sizeof(test_numbers[0]));

    printf("--- Prime Number Check ---\n");

    for (int i = 0; i < count; i++)
    {
        int val = test_numbers[i];
        printf("Number: %3d -> Prime: %s\n", val, is_prime(val) ? "YES" : "NO");
    }

    return 0;
}
