# Russbear-ciphers

## 4F Cipher

The **4F cipher** is a basic encryption method that transforms text into hexadecimal symbols. The algorithm follows these steps:

1. **Binary Conversion**:  
   Each character in the input string is converted into its binary representation based on its ASCII value.

2. **Binary Grouping**:  
   The resulting binary sequence is divided into blocks of 4 bits each. If necessary, leading zeros are added for padding to ensure all blocks are complete.

3. **Hexadecimal Mapping**:  
   Each 4-bit block is mapped to a hexadecimal digit ranging from `0` to `F`. This creates a compact encrypted output.

4. **Suffix Annotation**:  
   After the encryption process, a suffix is appended to the result based on the distribution of **letters** (`A-Z`, `a-z`) and **digits** (`0-9`) in the **original input string**:
   - If the number of letters exceeds the number of digits, the suffix `++` is added.
   - If the number of digits exceeds the number of letters, the suffix `--` is added.
   - If the number of letters and digits is equal, the suffix `+-` is added.

The **4F cipher** is designed for simplicity and serves as a foundation for exploring more complex encryption techniques.
