# 📘 Day 01 — 10 Fundamental C Programming Interview Programs

Welcome to **Day 01** of the C Programming Interview Preparation track. This module contains **10 clean, compilable, and production-tested C programs** focusing on core language fundamentals, bitwise operations, math logic, arrays, and string manipulations frequently asked in Embedded Software and Firmware Engineer interviews.

---

## 📋 Program Index & Summary Table

| # | Program File | Problem Focus | Time Complexity | Space Complexity | Embedded Key Insight |
| :-: | :--- | :--- | :-: | :-: | :--- |
| **01** | [`01_even_or_odd.c`](./01_even_or_odd.c) | Check Even or Odd | $O(1)$ | $O(1)$ | Bitwise `& 1` vs modulo `% 2` cycle cost on MCUs lacking HW division. |
| **02** | [`02_reverse_integer.c`](./02_reverse_integer.c) | Reverse Integer | $O(\log_{10} N)$ | $O(1)$ | Preventing 32-bit arithmetic overflow without buffer allocation. |
| **03** | [`03_palindrome_number.c`](./03_palindrome_number.c) | Palindrome Number | $O(\log_{10} N)$ | $O(1)$ | Half-reversal technique eliminates overflow risks. |
| **04** | [`04_factorial.c`](./04_factorial.c) | Factorial Calculation | $O(N)$ | $O(1)$ | Iterative loop avoids recursion stack frame overflow (MISRA-C 17.2). |
| **05** | [`05_prime_number.c`](./05_prime_number.c) | Prime Number Check | $O(\sqrt{N})$ | $O(1)$ | Integer `i * i <= N` prevents floating-point `sqrt()` library bloat. |
| **06** | [`06_min_max_array.c`](./06_min_max_array.c) | Min & Max in Array | $O(N)$ | $O(1)$ | Single linear pass; sensor outlier rejection and NULL pointer guards. |
| **07** | [`07_reverse_string.c`](./07_reverse_string.c) | In-Place String Reversal | $O(N)$ | $O(1)$ | Two-pointer swap; mutable RAM arrays vs read-only `.rodata` string literals. |
| **08** | [`08_count_vowels_consonants.c`](./08_count_vowels_consonants.c) | String Character Analysis | $O(N)$ | $O(1)$ | Safe `(unsigned char)` casting when calling `<ctype.h>` functions. |
| **09** | [`09_fibonacci_series.c`](./09_fibonacci_series.c) | Fibonacci Series | $O(N)$ | $O(1)$ | 3-register iterative state shift vs exponential $O(2^N)$ recursion. |
| **10** | [`10_swap_without_temp.c`](./10_swap_without_temp.c) | Swap Two Numbers | $O(1)$ | $O(1)$ | Bitwise XOR vs arithmetic swap; critical pointer aliasing guard. |

---

## 🛠 Compilation & Execution

All programs are written in standard **C99** and compile cleanly with `-Wall -Wextra -std=c99 -pedantic`.

### Compiling a Specific Program
```bash
gcc -Wall -Wextra -std=c99 -pedantic 01_even_or_odd.c -o 01_even_or_odd
./01_even_or_odd
```

### Compiling All Programs in One Command
```bash
# On Linux / macOS / MinGW:
for f in *.c; do gcc -Wall -Wextra -std=c99 -pedantic "$f" -o "${f%.c}"; done
```

---

## 💡 Detailed Program Walkthroughs & Interview Follow-Ups

### 1. Check Even or Odd (`01_even_or_odd.c`)
* **Problem:** Determine whether an integer is even or odd.
* **Logic:** 
  * Modulo check: `num % 2 == 0`.
  * Bitwise check: `(num & 1) == 0`. The LSB of all binary even numbers is `0`, and for odd numbers it is `1`.
* **Sample Output:**
  ```text
  Testing value: 42
    Modulo Method : 42 is Even
    Bitwise Method: 42 is Even
  ```
