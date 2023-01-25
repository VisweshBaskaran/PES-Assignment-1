/*
Author: Visweshwaran Baskaran
Sources:  
uint32_t multiply(uint32_t x, int y): based on code provided in https://www.geeksforgeeks.org/multiply-two-numbers-without-using-multiply-division-bitwise-operators-and-no-loops/
char *hexdump(char *str, size_t size, const void *loc, size_t nbytes): Offset printing logic obtained from dicussion with Mihir Patil
*/
#include<stdio.h>
#include<stdint.h>
#include<assert.h>
#include<string.h>

#define maxlen_binstr_to_uint 34
#define minlen_binstr_to_uint 2
#define maxlen_hexstr_to_uint 10
#define minlen_hexstr_to_uint 3
#define startbit_max_grabfour 28
#define startbit_min_grabfour 0

typedef enum 
{
CLEAR,
SET,
TOGGLE
} operation_t;

/*
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
*/
char *hexdump(char *str, size_t size, const void *loc, size_t nbytes)
{   
    if(size > nbytes) //size has to be large enough to fit nbytes of data in the return string
    ;
    else
    {
        str[0] = '\0';
        return str; 
    }
    if (nbytes > 65535) //nbytes < 65535 
    { 
        str[0] = '\0';
        return str;
    }
    int char_count=0, str_count=0;//char_count counts the character, str_count counts the index of str.
    uint8_t input_char, mask_nibble0 = 0x0F, mask_nibble1 =0xF0, input_nibble0,input_nibble1 ; // nibble masks to extract lower nibble (nibble0) and upper nibble (nibble1)
    uint8_t *input = (uint8_t *)loc; //dereferencing loc after typecasting into uint8_t *
    uint16_t offset_copy,offset=0; 
    int i = 0; //nbyte counter
    while(i<nbytes) //Loop for nbytes time
    {   
        if(char_count== 0) //Block to print offset when a new line is encountered or when hexdump starts
        {
            offset_copy = offset; //copying to preserve offset
            str[str_count++]='0'; //0x  to denote offset is in hexadecimal
            str[str_count++]='x';
            uint8_t hex_str[5]; //array to store 4 byte hex value
            for (int i = 0; i < 4; i++)
            {
            hex_str[3 - i] = "0123456789ABCDEF"[offset_copy & 0xF]; //Assigning from end based on a lookup string indexed by offset and mask of 0xF to obtain the first bit
            offset_copy >>= 4; //Bitwise right shift by 4 bits to be able to extract next 4 bits in next iteration
            }
        //hex_str values are stored to str;
        str[str_count++] = hex_str[0];
        str[str_count++] = hex_str[1];
        str[str_count++] = hex_str[2];
        str[str_count++] = hex_str[3];
        // 2 spaces after offset
        str[str_count++] = ' ';
        str[str_count++] = ' ';
        //offset incremented by 8
        offset = offset + 8;
        }
        if(char_count!=8) 
        {
        input_char = input[i]; //Accessing each character by indexing and storing it in input_char
        input_nibble1 = input_char & mask_nibble1; //0xF0, mask to obtain upper nibble
        input_nibble1 = input_nibble1 >> 4; // Arithmetic shift right to bring upper nibble to lower nibble, now takes values between 0-15
         if(input_nibble1>=10)    
            str[str_count++] = input_nibble1 - 10 + 'A'; //To assign A to F
        else if(input_nibble1 <10)
            str[str_count++] = input_nibble1 + '0';// To assign 0 to 9
            
        input_nibble0 = input_char & mask_nibble0; //0x0F, mask to obtain lower nibble
        if(input_nibble0>=10) 
            str[str_count++] = input_nibble0 - 10 + 'A'; //To assign A to F
        else if(input_nibble0 <10)
            str[str_count++] = input_nibble0 + '0'; // To assign 0 to 9
        str[str_count++] = ' ';//Leave a space after one character
        char_count++; //increment character count
        i++; //increment nbyte counter
        }
        else
        {   //At end of each line before offset is printed
            char_count = 0; //Character count resetted to enter offset block
            str_count--; //Space after character at end of line has to be reassigned to \n
            str[str_count++] = '\n'; //Assigning newline
        }
    }
    str_count--;
    str[str_count] = '\0';
    return str;
}
uint32_t pow2(int n) //Function to compute 2^n, where n is passed as the argument to pow2.
{
  uint32_t result = 1; // 2^0 = 1;
  for (int i=1; i<=n; i++) //if n is 0, result is returned with initialized value i.e 1 = 2^0
  {
    result = result * 2; // multiplying result with 2, n times to achieve 2^n
  }
  return result;
}
uint32_t pow16(int n) //Function to compute 16^n, where n is passed as the argument to pow16.
{
    int32_t result = 1; // 16^0 = 1;
    for (int i=1; i<=n; i++) //if n is 0, result is returned with initialized value i.e 1 = 16^0
    { 
        result = result * 16; //multiplying result with 2, n times to achieve 16^n
    }
    return result;
}
uint32_t multiply(uint32_t x, int y) //Function to compute product of 2 numbers by using recursion
{
   /* 0  multiplied with anything gives 0 */
   if(y == 0) return 0;
   /* Add x one by one */
   else if(y > 0 ) return (x + multiply(x, y-1)); //adds x to x by y times to achieve x*y;
  /* the case where y is negative */
    return (-multiply(x, -y)); 
   //else if(y < 0 ) return (-multiply(x, -y));
   //return 0;
}
/*
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
*/
int int_to_binstr(char *str, size_t size, int32_t num, uint8_t nbits)
{
    uint8_t nbits_copy = nbits+1; //since first two indices are taken up by 0 and 1, we have to start filling from 2 to (nbits+1)
    int rem; //variable to store reminder when num is divided by 2
    if(str == NULL) //if str is NULL, -1 is returned and str is set to be empty
    {
        str = "";
        return 0xFFFFFFFF;
    }
     //Checking if size is big enough to accommodate the returned string str
    if(size >= (nbits+2) ) //nbits + 2 is the lower bound since we have to accommodate '0', 'b' and nbits
    {
        ;
    }
    else
    {
        str = ""; //when size is not large enough, str is set to be empty and -1 is returned
        return 0xFFFFFFFF;
    }
    int32_t maxvalue_signed_int_32 = (pow2(31) - 1);
    int32_t minvalue_signed_int_32 = -(pow2(31));
    if((num <= maxvalue_signed_int_32) && (num >= minvalue_signed_int_32)) //if num lies between maxvalue and minvalue of signed 32 bit int then input is valid
    {
        ;
    }
    else
    {
        str = ""; //when num is not valid, str is set to be empty and -1 is returned
        return 0xFFFFFFFF; 
    }
    if(nbits >= 0 && nbits <= 255) //if nbit lies between the minvalue and maxvalue of unsigned 8 bit in then input is valid
    {
        ;
    }
    else
    {
        str = ""; //when nbit is not valid, str is set to be empty and -1 is returned
        //printf("nbits not in range"); 
        return 0xFFFFFFFF;
    }
    //To check if nbits is large enough to hold num, we can simply check whether num lies between the maxvalue and minvalue of signed 'nbits' bit int
    //For example when nbit = 8, the range starts from min value of signed 8 bit integet and ends at max value of signed 8 bit integer
    int minval = -(pow2(nbits - 1));  // -(2^(nbits-1))
    int maxval = pow2((nbits - 1)) - 1; // 2^(nbbits-1)
    if(num <= maxval && num >=minval)
    {
        //setting 0th index and 1st index as '0' and 'b'
        str[0] = '0'; 
        str[1] = 'b';
        //Based on whether num is greater than 0, lesser than or equal to 0, str and size are computed
        if(num == 0)
        {
            for(int i= (nbits+2); i>1; i--) 
            {
                
                str[i] = '0'; //all bits after index 0 and 1 i.e after 0b is set to be 0
                
            }
            //printf("final string: %s\n",str);
            size = nbits +2;
            return (size); //size includes: '0' + 'b' + nbits
        }
        if(num>0)
        {
            //logic to convert to binary
            while(num>0)
            {
                rem = num & 1; //extracting 0th bit to obtain reminder
                //assigning 1 or 0 to string based on reminder from LSB towards MSB till num > 0
                if(rem == 1) 
                {
                    str[nbits_copy] = '1';
                }
                else if(rem == 0)
                {
                    str[nbits_copy] = '0';
                }
                nbits_copy--;
                num = num >> 1; //dividing by 2;
            }
            //Loop to add '0' to str from current index to 2nd index
            for(int i= (nbits_copy); i>1; i--)
            {
                //printf("current nbits_copy %d\n",i);
                str[i] = '0'; 
            }
            str[(nbits+2)] = '\0';  //adding null character at the end;
            //printf("final string: %s\n",str);
            size = nbits+2;
            return (size);
        }
        else if(num<0)
        {
             //Binary representation of a negative number in 2's complement 
             //can be obtained by computing the binary representation of the decimal number:2^nbits + num
            int32_t newnum = pow2(nbits) + num;
            while(newnum>0)
            {
                //temp = modulus2(newnum);
                rem = newnum & 1; //obtaining remainder when divided by 2, by extracting 0th bit
                //printf("%d\n",temp);
                //printf("%d current nbits_copy\n", nbits_copy);
                //assigning 1 or 0 to string based on reminder from LSB towards MSB till num > 0
                if(rem == 1)
                {
                    str[nbits_copy ] = '1';
                    //printf("string value: %c \n",str[nbits_copy]);
                }
                else if(rem == 0)
                {
                    str[nbits_copy ] = '0';
                    //printf("string value: %c \n",str[nbits_copy]);
                }
                nbits_copy--;
                newnum = newnum >> 1;
            }
            //printf(" nbits_copy value before for %d",nbits_copy);
            //Loop to add '0' to str from current index to 2nd index
            for(int i= nbits_copy; i>=2; i--)
            {
                //printf("current nbits_copy %d",i);
                str[i] = '0';
            }
            str[(nbits+2)] = '\0'; //adding null character at the end;
            //printf("final string: %s\n",str);
            return (nbits+2);
        }
    }
    str = "";
    return 0xFFFFFFFF;
}
int test_int_to_binstr()
{
    char str[255]="";
    size_t size = sizeof(str);
    size_t size1 = 7;
    assert (10 == int_to_binstr(str, size, 18,8));
    assert (6 == int_to_binstr(str, size, -1,4));
    assert (10 == int_to_binstr(str, size, -3,8));
    assert (-1 == int_to_binstr(str, size, -18,4));
    assert (-1 == int_to_binstr(str, size1, 64,9));
    assert (-1 == int_to_binstr(NULL, size, -18,4));
    assert (-1 == int_to_binstr(str, size, -18,-1));
    assert (-1 == int_to_binstr(str, size, 2147483648,4));
    assert (34 == int_to_binstr(str, size, 2147483647,32));
    assert (34 == int_to_binstr(str, size, -2147483647,32));
    assert (3 == int_to_binstr(str, size, 0,1));
    return 1;
}
/*
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

*/
uint32_t hexstr_to_uint(const char *str){
    int len = 0; //variable to store length of str
    int exponent; //variable to store exponent value to which power, 2 should be raised to
    uint32_t uint=0; //result variable to be returned  
    if(str == NULL) //if str is NULL, -1 is returned
    {
        return 0xFFFFFFFF;
    }
    if(str[0]=='0' && (str[1]=='x' || str[1] == 'X')) //to verify if the input is of form '0x... or 0X...'
    {  
        while(str[len]!='\0') //calculating len by parsing till end of string
        {
            len++;
        }
        //the range of valid values for length is 2 + 1 to 2 + 8 i.e 3 to 10
        if((maxlen_hexstr_to_uint< len) || (len < minlen_hexstr_to_uint))  
        {
            return 0xFFFFFFFF; //return -1 when length has invalid value
        }
        for(int i = 2; i<len; i++)
        {
            //checking for validity of characters in the string after 0x or 0X
            if(((str[i] < 'a')|| (str[i] > 'f')) && ((str[i] < 'A') || (str[i] > 'F')) && ((str[i] < '0') || (str[i] > '9')))
                
                return 0xFFFFFFFF; //return -1 when length has invalid value
            else
                //printf("okay\n")
                ; //do nothing
        }
    }
    else
    {   
        return 0xFFFFFFFF;
    }
    //logic to convert hexstr to uint
    len = len-1; //adjusting length wrt 0 index
    for(int i = len; i>1; i--)
    {
        exponent = len - i;
        //Based on the character in str[i], its corresponding numerical value is used to increment result variable according to place value in base 16
        switch(str[i])
        {   case '0':
            //uint = uint + multiply((pow16(exponent)), 0);
            break;
            
            case '1':
            uint = uint + multiply((pow16(exponent)), 1); 
            break;
            
            case '2':
            uint = uint + multiply((pow16(exponent)), 2);
            break;
            
            case '3':
            uint = uint + multiply((pow16(exponent)), 3);
            break;
            
            case '4':
            uint = uint + multiply((pow16(exponent)), 4);
            break;
            
            case '5':
            uint = uint + multiply((pow16(exponent)), 5);
            break;
            
            case '6':
            uint = uint + multiply((pow16(exponent)), 6);
            break;
            
            case '7':
            uint = uint + multiply((pow16(exponent)), 7);
            break;
            
            case '8':
            uint = uint + multiply((pow16(exponent)), 8);
            break;
            
            case '9':
            uint = uint + multiply((pow16(exponent)), 9);
            break;
            
            case 'a':
            uint = uint + multiply((pow16(exponent)), 10);
            break;
            
            case 'A':
            uint = uint + multiply((pow16(exponent)),10);
            break;
            
            case 'b':
            uint = uint + multiply((pow16(exponent)), 11);
            break;
            
            case 'B':
            uint = uint + multiply((pow16(exponent)), 11);
            break;
            
            case 'c':
            uint = uint + multiply((pow16(exponent)), 12);
            break;
            
            case 'C':
            uint = uint + multiply((pow16(exponent)), 12);
            break;
            
            case 'd':
            uint = uint + multiply((pow16(exponent)), 13);
            break;
            
            case 'D':
            uint = uint + multiply((pow16(exponent)), 13);
            break;
            
            case 'e':
            uint = uint + multiply((pow16(exponent)), 14);
            break;
            
            case 'E':
            uint = uint + multiply((pow16(exponent)), 14);
            break;
            
            case 'f':
            uint = uint + multiply((pow16(exponent)), 15);
            break;
            
            case 'F':
            uint = uint + multiply((pow16(exponent)), 15);
            break;    
        }

    }
    return uint;

}
int test_hexstr_to_uint()
{
    assert(0xFFFFFFFF == hexstr_to_uint(NULL));
    assert(0xFFFFFFFF == hexstr_to_uint("1x"));
    assert(0xFFFFFFFF == hexstr_to_uint(""));
    assert(18 == hexstr_to_uint("0x12"));
    assert(18 == hexstr_to_uint("0x0012"));
    assert(65400 == hexstr_to_uint("0xfF78"));
    assert(310 == hexstr_to_uint("0x0136"));
    assert(0xFFFFFFFF == hexstr_to_uint("0XFbabababab1"));

    return 1;

}
/*
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
*/
uint32_t binstr_to_uint(const char *str){
    int len = 0;
    int exponent;
    uint32_t uint=0;//initiating decimal value to be 0;
      if(str == NULL)
    {
        return 0xFFFFFFFF;
    }
    if(str[0]=='0' && str[1]=='b') //to check if the input is of form '0b...'
    {  
        while(str[len]!='\0')
        {
            len++;
        }
        if((len>maxlen_binstr_to_uint) || (len == minlen_binstr_to_uint)) //34 & 2 
        {
            return 0xFFFFFFFF;
        }
        for(int i = 2; i<len; i++)
        {
            if(str[i] == '0' || str[i] == '1')
                ;
            else
                return 0xFFFFFFFF;
        }
    }
    else
    {   
        return 0xFFFFFFFF;
    }

    //logic to convert binstr to uint
    len = len-1; //storing max length
    for(int i = len; i>1; i--)
    {
        exponent = len - i;
        if(str[i] == '1')
        {  
            uint = uint + pow2(exponent); 
        }
    }
    return uint;
}
int test_binstr_to_uint()
{
assert(0xFFFFFFFF == binstr_to_uint("") );
assert(0xFFFFFFFF == binstr_to_uint(NULL) );
assert(0 == binstr_to_uint("0b00") );
assert(0xFFFFFFFF == binstr_to_uint("0b05100") );
assert(6 == 0b110);
assert(0xFFFFFFFF == binstr_to_uint("0A110"));
assert(0xFFFFFFFF == binstr_to_uint("0B110"));
assert(0xFFFFFFFF == binstr_to_uint("0b"));
assert(0xFFFFFFFF == binstr_to_uint("0b111111111111111111111111111111111"));
return 1;
}

