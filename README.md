# PES-Assignment-1
This repository contains the implementation of various functions for Assignment 1 of PES ECEN5813 Spring23.

## Functions
## 1. binstr_to_uint

       uint32_t binstr_to_uint(const char *str)
       
This function returns an unsigned integer represented by a binary string input which is null terminated. The binary string should be of the form '0bcccccc' where each 'c' must be '0' or '1'. The characters in the string are case sensitive.

Return type: uint32_t

Returned variable: An unsigned integer of 32 bits containing the base 10 value of the given binary string.

Argument:

str: (const char*) Data type. The binary string to be converted.
Function logic:

Invalidity arises if str is NULL, if the first two characters of the string are not '0b', or if the length of the string is more than 34 or less than 3.
The function accesses each character in the string from the least significant bit (LSB) and calculates its equivalent base 10 value to compute the return variable.

## 2. int_to_binstr

       int int_to_binstr(char *str, size_t size, int32_t num, uint8_t nbits)
This function computes the binary representation of a signed integer num and stores it in the character array str. The function returns the number of characters written to str.

Return type: int

Returned variable: size, the number of characters written to str.

Arguments:

str: (char*) Data type. The computed binary representation is stored in str. It should not be NULL.
size: (size_t) Data type. Represents the number of characters written to str. str should be large enough to accommodate the number of characters written.
num: (int32_t) Data type. Contains the base 10 number. Should be within the bounds of int32_t.
nbits: (uint8_t) Data type. nbits should be large enough to fit in num.

Function logic:

Invalidity cases are checked, including str being NULL, size not being large enough, num and nbits being within the data type's bounds, and nbits being able to fit in the binary representation of num.
When num can fit between -2^(nbits-1) and 2^(nbits-1) - 1, the first and second indices of str are set to '0' and 'b', respectively.
When num is 0, '0' is assigned to all indices from 2 to nbits + 2.
When num is greater than 0, the remainder is extracted using & 0b1. Based on the remainder, the corresponding string is assigned and stored in str.
When num is less than 0, the same process as above is followed after adding 2^nbits to the number to obtain the 2's complement directly.

## 3. hexstr_to_uint

    uint32_t hexstr_to_uint(const char *str)

This function returns an unsigned integer represented by a hexadecimal string input which is null terminated. The hexadecimal string should be of the form '0xcccccc' where 'c' are between '0' and 'F'. The characters in the string are not case sensitive.

Return type: uint32_t

Returned variable: An unsigned integer of 32 bits containing the base 10 value of the given hexadecimal string.

Argument:

str: (const char*) Data type. The hexadecimal string to be converted.
Function logic:

Invalidity arises if str is NULL, if the first two characters of the string are not '0x' or '0X', or if the characters in str do not belong to the hexadecimal characters (i.e., 0-9, a-f, A-F).
The function accesses each character in the string from the least significant bit (LSB) and calculates its equivalent base 10 value to compute the return variable.

## 4. twiggle_except_bit

       uint32_t twiggle_except_bit(uint32_t input, int bit, operation_t operation)

This function performs an operation on all bits of the input value except the given bit. The operations available are defined in the operation_t enum.

Return type: uint32_t

Returned variable: An unsigned 32-bit integer.

Function logic:

The operations of setting, toggling, and clearing can be obtained by masking the input with a 1 shifted down bit times.
CLEAR: Bitwise AND with the mask.
SET: Bitwise OR with the negation of the mask.
TOGGLE: Bitwise XOR of the negation of the input and the mask.

## 5. grab_four_bits

       uint32_t grab_four_bits(uint32_t input, int start_bit)

This function returns four bits from the input value, shifted down.

Return type: uint32_t

Returned variable: An unsigned 32-bit integer containing the four bits from the start_bit towards the most significant bit (MSB).

Parameters:

input: Data type - uint32_t. Contains the input binary number.
start_bit: Data type - int. Position from which to extract four bits towards the MSB.

Function logic:

By shifting down the input by start_bit bits and using a mask with a value of 0x000F, the desired four bits can be obtained.
Invalidity arises when the start_bit has a value that fetches bits outside the 32 bits.

## 6. hexdump

       char *hexdump(char *str, size_t size, const void *loc, size_t nbytes)
 
This function returns the hexadecimal representation of memory content starting from loc. The memory content is printed in chunks of eight bytes per line. The offset, which represents the number of bytes from loc, is printed at the beginning of each line in 16-bit hexadecimal. Each character is separated by one space, and there are two spaces between the last element of an index and the first character's first element.

Return type: char *

Returned variable: str, the hexdump string.

Parameters:

str: (char*) Data type. Stores the hexdump string to be returned.
size: (size_t) Data type. Size of str.
loc: (const void*) Data type. A pointer to any constant datatype. Contains the string that is to be processed and the starting memory location.
nbytes: (size_t) Data type. Determines the number of bytes for which the hexdump has to be printed starting from loc.
Function logic:

Invalidity cases are tested by checking if size is large enough to accommodate nbytes and if nbytes is less than 65535.
For each character from loc to loc + nbytes, the ASCII value is parsed. Nibble1 and nibble0 are extracted using masks, and then the hex digits are calculated and appended to the appropriate location in str.
Every eight characters, a new line is printed, and the remaining hex dump is done eight characters at a time.
For the offset, every time eight characters are reached (along with the case before parsing any character), the offset from loc is printed in 16-bit hexadecimal. This is achieved by masking the offset by 0xF
