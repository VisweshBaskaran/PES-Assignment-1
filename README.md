# PES-Assignment-1
Functions in Assignment 1 for PES ECEN5813 Spring23:
1)
uint32_t binstr_to_uint(const char *str)

Returns an unsigned integer represented by the binary string input which is null terminated. The hex 
string is of the form ‘0xcccccc’ where each c must be '0' or '1'.  The characters in the string are case sensitive.
Return type: uint32_t
Returned variable: an unsigned integer of 32 bits containing the base 10 value of the given binary string

Argument: 
str: (const char*) data type. Returns -1 incase of invalidity.

Function logic:
Invalidity arised from str being NULL, first two characters of string not being of the form 0b
Length of the string should not be more than 34 and less than 3.
From LSB, the character in each position is accessed and then its equivalent base 10 value is used to compute the return variable

2) 
int int_to_binstr(char *str, size_t size, int32_t num, uint8_t nbits)

Function to compute the binary representation of a signed integer num and store in str. 
Function returns the number of characters written to str.
Return Type: int
Returned variable: size
Arguments: 
str: (char *) Data type. Computed binary representation is stored in str. Should not be NULL
size: (size_t) Data type. Represents number of characters written to str. s
tr should be large enough to accommodate the number of characters written to str
num: (int32_t) Data type. Contains the base 10 number. Should be within bounds of int32_t
nbits: (uint8_t) Data type. nbits should be large enough to fit in num

Function logic:
Checking for invalidity cases as mentioned above; str should not be NULL, size should be large enough, num and nbits should be within the data type's bound values and nbits should be able to fit in binary representation of num.
When num will be able to fit in -2^(nbits-1) and 2^(nbits-1) - 1. 0th and 1st indices are made to be 0 and b
When num is 0, assign '0' to all indices from 2 to nbits +2
When num > 0: remainder is extracted by & 0b1. Based on remainder, the string is assigned and stored in str.
When num < 0: Same as above is followed after adding 2^nbits to the number to obtain 2's complement directly.

3)
uint32_t hexstr_to_uint(const char *str)

Returns an unsigned integer represented by the hex string input which is null terminated. The hex 
string is of the form ‘0xcccccc’ where ‘c’ are between ‘0’ and ‘F’.  The characters in the string are not case sensitive
Return type: uint32_t
Returned variable: an unsigned integer of 32 bits containing the base 10 value of the given hexstr

Argument: 
str: (const char*) data type. Returns -1 incase of invalidity.

Function logic:
Invalidity arised from str being NULL, first two characters of string not being of the form 0x or 0X, characters in str not belonging to hexadecimal characters i.e 0-9,a-f,A-F
From LSB, the character in each position is accessed and then its equivalent base 10 value is used to compute the return variable

4)
uint32_t twiggle_except_bit(uint32_t input, int bit, operation_t operation)

Except the given bit, all bits are either set, toggle or cleared based on the input operation.
Defined operations are part of a enum operation_t

Return type: uint32
Returned variable: An unsigned 32 bit integer

Function logic:
SET, CLEAR and TOGGLE can be obtained by masking the input with a 1 shifted down "bit" times mask
CLEAR: bitwise and with mask
SET: bitwise or with negation of mask
TOGGLE: bitwise xor of negation of input and mask
5)
uint32_t grab_four_bits(uint32_t input, int start_bit)

Returns four bits from the input value, shifted down.
Return type: uint32_t
Returned Variable: An unsigned 32 bit integer containing the 4 bits from start bit towards MSB.

Parameters:
input: Data type - uint32_t. Contains the input binary number 
start_bit: Data type - int. Position from which we should extract 4 bits towards MSB.

Program logic:
By shifting down the input by start bits and by using a mask of value 0x000F we can obtain the desired 4 bits
Invalidity arises when the start_bit has a value that fetches bits outside the 32 bits.

6)
char *hexdump(char *str, size_t size, const void *loc, size_t nbytes)

 This function returns the value of 8 bytes of memory per line in hexadecimal. The first location starts at loc.
 An offset is printed at the beginning of each line, which is the offset in bytes from loc in 16 bit hex. 
 Spacing between characters are 1 space and there are 2 spaces between the last element of index and first character's first element 
 
 Return Type: char *
 Returned variable: str
 Parameters:
 str: (char *) data type. Stores the hexdump string to be returned
 size: (size t) data type. Size of str
 loc: (const void *) data type. C point to any constant pointer to any datatype *. Contains the string that is to be processed and the starting memory location
 nbytes: (size_t) data type. Determines till which byte the hexdump has to be printed after starting from loc.

 Function Logic: 
 Invalidity cases are tested by checking if size is large enough to accommodate nbytes and if nbytes < 65535
 From i= 0 to nbytes, each character is parsed to obtain its ASCII value. 
 From the ASCII value nibble1 and nibble0 are extracted using masks and then are used to calculate each hex digit which are then appended to the appropriate location
 Every 8 characters, new line is printed and the remaining hex dump is done 8 characters at a time;
 For the offset, every time 8 characters is reached (along with the case before parsing any character) the offset from loc is printed in 16 bit hex. This is achieved by masking the offset by 0xF.