/*
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
*/

uint32_t grab_four_bits(uint32_t input, int start_bit){
    uint32_t mask = 0x000F; 
    if(start_bit > startbit_max_grabfour  || start_bit < startbit_min_grabfour)
    {
        return 0xFFFFFFFF;
    }
    input = input >> start_bit;
    input = input & mask;
    return input;
}

int test_grab_four_bits()
{
    assert( 12 ==  grab_four_bits(0x7337,6));
    assert( 6 == grab_four_bits(0x7337,7));
    assert( 0xFFFFFFFF == grab_four_bits(0x0FAC,29));
    assert( 0xFFFFFFFF == grab_four_bits(0xCEEC,-1));
    return 1;
}
/*
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
*/
uint32_t twiggle_except_bit(uint32_t input, int bit, operation_t operation){
    if(bit>=0 && bit <=31)
    ;
    else
    {
        return 0xFFFFFFFF;
    }
    uint32_t mask = 1 << bit;
    if(operation == CLEAR)
    {
         /*since we need to clear all the bits except bit in consideration, 
         we use a mask which contains all the bits to be 0 except the required position which is 1,
         therefore doing 'bitwise and' of the input and mask gets us the desired result  */
        input = input & mask;
    }
    else if(operation == SET)
    {
        //printf("0x%08x\n",mask);
         /*since we need to set all the bits except bit in consideration, 
         we use a mask which contains all the bits to be 0 except the required position which is 1,
         therefore doing 'bitwise or' of the ~input and mask gets us the desired result  */
        input = input | ~mask;
    }
    else if(operation == TOGGLE)
    {
         /*since we need to toggle the bits except bit in consideration, 
         hence we toggle all the bits and then we toggle the bit in consideration back */
        input = ~input;
        input = input ^ (mask);
    }
    else
    return 0xFFFFFFFF;
    return input;
}
int test_twiggle_except_bit()
{   

    assert(0xFFFFFFFE == twiggle_except_bit(0x0, 0, SET));
    assert(0xFFFFFFF7 == twiggle_except_bit(0x0, 3, SET));
    assert(0xFFFF8CE8 == twiggle_except_bit(0x7337, 5, TOGGLE));
    assert(0x00000001 == twiggle_except_bit(0xFFFF, 0, CLEAR));
    assert(0x00000000 == twiggle_except_bit(0x7337, 31, CLEAR));
    assert(0xFFFFFFFF == twiggle_except_bit(0x7337, -1, TOGGLE));
    assert(0xFFFFFFFF == twiggle_except_bit(0x7337, 32, CLEAR));

    return 1;
}
int main()
{   test_twiggle_except_bit();
    test_grab_four_bits();
    test_binstr_to_uint();
    test_hexstr_to_uint();
    test_int_to_binstr();
    return 0;
}