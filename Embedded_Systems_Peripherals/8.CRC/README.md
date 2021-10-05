# CRC - Cyclic Redundancy Check

it is a type of error checking like checksum error detection it is workin by calculating the CRC value from a certain key and send it after sending data and the reciver is calculating the crc along with crc value which should be **zero** the key is chossen according to communication medium or protocol and there are alot of papers on key choose for a certain application type

## CRC plain mathematical algorithm

it depends on calculating the mod of a certain number and subtract that number from the main message key and add that product to the message to make it divisable by the key which at the reciver will produce zero when divided by the same key such that

**Data** = 152
**Key** = 5

    15
   ----------
10 | 152
---- 150
    ----
     2

10-2 = 8

then we would add that number to the message and send it such that = 152 + 8 = 160
or
subtract that mod from the message and send it 152-2 = 150

for a binary we have some rules such that

### Binary CRC math

according to the algorithm we can calculate the CRC value but here we calculate the plain CRC values such that

**Data** = 0b 11010111110
**Key** = 0b 10011

        110000111
      ---------------
10011 |  11010111110000
_______ -10011
        __________
          10011
         -10011
         _________
           000011110
          -    10011
          ___________
               011010
              - 10011
              _________
                010010
                -10011
                ________
                 000010

then the CRC value is the mod which is equal to 0010

then the data to be transmitted equal to 11010111110010

then at the Reciver the message would be **moded** over the same key (generator polinomial)

        1100001
      ---------------------
10011 | 11010111110010
_______-10011
        _______
        010011
        -10011
        _______
         0000011110
             -10011
             _______
              011010
              -10011
              _______
               010011
               -10011
               ______
                000000

then the message received correctly

some times the generator plynomial (have an extra term at digit 16 in 16-CRC or 32 in 32-CRC which is odd behavior cause shfting before Xoring with the polynomial) such as **ben Eater videos**

### For our STM32F103 we have

- ### a 32-bit data regiter so we are tied with crc-32

- ### a fixed (Ethernet) Polynomial = 0x04C11DB7

- ### Initial CRC value of 0xFFFFFFFF

- ### with no output or input reverse bits and no Xorout (no out reverse or xored with 0x00000000)

we can use [this site][https://crccalc.com/] to test the algorithm
