# Cipher Tool: 4F

This tool provides encryption functionality using a custom cipher algorithm. The encryption process is designed to be irreversible, making it similar to a hash function. It supports Unicode characters and does not include decryption functionality.

## How It Works

1. **Binary Conversion**:
   - Each character in the input string is converted into its 8-bit binary representation.

2. **Hexadecimal Conversion**:
   - The binary string is grouped into 4-bit chunks and converted into hexadecimal.

3. **Base36 Compression**:
   - The hexadecimal string is further compressed into Base35 format for compactness.

4. **Suffix Addition**:
   - A suffix (`++`, `--`, or `+-`) is added based on the ratio of letters to digits in the input string.
