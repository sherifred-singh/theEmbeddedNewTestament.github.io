/**
 * ============================================================================
 * Program 10: Swap Two Numbers Without a Temp Variable (XOR vs Arithmetic)
 * ============================================================================
 *
 * 1. Problem Statement:
 *    Write a C program to swap two integer variables without using a temporary
 *    third variable. Implement and compare both Bitwise XOR swap and Arithmetic
 *    swap, highlighting their respective safety risks.
 *
 * 2. Logic Explanation:
 *    - Method 1: Bitwise XOR Swap:
 *      * Step 1: a = a ^ b
 *      * Step 2: b = a ^ b  -> (a ^ b) ^ b = a
 *      * Step 3: a = a ^ b  -> (a ^ b) ^ a = b
 *      * Advantage: Never suffers from arithmetic overflow.
 *      * Critical Danger: Fails completely if pointers alias the same address (&a == &b).
 *    - Method 2: Arithmetic Swap:
 *      * Step 1: a = a + b
 *      * Step 2: b = a - b
 *      * Step 3: a = a - b
 *      * Critical Danger: If a + b exceeds INT_MAX, signed integer overflow
 *        occurs, which is Undefined Behavior in C.
 *
 * 3. Expected Input & Output:
 *    - Initial: a = 25, b = 70
 *    - Swapped: a = 70, b = 25
 *
 * 4. Time Complexity:  O(1)
 * 5. Space Complexity: O(1)
 *
 * 6. Sample Output:
 *    --- Swapping Without Temporary Variable ---
 *    [Test 1: Bitwise XOR Swap]
 *      Before Swap: a = 25, b = 70
 *      After Swap : a = 70, b = 25
 *    [Test 2: Arithmetic Swap]
 *      Before Swap: x = 100, y = -45
 *      After Swap : x = -45, y = 100
 *    [Test 3: Pointer Aliasing Safety Check]
 *      Value before self-swap: 50
 *      Value after self-swap : 50 (Safely protected against zeroing!)
 *
 * 7. Interview Follow-Up Question:
 *    Q: "What fatal bug occurs if an in-place XOR swap function does not check `if (x == y)`?"
 *    A: If both pointers point to the exact same memory address (`&a == &b`),
 *       the first instruction `*x ^= *y` becomes `*x ^= *x`, which computes to 0.
 *       The variable's value is permanently erased and zeroed out!
 *       Always verify pointer addresses `if (ptr_a != ptr_b)` before an XOR swap.
 * ============================================================================
 */

#include <stdio.h>
#include <stdbool.h>

/* Bitwise XOR swap with pointer aliasing guard */
static void swap_xor(int *a, int *b)
{
    if ((a == NULL) || (b == NULL))
    {
        return;
    }

    /* Guard against pointer aliasing (&a == &b) */
    if (a != b)
    {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

/* Arithmetic swap (Warning: vulnerable to signed overflow if uncontrolled) */
static void swap_arithmetic(int *a, int *b)
{
    if ((a == NULL) || (b == NULL))
    {
        return;
    }

    if (a != b)
    {
        *a = *a + *b;
        *b = *a - *b;
        *a = *a - *b;
    }
}

int main(void)
{
    printf("--- Swapping Without Temporary Variable ---\n\n");

    /* Test 1: XOR Swap */
    int a = 25;
    int b = 70;
    printf("[Test 1: Bitwise XOR Swap]\n");
    printf("  Before Swap: a = %d, b = %d\n", a, b);
    swap_xor(&a, &b);
    printf("  After Swap : a = %d, b = %d\n\n", a, b);

    /* Test 2: Arithmetic Swap */
    int x = 100;
    int y = -45;
    printf("[Test 2: Arithmetic Swap]\n");
    printf("  Before Swap: x = %d, y = %d\n", x, y);
    swap_arithmetic(&x, &y);
    printf("  After Swap : x = %d, y = %d\n\n", x, y);

    /* Test 3: Aliasing Edge Case */
    int single_var = 50;
    printf("[Test 3: Pointer Aliasing Safety Check]\n");
    printf("  Value before self-swap: %d\n", single_var);
    swap_xor(&single_var, &single_var);
    printf("  Value after self-swap : %d (Safely protected against zeroing!)\n", single_var);

    return 0;
}