* **Interview Follow-Up:** *Why is `(n % 2 == 1)` buggy for negative odd numbers?*  
  In C99, integer division truncates towards zero. `(-5 % 2)` yields `-1`, NOT `1`. Thus `if (n % 2 == 1)` evaluates to false. Use `(n % 2 != 0)` or `(n & 1)` instead.

---

### 2. Reverse an Integer (`02_reverse_integer.c`)
* **Problem:** Reverse the digits of a 32-bit signed integer.
* **Logic:** Continuously extract the remainder `num % 10`, multiply the accumulator by 10, and divide `num /= 10`. Includes bounds checking against `INT32_MAX / 10` before multiplication.
* **Sample Output:**
  ```text
  Original:  12345      -> Reversed:  54321 (Status: OK)
  Original: -9876       -> Reversed: -6789 (Status: OK)
  Original:  1000000009 -> Reversed:  0 (Status: OVERFLOW DETECTED)
  ```
* **Interview Follow-Up:** *How do you prevent integer overflow before executing `reversed * 10 + rem`?*  
  Compare `reversed > INT_MAX / 10`. If `reversed == INT_MAX / 10`, verify that `rem <= INT_MAX % 10` (which is 7 for 32-bit signed int).

---

### 3. Palindrome Number (`03_palindrome_number.c`)
* **Problem:** Determine if an integer reads the same forwards and backwards without converting to a string.
* **Logic:** Negative numbers and numbers ending with 0 (except 0) are never palindromes. Reversing only the second half of the number until `num <= reversed_half` avoids full integer overflow.
* **Sample Output:**
  ```text
  Number:   121 -> Palindrome: YES
  Number:  -121 -> Palindrome: NO
  Number: 12321 -> Palindrome: YES
  ```
* **Interview Follow-Up:** *What is the advantage of reversing only half the number?*  
  Reversing the full integer can overflow a 32-bit integer if the reversed value exceeds `2,147,483,647`. Half-reversal guarantees the value never exceeds the original integer's magnitude.

---

### 4. Factorial Calculation (`04_factorial.c`)
* **Problem:** Calculate the factorial of non-negative integer $N$.
* **Logic:** Iterative accumulation using `uint64_t`. Returns an error for $N > 20$ because $21!$ exceeds $2^{64} - 1$.
* **Sample Output:**
  ```text
   5! = 120
  10! = 3628800
  20! = 2432902008176640000
  21! = OVERFLOW (Exceeds 64-bit capacity)
  ```
* **Interview Follow-Up:** *Why does MISRA-C Rule 17.2 forbid recursion in safety-critical firmware?*  
  Microcontrollers have fixed, limited stack SRAM (often 1 KB - 8 KB). Deep or uncontrolled recursion easily exhausts stack memory, triggering silent RAM corruption or HardFault exceptions.

---

### 5. Prime Number Check (`05_prime_number.c`)
* **Problem:** Check whether an integer $N > 1$ is prime.
* **Logic:** Early exit for $N \le 1$, multiples of 2, and multiples of 3. Then test divisors of the form $6k \pm 1$ up to `i * i <= N`.
* **Sample Output:**
  ```text
  Number:   2 -> Prime: YES
  Number:  17 -> Prime: YES
  Number:  49 -> Prime: NO
  Number:  97 -> Prime: YES
  ```
* **Interview Follow-Up:** *Why use `i * i <= N` instead of `i <= sqrt(N)`?*  
  `sqrt()` is a floating-point function from `libm`. On microcontrollers lacking a hardware FPU (e.g., Cortex-M0/M3), linking `sqrt()` pulls in software floating-point emulation libraries, increasing Flash memory footprint and execution latency.

---

### 6. Min and Max in an Array (`06_min_max_array.c`)
* **Problem:** Find the minimum and maximum elements in an array in a single traversal.
* **Logic:** Initialize `min` and `max` to `arr[0]`. Scan through index 1 to $N - 1$, updating `min` and `max`. Include NULL pointer and zero-length input validation.
* **Sample Output:**
  ```text
  Array Elements: [34, -5, 89, 12, 0, 77]
  Minimum Value : -5
  Maximum Value : 89
  ```
