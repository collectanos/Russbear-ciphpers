# Russbear-ciphers

## 4F Cipher

The **4F cipher** is a simple encryption algorithm that converts text into a compact format using binary, hexadecimal, and base-36 encoding.

### How It Works
1. Converts input text into binary.
2. Groups binary data into 4-bit blocks and maps them to hexadecimal (`0`–`F`).
3. Compresses the hexadecimal output into base-36 (`0`–`9`, `A`–`Z`).
4. Adds a suffix (`++`, `--`, or `+-`) based on the number of letters and digits in the input.
