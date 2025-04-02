# Cipher Tool: 4F

This tool provides encryption functionality using a custom cipher algorithm. The encryption process is designed to be irreversible, making it similar to a hash function. It supports Unicode characters and does not include decryption functionality.

## Features

- Converts text into a Base36-encoded string with a suffix indicating the ratio of letters to digits.
- Supports Unicode characters.
- Verbose mode displays intermediate steps during encryption.
- Designed to be irreversible, similar to a hash function.
- Compresses Base36 by grouping symbols into chunks of 3 or 2, converting them to decimal, dividing by 4, and mapping to ASCII (256).

## How It Works

1. Each character in the input string is converted into its 8-bit binary representation.
2. The binary string is grouped into 4-bit chunks and converted into hexadecimal.
3. The hexadecimal string is compressed into Base36 format.
4. Base36 is further compressed by grouping symbols into chunks of 3 or 2, converting them to decimal, dividing by 4, and mapping to ASCII (256).
5. A suffix (`++`, `--`, or `+-`) is added based on the ratio of letters to digits in the input string.
