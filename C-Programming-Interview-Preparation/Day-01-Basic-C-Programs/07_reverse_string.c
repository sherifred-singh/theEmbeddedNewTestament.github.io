/**
 * ============================================================================
 * Program 07: In-Place String Reversal (Two-Pointer Technique)
 * ============================================================================
 *
 * 1. Problem Statement:
 *    Write a C program to reverse a null-terminated string in-place without
 *    allocating an auxiliary buffer or using dynamic memory (malloc).
 *
 * 2. Logic Explanation:
 *    - In-place reversal uses two pointers:
 *      * `left` points to the start of the string (index 0).
 *      * `right` points to the last character before '\0' (index len - 1).
 *    - While `left < right`:
 *      * Swap the characters at `*left` and `*right`.
 *      * Increment `left` and decrement `right`.
 *    - Preserves the terminating null byte ('\0') at the exact original position.
 *
 * 3. Expected Input & Output:
 *    - Input:  "Embedded"  -> Output: "deddebmE"
 *    - Input:  "Firmware"  -> Output: "erawmriF"
 *    - Input:  "A"         -> Output: "A"
 *    - Input:  ""          -> Output: ""
 *
 * 4. Time Complexity:  O(N) — N/2 swaps.
 * 5. Space Complexity: O(1) — zero heap/stack buffer allocation.
 *
 * 6. Sample Output:
 *    --- In-Place String Reversal ---
 *    Original: [Embedded] -> Reversed: [deddebmE]
 *    Original: [Firmware] -> Reversed: [erawmriF]
 *    Original: [A]        -> Reversed: [A]
 *    Original: []         -> Reversed: []
 *
 * 7. Interview Follow-Up Question:
 *    Q: "What happens if you pass `char *str = "Embedded";` to your function?"
 *    A: A catastrophic crash (Segmentation Fault or MCU BusFault/HardFault).
 *       String literals defined with `char *` are placed in the read-only data
 *       section (.rodata) in Flash memory. Attempting to write or swap characters
 *       in .rodata triggers a memory management fault. In-place reversal requires
 *       a mutable array in RAM, such as `char str[] = "Embedded";`.
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h>

static void reverse_string_in_place(char *str)
{
    if (str == NULL)
    {
        return;
    }

    size_t len = strlen(str);
    if (len <= 1)
    {
        return; /* Nothing to reverse for empty or 1-char strings */
    }

    size_t left = 0;
    size_t right = len - 1;

    while (left < right)
    {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;

        left++;
        right--;
    }
}

int main(void)
{
    /* Use mutable char arrays (in RAM/Stack), NOT string literals */
    char test1[] = "Embedded";
    char test2[] = "Firmware";
    char test3[] = "A";
    char test4[] = "";

    printf("--- In-Place String Reversal ---\n");

    printf("Original: [%s] -> ", "Embedded");
    reverse_string_in_place(test1);
    printf("Reversed: [%s]\n", test1);

    printf("Original: [%s] -> ", "Firmware");
    reverse_string_in_place(test2);
    printf("Reversed: [%s]\n", test2);

    printf("Original: [%s] -> ", "A");
    reverse_string_in_place(test3);
    printf("Reversed: [%s]\n", test3);

    printf("Original: [%s] -> ", "");
    reverse_string_in_place(test4);
    printf("Reversed: [%s]\n", test4);

    return 0;
}
