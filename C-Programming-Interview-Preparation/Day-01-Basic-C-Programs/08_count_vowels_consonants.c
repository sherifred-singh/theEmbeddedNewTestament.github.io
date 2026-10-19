/**
 * ============================================================================
 * Program 08: Count Vowels, Consonants, Digits, and Spaces
 * ============================================================================
 *
 * 1. Problem Statement:
 *    Write a C program that takes a string and counts the total number of
 *    vowels, consonants, digits, and whitespace characters.
 *
 * 2. Logic Explanation:
 *    - Traverse the null-terminated string character by character until '\0'.
 *    - Convert each character to lowercase using `tolower((unsigned char)c)`.
 *    - Check categories:
 *      * If 'a', 'e', 'i', 'o', 'u' -> increment vowel count.
 *      * Else if between 'a' and 'z' -> increment consonant count.
 *      * Else if between '0' and '9' -> increment digit count.
 *      * Else if space, tab, newline -> increment space count.
 *
 * 3. Expected Input & Output:
 *    - Input:  "STM32 ARM Cortex-M4 @ 180MHz"
 *    - Output: Vowels: 4, Consonants: 15, Digits: 6, Spaces: 4
 *
 * 4. Time Complexity:  O(N) — single linear traversal.
 * 5. Space Complexity: O(1) — counter structure in local stack.
 *
 * 6. Sample Output:
 *    --- String Character Analysis ---
 *    Analyzed String: "STM32 ARM Cortex-M4 @ 180MHz"
 *      Vowels     : 4
 *      Consonants : 15
 *      Digits     : 6
 *      Spaces     : 4
 *      Special/Other: 2
 *
 * 7. Interview Follow-Up Question:
 *    Q: "Why MUST you cast `char` to `(unsigned char)` when calling functions from `<ctype.h>`?"
 *    A: On many architectures, standard `char` is signed (-128 to 127). If a char
 *       has a negative value (e.g. ASCII > 127 in extended sets), passing a negative
 *       integer to `tolower()` or `isalpha()` is undefined behavior and often causes
 *       an out-of-bounds array access in the C standard library's internal lookup table.
 * ============================================================================
 */

#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

typedef struct
{
    size_t vowels;
    size_t consonants;
    size_t digits;
    size_t spaces;
    size_t others;
} char_statistics_t;

static void analyze_string(const char *str, char_statistics_t *stats)
{
    if ((str == NULL) || (stats == NULL))
    {
        return;
    }

    stats->vowels = 0;
    stats->consonants = 0;
    stats->digits = 0;
    stats->spaces = 0;
    stats->others = 0;

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        unsigned char ch = (unsigned char)str[i];

        if (isalpha(ch))
        {
            unsigned char lower = (unsigned char)tolower(ch);
            if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u')
            {
                stats->vowels++;
            }
            else
            {
                stats->consonants++;
            }
        }
        else if (isdigit(ch))
        {
            stats->digits++;
        }
        else if (isspace(ch))
        {
            stats->spaces++;
        }
        else
        {
            stats->others++;
        }
    }
}

int main(void)
{
    const char *sample = "STM32 ARM Cortex-M4 @ 180MHz";
    char_statistics_t stats;

    analyze_string(sample, &stats);

    printf("--- String Character Analysis ---\n");
    printf("Analyzed String: \"%s\"\n", sample);
    printf("  Vowels        : %zu\n", stats.vowels);
    printf("  Consonants    : %zu\n", stats.consonants);
    printf("  Digits        : %zu\n", stats.digits);
    printf("  Spaces        : %zu\n", stats.spaces);
    printf("  Special/Other : %zu\n", stats.others);

    return 0;
}
