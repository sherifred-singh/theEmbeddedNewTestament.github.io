# 🎯 C Programming Interview Preparation

Welcome to the **C Programming Interview Preparation** repository. This dedicated track is structured into modular daily practice modules designed to prepare embedded software, firmware, and systems engineers for technical coding interviews.

---

## 📌 Syllabus & Daily Progression Roadmap

| Day | Focus Module | Difficulty | Description | Status |
| :---: | :--- | :---: | :--- | :---: |
| **Day 01** | [**Basic C Programs**](./Day-01-Basic-C-Programs/README.md) | 🟢 Foundation | Fundamental logic, bitwise vs arithmetic, loops, arrays, and basic strings. | ✅ Complete |
| **Day 02** | **Pointers & Memory Architecture** | 🟡 Intermediate | Pointer arithmetic, function pointers, `const` pointers, stack vs heap. | ⏳ Upcoming |
| **Day 03** | **Bitwise Manipulation for Embedded** | 🟡 Intermediate | Bit masking, register packing, endianness conversion, parity checks. | ⏳ Upcoming |
| **Day 04** | **Structures, Unions & Memory Alignment** | 🟡 Intermediate | Padding, packing, bitfields, struct serialization, hardware register mapping. | ⏳ Upcoming |
| **Day 05** | **Strings & Buffer Management** | 🟡 Intermediate | Custom string libraries, ring buffer parsing, bounds checking, string-to-int. | ⏳ Upcoming |
| **Day 06** | **Storage Classes & Type Qualifiers** | 🔴 Advanced | `volatile`, `static`, `extern`, `register`, ISR memory synchronization. | ⏳ Upcoming |
| **Day 07** | **Embedded Data Structures in C** | 🔴 Advanced | Linked lists, lock-free circular FIFO buffers, finite state machine lookup tables. | ⏳ Upcoming |

---

## 🛠 Compilation & Build Instructions

All programs are written in standard **C99** and can be compiled using GCC, Clang, or any standard ANSI C compiler.

### Single File Compilation
```bash
# Compile with strict warnings
gcc -Wall -Wextra -std=c99 -pedantic <filename>.c -o <output_executable>

# Execute
./<output_executable>
```

### Batch Compilation (GCC / Linux / MinGW)
```bash
for file in *.c; do
    gcc -Wall -Wextra -std=c99 -pedantic "$file" -o "${file%.c}"
done
```

---

*Authored and maintained as part of the Embedded Systems Interview Preparation series.*
