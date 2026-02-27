# Columnar Transposition Cipher in C
**Category:** Low-Level Programming / Cryptography Baseline
**Objective:** Implementation of a symmetric key transposition cipher with manual memory management.

## Key Features
* **Manual Memory Management:** Strict use of `malloc` and `free` to handle dynamic matrices and strings.
* **Modular Architecture:** Separation of concerns using header files and implementation units.
* **File I/O:** Robust reading and writing of encrypted payloads.

## Technical Mechanics
The cipher builds a dynamic matrix based on a keyword's length. The encryption order is determined by sorting the keyword's characters, which dictates the column readout order.



## How to Build
Requires `gcc` and `make`.
```bash
make
./cipher
