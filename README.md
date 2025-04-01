# Russbear-ciphers

## 4F Cipher

The **4F cipher** is a simple encryption algorithm that converts text into a compact format using binary, hexadecimal, and base-36 encoding. This implementation supports only **ASCII characters** (values 0–127).

### How It Works
1. Converts input text into binary (8 bits per character).
2. Groups binary data into 4-bit blocks and maps them to hexadecimal (`0`–`F`).
3. Compresses the hexadecimal output into base-36 (`0`–`9`, `A`–`Z`).
4. Adds a suffix (`++`, `--`, or `+-`) based on the number of letters and digits in the input.
5. Uses `=` symbols in the suffix for padding if necessary.

### Limitations
- The algorithm supports only **ASCII characters**. Input containing non-ASCII characters (e.g., Cyrillic, emojis, etc.) will result in an error.