* **Interview Follow-Up:** *Why is initializing with `arr[0]` better than `INT_MAX` / `INT_MIN`?*  
  If the array has elements, initializing with `arr[0]` guarantees that the returned minimum and maximum are authentic values present in the input dataset.

---

### 7. In-Place String Reversal (`07_reverse_string.c`)
* **Problem:** Reverse a C string in-place without auxiliary buffers or `malloc`.
* **Logic:** Two pointers: `left` at index 0 and `right` at `len - 1`. Swap `str[left]` and `str[right]` while `left < right`.
* **Sample Output:**
  ```text
  Original: [Embedded] -> Reversed: [deddebmE]
  Original: [Firmware] -> Reversed: [erawmriF]
  ```
* **Interview Follow-Up:** *What happens if you pass `char *str = "Hello";` to an in-place reversal function?*  
  `char *str = "Hello";` points to a string literal in read-only Flash/ROM memory (`.rodata`). Attempting to modify it triggers a Segmentation Fault or MCU Bus Fault. Mutable arrays (`char str[] = "Hello";`) must be used.

---

### 8. String Character Analysis (`08_count_vowels_consonants.c`)
* **Problem:** Count vowels, consonants, digits, and spaces in a C string.
* **Logic:** Traverse string character by character; convert to lowercase with `tolower((unsigned char)c)`; categorize using ASCII ranges.
* **Sample Output:**
  ```text
  Analyzed String: "STM32 ARM Cortex-M4 @ 180MHz"
    Vowels        : 4
    Consonants    : 15
    Digits        : 6
    Spaces        : 4
    Special/Other : 2
  ```
* **Interview Follow-Up:** *Why must `char` be cast to `(unsigned char)` when calling `<ctype.h>` functions?*  
  Standard `char` can be signed (-128 to 127). Passing negative values to `<ctype.h>` functions results in undefined behavior or out-of-bounds array indexing in standard C library implementations.

---

### 9. Fibonacci Series Generation (`09_fibonacci_series.c`)
* **Problem:** Generate the first $N$ terms of the Fibonacci sequence iteratively.
* **Logic:** Maintain two state variables (`prev2 = 0`, `prev1 = 1`). Compute `current = prev2 + prev1`, print, and shift states.
* **Sample Output:**
  ```text
  Generating first 10 Fibonacci terms:
  Term  1: 0
  Term  2: 1
  Term  3: 1
  ...
  Term 10: 34
  ```
* **Interview Follow-Up:** *At what term does the Fibonacci sequence overflow a 32-bit unsigned integer?*  
  $F(47) = 2,971,215,073$ fits in `uint32_t`, but $F(48) = 4,807,526,976$ exceeds `UINT32_MAX` ($4,294,967,295$), requiring `uint64_t`.

---

### 10. Swap Two Numbers Without Temp Variable (`10_swap_without_temp.c`)
* **Problem:** Swap two integer variables without using a temporary variable.
* **Logic:**
  * Bitwise XOR swap: `*a ^= *b; *b ^= *a; *a ^= *b;`.
  * Arithmetic swap: `*a = *a + *b; *b = *a - *b; *a = *a - *b;`.
* **Sample Output:**
  ```text
  [Test 1: Bitwise XOR Swap]
    Before Swap: a = 25, b = 70
    After Swap : a = 70, b = 25
  [Test 3: Pointer Aliasing Safety Check]
    Value before self-swap: 50
    Value after self-swap : 50 (Safely protected against zeroing!)
  ```
* **Interview Follow-Up:** *What fatal bug occurs if `swap_xor(&x, &x)` is called without checking `if (a != b)`?*  
  If both pointers point to the exact same memory location, the first operation `*a ^= *b` becomes `x ^= x`, which evaluates to `0`. The variable is instantly wiped out!

---

*Continue to Day 02 for Pointers, Memory Models, and Function Pointers.*
