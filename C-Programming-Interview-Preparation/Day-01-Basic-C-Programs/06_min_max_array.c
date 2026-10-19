/**
 * ============================================================================
 * Program 06: Find Min and Max in an Array (Single Pass O(N))
 * ============================================================================
 *
 * 1. Problem Statement:
 *    Write a C program to find the smallest and largest values in an integer array
 *    in a single pass (O(N) time).
 *
 * 2. Logic Explanation:
 *    - Initialize both `min` and `max` variables with the first element of the array:
 *      min = arr[0], max = arr[0].
 *    - Traverse through the rest of the array (from index 1 to size - 1):
 *      * If arr[i] > max, update max = arr[i].
 *      * Else if arr[i] < min, update min = arr[i].
 *    - Validate inputs against NULL pointer and size == 0 before dereferencing.
 *
 * 3. Expected Input & Output:
 *    - Input:  {34, -5, 89, 12, 0, 77}
 *    - Output: Min: -5, Max: 89
 *
 * 4. Time Complexity:  O(N) — single linear pass through N elements.
 * 5. Space Complexity: O(1) — constant auxiliary memory.
 *
 * 6. Sample Output:
 *    --- Array Min & Max Search ---
 *    Array Elements: [34, -5, 89, 12, 0, 77]
 *    Minimum Value : -5
 *    Maximum Value : 89
 *
 * 7. Interview Follow-Up Question:
 *    Q: "Why is initializing min with INT_MAX and max with INT_MIN potentially riskier
 *       than initializing both with arr[0]?"
 *    A: If the array contains no elements (empty or size 0), returning INT_MAX/INT_MIN
 *       may mislead the caller into thinking those values were actual data points.
 *       Initializing with arr[0] guarantees that min and max are always authentic
 *       members of the dataset, while defensive checks (size == 0 or arr == NULL)
 *       explicitly return an error code or bool status.
 * ============================================================================
 */

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

/* Finds min and max in a single linear pass; returns false if invalid */
static bool find_min_max(const int *arr, size_t size, int *out_min, int *out_max)
{
    /* Defensive input validation */
    if ((arr == NULL) || (out_min == NULL) || (out_max == NULL) || (size == 0))
    {
        return false;
    }

    int current_min = arr[0];
    int current_max = arr[0];

    for (size_t i = 1; i < size; i++)
    {
        if (arr[i] > current_max)
        {
            current_max = arr[i];
        }
        else if (arr[i] < current_min)
        {
            current_min = arr[i];
        }
    }

    *out_min = current_min;
    *out_max = current_max;
    return true;
}

int main(void)
{
    int sensor_readings[] = {34, -5, 89, 12, 0, 77};
    size_t count = sizeof(sensor_readings) / sizeof(sensor_readings[0]);

    printf("--- Array Min & Max Search ---\n");
    printf("Array Elements: [");
    for (size_t i = 0; i < count; i++)
    {
        printf("%d%s", sensor_readings[i], (i + 1 < count) ? ", " : "]\n");
    }

    int min_val = 0;
    int max_val = 0;

    if (find_min_max(sensor_readings, count, &min_val, &max_val))
    {
        printf("Minimum Value : %d\n", min_val);
        printf("Maximum Value : %d\n", max_val);
    }
    else
    {
        printf("Error: Invalid array or empty buffer.\n");
    }

    return 0;
}
