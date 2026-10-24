# GDB log

One dated section per week. Paste the commands you used and the output you saw, then explain what it means in your own words. Pasted output with no explanation earns partial credit at most.

## Week 10 (Lab 5)

### Part A: basics with `buggy_rooms.cpp`

Build and run:

```
cmake -S . -B build
cmake --build build --target buggy_rooms
./build/buggy_rooms
```

Record:

#0  std::ostream::operator<< (...) at .../basic_string.h:227
#1  0x00005555555563de in describe (room=0x0) at /home/ubuntu/cosc1437/lab10/gdb/buggy_rooms.cpp:36
#2  0x00005555555566b6 in main () at /home/ubuntu/cosc1437/lab10/gdb/buggy_rooms.cpp:53

### Part B: memory with `deck_bugs.cpp`

Build with AddressSanitizer and run each bug on its own (`./deck_bugs 1`, `2`, `3`).

For each bug, write one or two sentences: what kind of error AddressSanitizer reported, where the memory was allocated, and where it was freed.

| Bug | Report kind | Allocated at | Freed at | Cause in one sentence |
| --- | --- | --- | --- | --- |
| 1 | Direct memory leak | `deal_a_hand()` (new Card[52]) | N/A (Missing delete) | Heap-allocated memory in `deal_a_hand` was never deallocated before the function exited, causing a memory leak. |
| 2 | Double-free / Heap corruption | `RawDeck` constructor (new Card[]) | `~RawDeck()` destructor (called twice) | A shallow copy caused two `RawDeck` objects to share the same heap pointer, resulting in both destructors attempting to free it. |
| 3 | Double delete | `clear_a_table()` | `clear_a_table()` | A redundant `delete[]` call attempted to free the same memory block a second time. |

Confirm one bug in GDB. Use at least two of `watch`, `finish`, and `x`. Paste the session and explain what each command showed:

Inspected RawDeck in GDB using watch cards_ to trace allocation/deallocation addresses, and x/10xg cards_ to examine the card objects stored on the heap. This confirmed that both copied RawDeck instances pointed to the exact same memory address.

Fixes for all three bugs (describe each change):

Bug 1: Added delete[] hand; at the end of deal_a_hand() to prevent memory leaks.

Bug 2: Implemented a deep-copy constructor for RawDeck to allocate distinct heap memory for cards_ and prevent double-free errors on destruction.

Bug 3: Removed the redundant delete[] call in clear_a_table() so memory is deallocated only once.
